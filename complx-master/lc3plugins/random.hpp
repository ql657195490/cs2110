#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <lc3_plugin.hpp>
#include <lc3_parser.hpp>

#define RANDOM_MAJOR_VERSION 1
#define RANDOM_MINOR_VERSION 3

class RandomPlugin : public DeviceRegisterPlugin
{
    public:
        RandomPlugin(unsigned short address, unsigned int seed);
        ~RandomPlugin();
        virtual short OnRead(lc3_state& state);
        virtual void OnWrite(lc3_state& state, short value);
        unsigned int seed;
};

extern "C" Plugin* create_plugin(const std::map<std::string, std::string>& params);
extern "C" void destroy_plugin(Plugin* ptr);

#endif

