#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <dlfcn.h>
#include "lc3_runner.hpp"
#include "lc3_execute.hpp"
#include "lc3_os.hpp"

/** lc3_init
  *
  * Initializes the state of the lc3
  *
  * @param state An LC3 state
  * @param randomize Randomizes everything!
  */
void lc3_init(lc3_state& state, bool randomize)
{
    // Set Registers
    state.regs[0] = randomize * lc3_random();
    state.regs[1] = randomize ? lc3_random() : 32767;
    state.regs[2] = randomize * lc3_random();
    state.regs[3] = randomize * lc3_random();
    state.regs[4] = randomize * lc3_random();
    state.regs[5] = randomize * lc3_random();
    state.regs[6] = randomize * lc3_random();
    state.regs[7] = randomize ? lc3_random() : 0x490;

    // PC is initially at address 3000
    state.pc = 0x3000;

    // User mode
    state.privilege = 1;
    state.priority = 0;


    // Set Control Flags
    state.n = 0;
    state.z = 1;
    state.p = 0;

    // Set Additional Flags
    state.halted = 0;
    state.true_traps = 0;
    state.warnings = 0;
    state.executions = 0;
    state.interrupt_enabled = 0;

    // Clear subroutine info
    state.max_call_stack_size = 0;
    state.call_stack.clear();

    // Set Stack Flags
    state.max_stack_size = 0;
    state.undo_stack.clear();

    // Set I/O Stuff
    state.input = &std::cin;
    state.reader = lc3_read_char;
    state.peek = lc3_peek_char;
    state.output = &std::cout;
    state.writer = lc3_write_char;
    state.warning = &std::cout;

    // Clear memory
    memset(state.mem, 0, sizeof(short) * 65536);
    // Add LC3 OS
    memcpy(state.mem, lc3_os, LC3_OS_SIZE * sizeof(unsigned short));

    // Clear plugins
    lc3_remove_plugins(state);

    // Clear Symbol Table
    state.symbols.clear();
    state.rev_symbols.clear();

    // Clear Breakpoints and all that jazz
    state.breakpoints.clear();
    state.blackboxes.clear();
    state.reg_watchpoints.clear();
    state.mem_watchpoints.clear();
    state.subroutines.clear();

    // Clear pending interrupts
    state.interrupts.clear();
    state.interrupt_test.clear();
    state.interrupt_vector = -1;
    state.savedssp = 0x3000;
    state.savedusp = 0xF000;

    state.memory_ops.clear();
    state.total_reads = 0;
    state.total_writes = 0;

    state.in_lc3test = false;
}

/** lc3_remove_plugins
  *
  *
  */
void lc3_remove_plugins(lc3_state& state)
{
    state.instructionPlugin = NULL;
    state.plugins.clear();
    state.devicePlugins.clear();
    state.trapPlugins.clear();
    state.interruptPlugin.clear();

    // Destroy all plugins
    for (std::map<std::string, PluginInfo>::const_iterator i = state.filePlugin.begin(); i != state.filePlugin.end(); ++i)
    {
        const PluginInfo& infos = i->second;
        infos.destroy(infos.plugin);
        dlclose(infos.handle);
    }
    state.filePlugin.clear();

    // Set up "dummy plugins" to sit on reserved addresses
    state.trapPlugins[0x20] = NULL;
    state.trapPlugins[0x21] = NULL;
    state.trapPlugins[0x22] = NULL;
    state.trapPlugins[0x23] = NULL;
    state.trapPlugins[0x24] = NULL;
    state.trapPlugins[0x25] = NULL;

    state.devicePlugins[0xFE00] = NULL;
    state.devicePlugins[0xFE02] = NULL;
    state.devicePlugins[0xFFFE] = NULL;
}

/** lc3_run
  *
  * Runs the machine until the machine is halted.
  */
