CS2110-malloc-grader
====================

The rewritten autograder for the malloc assignment in CS2110.

Currently, the GNUMakefile should be edited to point to the student-to-grade's folder with the submission inside.
Right now it's set to just ..
so, you can just run make. The results will both be printed out and put in a graded.txt

You should also edit grader.c to put your own name in for GRADER_NAME.

The rewritten grader is designed a bit differently from the original - instead of catching segfault signals and then jumping back after the test, we run tests in separate processes.
We do this so that student's code and segfaults cannot possibly corrupt the main grading thread.
To run a paticular test, the main grading process popen's itself with a numeric argument (./grader 2) which runs that test and prints the results on standard out.
The main grading process reads the stdout of its children processes and adds up the points gained.

It will print some information to stdout and write the results to "graded.txt", or whatever name you put in as FILE_NAME in grader.c.

If you want to add additional test cases, you can just edit the tests.c/h files to add additional functions. Note in test.h how to add it to the macro list. Also note that the way most of the current test functions are structured is to have one general test function that takes a function pointer to a malloc and a free, and then two stub functions that call the genearl function with the size_order and addr_order versions respectively, and these stub functions are what get added to the tests.h. (so we don't have to write large seperate functions for both size_order and addr_order.)

