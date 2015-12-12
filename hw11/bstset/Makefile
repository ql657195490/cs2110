CC = gcc
CFLAGS = -std=c99 -pedantic -Wall -Werror -Wextra
RELEASE_FLAGS = -O2
DEBUG_FLAGS = -g -DDEBUG

run-test : build-release
	./test

run-debug : build-debug
	./test

run-gdb : build-debug
	gdb ./test

run-valgrind : build-debug
	valgrind --leak-check=yes --show-reachable=yes --tool=memcheck ./test

build-release : CFLAGS += $(RELEASE_FLAGS)
build-release : bstset.o test.o bstset.h
	$(CC) $(CFLAGS) test.o bstset.o -o test

build-debug : CFLAGS += $(DEBUG_FLAGS)
build-debug : bstset.o test.o bstset.h
	$(CC) $(CFLAGS) test.o bstset.o -o test

bstset.o : bstset.c bstset.h
	$(CC) $(CFLAGS) -c bstset.c

test.o : test.c bstset.h
	$(CC) $(CFLAGS) -c test.c

clean :
	rm *.o test

submit :
	tar -czf bstset_submission.tar.gz bstset.c
