;;===============================
;;HONGRUI ZHENG
;;===============================

.orig x3000
LD R1, A 			;put A in R1
LD R2, B 			;put B in R2
NOT R3, R1 			;put not A in R3
NOT R4, R2 			;put not B in R3
AND R5, R3, R4		;put notA and notB in R5
NOT R5, R5			;put not(notA and notB) in R5
ST R5, ANSWER       ;load the value in r5 into label ANSWER
HALT
A       .fill 6
B       .fill 13
ANSWER  .fill 0	; This answer should contain A | B when finished.
.end
