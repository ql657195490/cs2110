;;===============================
;;HONGRUI ZHENG
;;===============================

.orig x3000
AND R1, R1, #0 ;CLear R1, use as sum
LD R3, ARRAY ;Use R3 to store the address of the array and increment this later to loop through the array
ADD R3, R3, #-1 ;Decrement to avoid error later
LD R2, LENGTH ;Load the length of the array in R3 to decrement later and use as loop conditions
LOOP
	ADD R3, R3, #1 ;increment the address to loop through the array
	LDR R4, R3, 0 ;put value of current address into R4 to do the actual calculations
	ADD R2, R2, #-1 ;Decrement the length as a condition for loop
	BRn END_LOOP ;End loop if R2 is decreased to be less than zero
	ADD R1, R1, R4 ;add the number at the address R3 to the sum in R1
	
	BR LOOP

END_LOOP
ST R1, ANSWER
BRn ABS
HALT
ABS
	NOT R1, R1 ;
	ADD R1, R1, #1 ;Negation of 2's complement number stored in R1 if it is negative
	BR END_LOOP


	ST R1, ANSWER
	HALT

ARRAY   .fill x6000
LENGTH  .fill 10
ANSWER	.fill 0		; The answer should have the abs(sum) when finished.
.end

.orig x6000
.fill 8
.fill 9
.fill 7
.fill 0
.fill -3
.fill -11
.fill -9
.fill -9
.fill 2
.fill 9
.end