void lc3_run(lc3_state& state)
{
    // Do this until halted
    while (!state.halted)
    {
        // Step one instruction
        lc3_step(state);
    }
}

/** lc3_run
  *
  * Runs the machine until the machine is halted or
  * it executes num instructions.
  */
void lc3_run(lc3_state& state, unsigned int num)
{
    unsigned int i = 0;
    // Do this num times or until halted.
    while (i < num && !state.halted)
    {
        // Step one instruction
        lc3_step(state);
        // Increment instruction count
        i++;
    }
}

/** lc3_step
  *
  * Executes one instruction
  */
void lc3_step(lc3_state& state)
{
    // If we are halted then don't step.
    if (state.halted) return;
    // Tick all plugins
    lc3_tick_plugins(state);
    // Fetch Instruction
    unsigned short data = state.mem[state.pc];
    // Test for blackbox (If the line was a JSR statement and it had a blackbox).
    bool blackbox_finish = lc3_blackbox_test(state);
    // Increment PC
    state.pc++;
    // Form Instruction
    lc3_instr instr = lc3_decode(state, data);
    // Execute Instruction
    const lc3_state_change change = lc3_execute(state, instr);
    // Test for blackbox (If the first line of subroutine had a blackbox).
    if (instr.data.opcode == JSR_INSTR || (instr.data.opcode == TRAP_INSTR && state.true_traps))
        blackbox_finish = blackbox_finish || lc3_blackbox_test(state);
    // Increment executions
    state.executions++;

    // If the change is INTERRUPT END
    if (change.changes == LC3_INTERRUPT_END)
    {
        // After you've scrubbed all of the floors in hyrule (remove all instructions that have been added except the LC3_INTERRUPT change.
        lc3_state_change* hmm = &state.undo_stack.back();
        while (hmm->changes != LC3_INTERRUPT_BEGIN)
        {
            state.undo_stack.pop_back();
            hmm = &state.undo_stack.back();
        }
        // Please sire have mercy (Change LC3_INTERRUPT_BEGIN to LC3_INTERRUPT to signal a completed interrupt)
        lc3_state_change& lib = state.undo_stack.back();
        lib.changes = LC3_INTERRUPT;
    }
    else
    {
        // Push Old into state
        state.undo_stack.push_back(change);
    }
    // Never pop if you are in priveleged mode.
    if (state.privilege && state.max_stack_size != 0 && state.max_stack_size < state.undo_stack.size())
        state.undo_stack.pop_front();

    // Tock all plugins
    lc3_tock_plugins(state);

    if (blackbox_finish)
        lc3_finish(state);

    // If we hit an error or a halt instruction return. no need to do any breakpoint tests.
    if (state.halted) return;
    // Breakpoint test
    lc3_break_test(state, &change);

    if (!state.interrupt_enabled) return;

    // Chime in on all observers.
    std::list<interrupt_test_func>::iterator i;
    for (i = state.interrupt_test.begin(); i != state.interrupt_test.end(); ++i)
    {
        interrupt_test_func func = *i;
        func();
    }

    // Interrupt?
    lc3_interrupt(state);
    // Check for interrupt
    const lc3_state_change& interrupt = state.undo_stack.back();
    if (interrupt.changes != LC3_INTERRUPT_BEGIN) return;
    // Another breakpoint test
    lc3_break_test(state, &interrupt);
}

/** lc3_back
  *
  * Backsteps one instruction
  */
