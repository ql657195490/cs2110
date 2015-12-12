.orig x3000
LEA R1, GRAMMAR_ARR
LDR R0, R1, 0
PUTS
HALT



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
