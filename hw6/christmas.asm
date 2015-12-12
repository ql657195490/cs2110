;;===============================
;;HONGRUI ZHENG
;;===============================

.orig x3000

AND R0, R0, #0 ;clear R0 for future printing
AND R1, R1, #0 ;clear R1 and use it to store the address of the day to print
AND R2, R2, #0 ;clear R2 and use it to store the length of day
AND R3, R3, #0 ;clear R3 
AND R4, R4, #0 ;
AND R5, R5, #0 ;
AND R6, R6, #0 ;

;Printing out first half
LD R2, DAY ;store the length of day in R2
LD R5, DAY ;
ADD R5, R5, #-1 ;
LEA R0, START_MSG_1 ;
PUTS ;print the first message
LEA R4, GRAMMAR_ARR ;
ADD R1, R4, R2 ;find the address of the day to print out
ADD R1, R1, #-1 ;decrement R1 to avoid error and print out the correct day
LDR  R0, R1, 0 ;put the address of the day to print out in RO
PUTS ;print out the day
LEA R0, START_MSG_2
PUTS




;printing out second half
LEA R3, MESSAGE_ARR ;put the address for the start of message array in R2

LOOP
ADD R2, R2, #-1 ;decrement R2 and use it as the condition for loop
BRn END_LOOP ;end the loop if R2 is decreased to less than zero
ADD R6, R3, R5 ;
LDR R0, R6, 0 ;put the address of the sentence in R0 for printing
ADD R5, R5, #-1 ;increment the address in R3 to get the next sentence
PUTS

BR LOOP

END_LOOP
	HALT



DAY	.fill 7

START_MSG_1
	.stringz "On the "

START_MSG_2
	.stringz " day of Christmas my true love gave to me:\n"

GRAMMAR_ARR
	.fill GRAM01
	.fill GRAM02
	.fill GRAM03
	.fill GRAM04
	.fill GRAM05
	.fill GRAM06
	.fill GRAM07
	.fill GRAM08
	.fill GRAM09
	.fill GRAM10
	.fill GRAM11
	.fill GRAM12

MESSAGE_ARR
	.fill MESS01
	.fill MESS02
	.fill MESS03
	.fill MESS04
	.fill MESS05
	.fill MESS06
	.fill MESS07
	.fill MESS08
	.fill MESS09
	.fill MESS10
	.fill MESS11
	.fill MESS12
.end

.orig x5000
GRAM01
	.stringz "first"
GRAM02
	.stringz "second"
GRAM03
	.stringz "third"
GRAM04
	.stringz "fourth"
GRAM05
	.stringz "fifth"
GRAM06
	.stringz "sixth"
GRAM07
	.stringz "seventh"
GRAM08
	.stringz "eighth"
GRAM09
	.stringz "ninth"
GRAM10
	.stringz "tenth"
GRAM11
	.stringz "eleventh"
GRAM12
	.stringz "twelfth"
MESS01
	.stringz "A partridge in a pear tree\n"
MESS02
	.stringz "Two turtle doves\n"
MESS03
	.stringz "Three French hens\n"
MESS04
	.stringz "Four calling birds\n"
MESS05
	.stringz "Five golden rings\n"
MESS06
	.stringz "Six geese a-laying\n"
MESS07
	.stringz "Seven swans a-swimming\n"
MESS08
	.stringz "Eight maids a-milking\n"
MESS09
	.stringz "Nine ladies dancing\n"
MESS10
	.stringz "Ten lords a-leaping\n"
MESS11
	.stringz "Eleven pipers piping\n"
MESS12
	.stringz "Twelve drummers drumming\n"
.end