void lc3_back(lc3_state& state)
{
    // If there are no changes in the stack we are done
    if (state.undo_stack.empty()) return;
    // Pop Changes from state
    lc3_state_change& changes = state.undo_stack.back();
    // Will not allow to backstep out of running interrupt.
    if (changes.changes == LC3_INTERRUPT_BEGIN) return;

    // Will never happen.
    assert(changes.changes != LC3_INTERRUPT_END);

    if (changes.changes != LC3_INTERRUPT)
    {
        // Unexecute instruction
        state.pc = changes.pc;
        state.regs[0x7] = changes.r7;

        state.n = changes.n;
        state.z = changes.z;
        state.p = changes.p;
        state.halted = changes.halted;

        if (changes.changes == LC3_REGISTER_CHANGE)
        {
            // Bad if the register is > 7
            assert(changes.location < 0x7);
            state.regs[changes.location] = changes.value;
        }
        else if (changes.changes == LC3_MEMORY_CHANGE)
        {
            state.mem[changes.location] = changes.value;
            lc3_notify_plugins_write(state, changes.location, changes.value);
        }
        else if (changes.changes == LC3_MULTI_CHANGE)
        {
            for (unsigned int i = 0; i < changes.info.size(); i++)
            {
                lc3_change_info& info = changes.info[i];
                if (info.is_reg)
                {
                    assert(info.location < 0x7);
                    state.regs[info.location] = info.value;
                }
                else
                {
                    state.mem[info.location] = info.value;
                    lc3_notify_plugins_write(state, info.location, info.value);
                }
            }
        }
        else if (changes.changes == LC3_SUBROUTINE_BEGIN)
        {
            if (!state.call_stack.empty())
                state.call_stack.pop_back();
        }
        else if (changes.changes == LC3_SUBROUTINE_END)
        {
            state.call_stack.push_back(changes.subroutine);
            if (state.max_call_stack_size != 0 && state.max_call_stack_size < state.call_stack.size())
                state.call_stack.pop_front();
        }

        // Decrement PC
        state.pc--;
        // Decrease execution count
        state.executions--;
    }

    state.warnings = changes.warnings;

    if (changes.changes == LC3_INTERRUPT)
        state.executions = changes.executions;

    state.undo_stack.pop_back();
}

/** lc3_rewind
  *
  * Backsteps many instructions
  */
void lc3_rewind(lc3_state& state, unsigned int num)
{
    bool interrupt_begin = false;
    // Do this num times or until no more changes or until we aren't able.
    while (!state.undo_stack.empty() && num > 0 && !interrupt_begin)
    {
        lc3_state_change& last = state.undo_stack.back();
        interrupt_begin = (last.changes == LC3_INTERRUPT_BEGIN);
        // Backstep
        lc3_back(state);
        num--;

    }
}

/** lc3_rewind
  *
  * Backsteps as far as it can.
  */
void lc3_rewind(lc3_state& state)
{
    bool interrupt_begin = false;
    // Do this until no more changes.
    while (!state.undo_stack.empty() && !interrupt_begin)
    {
        lc3_state_change& last = state.undo_stack.back();
        interrupt_begin = (last.changes == LC3_INTERRUPT_BEGIN);
        // Backstep
        lc3_back(state);
    }
}

/** lc3_next_line
  *
  * Executes the next line blackboxing any subroutines.
  */
void lc3_next_line(lc3_state& state)
{
    // Subroutine depth
    int depth = 0;

    do
    {
        // Get Next Instruction.
        lc3_instr instr = lc3_decode(state, state.mem[state.pc]);
        // So if we get a JSR/JSRR or if we get a TRAP and true traps are enabled
        if (instr.data.opcode == JSR_INSTR || (instr.data.opcode == TRAP_INSTR && state.true_traps))
            depth++;

        // If we get a RET instruction JMP R7
        if (instr.data.opcode == JMP_INSTR && instr.jmp.base_r == 7)
            depth--;

        // If we get an RTI instruction
        if (instr.data.opcode == RTI_INSTR)
            depth--;

        // Execute
        lc3_step(state);

        // If we got interrupted
        if (state.interrupt_enabled && state.undo_stack.back().changes == LC3_INTERRUPT_BEGIN)
            depth++;

    } while (depth != 0 && !state.halted);
}

/** lc3_prev_line
  *
  * Undos the current instruction ignoring subroutines
  */
