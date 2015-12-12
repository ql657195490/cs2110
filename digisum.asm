; ==========================
; CS2110 Lab 13 Fall 2015
; Name: HONGRUI ZHENG
; ==========================

;@plugin filename=lc3_udiv vector=x80

; Main
; Do not edit this function!

.orig x3000

	; Initialize stack
	LD R6, STACK

	; Call digisum(n)
	LD R0, N
	ADD R6, R6, -1
	STR R0, R6, 0
	JSR DIGISUM

	; Pop return value and arg off stack
	LDR R0, R6, 0
	ADD R6, R6, 2

	; Save the answer
	ST R0, ANSWER

	HALT

STACK
	.fill xF000
N
	.fill 45
ANSWER
	.blkw 1

; To call UDIV, use TRAP x80
; Preconditions:
;    R0 = X
;    R1 = Y
; Postconditions:
;    R0 = X / Y
;    R1 = X % Y

DIGISUM

	; TODO Implement this function!
	ADD R6, R6, -3 ;POINTS R6 AT OLD FRAMEPOINTER
	STR R7, R6, 1  ;STORE RETURN ADDRESS
	STR R5, R6, 0  ;STORE OLD FP INTO STACK
	ADD R5, R6, -1 ;CREATE NEW FP WILL POINT ONE ABOVE OLD FP

	ADD R6, R6, -2 ;MAKE ROOM FOR LOCAL VARIABLES
	
	LDR R0, R5, 4  ;R0=N
	AND R1, R1, 0  ;CLEAR R1
	ADD R1, R1, 10 ;SETTING R1 TO TEN
	TRAP x80       ;PERFORM UDIV
	STR R0, R5, 0  ;STORE FIRST LOCAL (DIV)
	STR R1, R5, -1 ;STORE SECOND LOCAL (MOD)
	LDR R0, R5, 4  ;LOAD N
	BRz RET0	   ;IF N == 0

	LDR R0, R5, 0  ;R0 = DIV
	ADD R6, R6, -1 ;
	STR R0, R6, 0  ;STORE FIRST/ONLY ARGUMENT
	JSR DIGISUM
	LDR R0, R6, 0  ;LOAD DIGISUM(DIV)
	LDR R1, R5, -1 ;LOAD MOD
	ADD R2, R0, R1 ;STORE SUM IN R2
	BR RETURN



RET0 
	AND R2, R2, 0  ;RETURN 0
	BR RETURN

RETURN 
	ADD R6, R5, 0  ;POINT SP TO FP
	STR R2, R5, 3  ;STORE RETURN VALUE IN R2
	LDR R7, R5, 2  ;RESTORE RETURN ADDRESS
	LDR R5, R5, 1  ;POINT R5 TO OLD FP
	ADD R6, R6, 3  ;POINT SP TO RETURN VALUE RETURN ADDRESS
	RET

.end
