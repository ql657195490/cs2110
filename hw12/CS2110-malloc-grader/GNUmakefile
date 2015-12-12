CC := gcc
CFLAGS := -std=gnu99 -Wall -g -lm
OPTFLAG := -g

STUDENT := ..#$(error Must set STUDENT to the directory containing the submission)

GRADERFILES := tests.o grader.o
HFILES := my_malloc.h malloc_common.h tests.h grader.h

grade: grader
	./grader
	mv graded.txt "$(STUDENT)"

# Override what the student has!
LIBRARY := malloc
export CC CFLAGS OPTFLAG LIBRARY

$(STUDENT): 
	$(MAKE) -f Makefile -C "$(STUDENT)" libmalloc.a -lm 

grader: $(GRADERFILES) $(STUDENT)
	$(CC) $(CFLAGS) -L "$(STUDENT)" $(GRADERFILES) -lmalloc -o $@ -lm
%.o: %.c $(HFILES)
	$(CC) $(CFLAGS) $(OPTFLAG) $< -c -o $@ -lm

clean:
	rm -f $(GRADERFILES) grader

.PHONY: clean $(STUDENT)
