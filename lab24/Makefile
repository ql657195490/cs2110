# Makefile for CS 2110 stack smashing lab

PROGNAME = hex2ascii
SRC = hex2ascii.c
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -std=c99 -pedantic -Wextra -g -fno-stack-protector
LFLAGS =

all : $(OBJ)
	@echo "[LINK] Linking $(PROGNAME)"
	@gcc -o $(PROGNAME) $^ $(LFLAGS)

%.o : %.c
	@echo "[COMPILE] Compiling $@"
	@gcc $(CFLAGS) -c $< -o $@

clean :
	@echo "[CLEAN] Removing all compiled files"
	@rm -f *.o $(PROGNAME)