void lc3_prev_line(lc3_state& state)
{
    // Subroutine depth
    int depth = 0;

    do
    {
        if (!state.undo_stack.empty())
        {
            lc3_state_change& last = state.undo_stack.back();
            // Can't backstep through interrupt
            if (last.changes == LC3_INTERRUPT_BEGIN)
                return;

            // Get rid of all processed interrupts.
            while (last.changes == LC3_INTERRUPT && !state.undo_stack.empty())
            {
                lc3_back(state);
                last = state.undo_stack.back();
            }
        }

        // Execute (Have to do this first you can't assume mem[pc - 1] was the last
        // instruction due to jumps.
        lc3_back(state);
        // Get the instruction that got you where you are.
        lc3_instr instr = lc3_decode(state, state.mem[state.pc]);
        // If we get a RET instruction JMP R7
        if (instr.data.opcode == JMP_INSTR && instr.jmp.base_r == 7)
            depth++;
        // So if we get a JSR/JSRR or if we get a TRAP and true traps are enabled
        if (instr.data.opcode == JSR_INSTR || (instr.data.opcode == TRAP_INSTR && state.true_traps))
            depth--;
        // Don't have to handle interrupts here...
    } while (depth != 0 && !state.halted && !state.undo_stack.empty());
}

/** lc3_finish
  *
  * Finishes the current subroutine
  */
void lc3_finish(lc3_state& state)
{
    // Subroutine depth We assume the user is already in a subroutine and just wants to get out of it
    int depth = 1;

    do
    {
        // Get Next Instruction.
        lc3_instr instr = lc3_decode(state, state.mem[state.pc]);
        // So if we get a JSR/JSRR or if we get a TRAP and true traps are enabled
        if (instr.data.opcode == JSR_INSTR || (instr.data.opcode == TRAP_INSTR && state.true_traps))
            depth++;

        // If we get a RET instruction JMP R7
        if (instr.data.opcode == JMP_INSTR && instr.jmp.base_r == 7)
            depth--;

        // If we got an RTI instruction
        if (instr.data.opcode == RTI_INSTR)
            depth--;

        // Execute
        lc3_step(state);

        // If we got interrupted
        if (state.interrupt_enabled && state.undo_stack.back().changes == LC3_INTERRUPT_BEGIN)
            depth++;
    } while (depth != 0 && !state.halted);
}

/** lc3_interrupt
  *
  * Checks for and processes a single pending interrupt.
  */
void lc3_interrupt(lc3_state& state)
{
    // No interrupts? return.
    if (state.interrupts.empty()) return;

    int my_priority = state.priority;
    int max_priority = -1, max_vector = -1;

    // Try to find a interrupt with higher priority
    std::list<lc3_interrupt_req>::iterator i;
    std::list<lc3_interrupt_req>::iterator max_pos;
    for (i = state.interrupts.begin(); i != state.interrupts.end(); ++i)
    {
        const lc3_interrupt_req& inter = *i;
        // We will be interrupted
        // second case is if we generated an exception.
        if (my_priority < inter.priority || (my_priority == inter.priority && inter.vector < 0x80))
        {
            // You will interrupt the guy interrupting
            if (max_priority < inter.priority)
            {
                max_priority = inter.priority;
                max_vector = inter.vector;
                max_pos = i;
            }
        }
    }

    if (max_priority == -1) return;

    // Interrupt acknowledged.
    state.interrupts.erase(max_pos);

    // HEY PROCESS I'M REALLY HAPPY FOR YOU AND IMMA LET YOU FINISH BUT THIS INTERRUPT HANDLER IS THE BEST HANDLER OF ALL TIME...  OF ALL TIME.
    if (state.privilege) // in user mode
    {
        state.savedusp = state.regs[6];
        state.regs[6] = state.savedssp;
    }
    // push PSR&PC to STACK
    int psr = (state.privilege << 15) | (state.priority << 8) | (state.n << 2) | (state.z << 1) | state.p;
    state.regs[6] -= 2;
    state.mem[state.regs[6] + 1] = psr;
    state.mem[state.regs[6]] = state.pc;

    // Set up new PSR
    state.privilege = 0;
    state.priority = max_priority;
    state.n = 0;
    state.z = 0;
    state.p = 0;

    // Get interrupt vector address contents
    state.pc = state.mem[0x0100 | max_vector];
    if (state.interrupt_vector != -1)
        state.interrupt_vector_stack.push_back(state.interrupt_vector);
    state.interrupt_vector = max_vector;

    lc3_state_change changes;
    changes.changes = LC3_INTERRUPT_BEGIN;
    changes.warnings = state.warnings;
    changes.executions = state.executions;
    // Push this thing back in there as a flag.
    state.undo_stack.push_back(changes);
}

