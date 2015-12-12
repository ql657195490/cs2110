;===========================
; Name: HONGRUI ZHENG
;===========================

.orig x3000
LEA R1, HELLO ;store the address of the start of the string to increment and loop through later
ADD R1, R1, #-1 ;
LOOP
	ADD R1, R1, #1 ;increment the address to get the next letter
	LDR R0, R1, 0 ;put the letter into R0
	BRz END_LOOP ;end loop if R0 is not positive
	OUT ;print the letter stored in R0	
	BR LOOP ;
END_LOOP
	HALT
HELLO	.stringz "Hello, world!"

.end

