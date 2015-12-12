# Makefile for CS 2110 sorting lab

PROGNAME = sort
SRC = sort.c
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Werror -std=c99 -pedantic -Wextra -g
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