/** lc3_keyboard_interrupt
  *
  * Signals a keyboard interrupt
  */
void lc3_keyboard_interrupt(lc3_state& state)
{
    lc3_signal_interrupt_once(state, 4, 0x80);
}

/** lc3_signal_interrupt
  *
  * Adds an interrupt to be handled to the pending queue.
  * @param priority Priority of the interrupt
  * @param vector Interrupt vector to be accessed when interrupt occurs
  */
void lc3_signal_interrupt(lc3_state& state, int priority, int vector)
{
    lc3_interrupt_req interrupt;
    interrupt.vector = vector;
    interrupt.priority = priority;
    state.interrupts.push_back(interrupt);
}

/** lc3_signal_interrupt_once
  *
  * Adds an interrupt to be handled to the pending queue ONLY if it doesn't already exist.
  * @param priority Priority of the interrupt
  * @param vector Interrupt vector to be accessed when interrupt occurs
  * @return bool true if it was added false otherwise
  */
bool lc3_signal_interrupt_once(lc3_state& state, int priority, int vector)
{
    // Try to find this interrupt
    std::list<lc3_interrupt_req>::iterator i;
    for (i = state.interrupts.begin(); i != state.interrupts.end(); ++i)
    {
        const lc3_interrupt_req& inter = *i;
        if (inter.priority == priority && inter.vector == vector)
        {
            return false;
        }
    }
    lc3_signal_interrupt(state, priority, vector);
    return true;
}

/** lc3_tick_plugins
  *
  *
  *
  */
void lc3_tick_plugins(lc3_state& state)
{
    if (state.instructionPlugin != NULL)
        state.instructionPlugin->OnTick(state);
    for (std::map<unsigned char, TrapFunctionPlugin*>::const_iterator i = state.trapPlugins.begin(); i != state.trapPlugins.end(); ++i)
        if (i->second != NULL)
            i->second->OnTick(state);
    for (std::map<unsigned short, DeviceRegisterPlugin*>::const_iterator i = state.devicePlugins.begin(); i != state.devicePlugins.end(); ++i)
        if (i->second != NULL)
            i->second->OnTick(state);
    for (unsigned int i = 0; i < state.plugins.size(); i++)
        state.plugins[i]->OnTick(state);
}

/** lc3_tock_plugins
  *
  *
  *
  */
void lc3_tock_plugins(lc3_state& state)
{
    if (state.instructionPlugin != NULL)
        state.instructionPlugin->OnTock(state);
    for (std::map<unsigned char, TrapFunctionPlugin*>::const_iterator i = state.trapPlugins.begin(); i != state.trapPlugins.end(); ++i)
        if (i->second != NULL)
            i->second->OnTock(state);
    for (std::map<unsigned short, DeviceRegisterPlugin*>::const_iterator i = state.devicePlugins.begin(); i != state.devicePlugins.end(); ++i)
        if (i->second != NULL)
            i->second->OnTock(state);
    for (unsigned int i = 0; i < state.plugins.size(); i++)
        state.plugins[i]->OnTock(state);
}
