;;===============================
;;Name: HONGRUI ZHENG
;;===============================

.orig x3000
LD R2, LENGTH ;put the length in R2
OUTER 
	LD  R1, ARRAY ;Put the address of the start of the array in R1
    LD  R6, #1 ;set R6 to one to use as isSorted
    AND R0, R0, #0 ;clear R0 to avoid errors
    ADD R0, R0, R2 ;put length of array in R0
INNER
	ADD R0, R0, #-1 ;use as first index to loop through in the outer for loop
    BRnz TEST1 ;if R0 <= 0, skip the next few lines to TEST1
    LDR R3, R1, #0 ;R3 = ARRAY[R1], getting the R1th element in array
	LDR R4, R1, #1 ;R4 = ARRAY[R1 + 1], getting the R1+1th element in array
	;Add the first element and the negation of the second element, if 
	;the sum is less than or equal to zero, it means the prior one is
	;larger than the latter one no matter the sign of the elements
	NOT R5, R4 ;
	ADD R5, R5, #1 ;Negating R4 and store it in R5
	ADD R5, R3, R5 ;
	BRnz TEST2 ;if R3 <= R4, skip the next few lines to TEST2
	;flipping two elements
	STR R4, R1, #0 ;ARRAY[R1] = R4
	STR R3, R1, #1 ;ARRAY[R1 + 1] = R3
    AND R6, R6, #0 ;Clearing R6
TEST2 
	;process next two elements
	ADD R1, R1, #1 ;Increment R1
    BR  INNER ;Loop back to INNER
TEST1 
	AND R6, R6, #1     
    BRz TEST3 ;if R6 != 1, finish the program
    BR END         
TEST3 
	ADD R2, R2, #-1 ;Decrement R2
    BRp OUTER ;if R2 > 0, loop back to AGAIN
END 
	HALT

ARRAY   .fill x6000
LENGTH  .fill 12
.end

; This array should be sorted when finished.
.orig x6000
.fill 28
.fill -50
.fill 7
.fill 2
.fill 42
.fill 4
.fill 15
.fill -8
.fill 34
.fill 101
.fill -5
.fill 250
.end

