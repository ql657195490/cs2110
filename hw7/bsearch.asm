;;===============================
;;Name: HONGRUI ZHENG
;;===============================

; Main
; Do not edit this function!

;@plugin filename=lc3_udiv vector=x80

.orig x3000

	LD R6, STACK	; Initialize stack pointer

	LD R0, ARR_PTR	; \ Load parameters
	AND R1, R1, 0	; |
	LD R2, ARR_LEN	; |
	ADD R2, R2, -1	; |
	LD R3, X	; /

	ADD R6, R6, -4	; \ Call BSEARCH
	STR R0, R6, 0	; |
	STR R1, R6, 1	; |
	STR R2, R6, 2	; |
	STR R3, R6, 3	; |
	JSR BSEARCH	; /

	LDR R0, R6, 0	; \ Pop return value and args off the stack
	ADD R6, R6, 5	; /

	ST R0, ANSWER

	HALT

STACK   .fill xF000 ; Bottom of the stack + 1
ARR_PTR .fill x6000 ; Pointer to the array of elements
ARR_LEN .fill 16
X       .fill 99    ; What to search for
ANSWER  .fill -999  ; Do NOT write to this label from the subroutine!


; To call UDIV, use TRAP x80
; Preconditions:
;    R0 = X
;    R1 = Y
; Postconditions:
;    R0 = X / Y
;    R1 = X % Y

BSEARCH
	ADD R6, R6, -3  ; POINTS R6 TO OLD FP
	STR R7, R6, 1   ; STORE RA
	STR R5, R6, 0   ; STORE OLD FP
	ADD R5, R6, -1  ; CREATE NEW FP POINTING ONE ABOVE OLD FP

	ADD R6, R6, -1  ; MAKE ROOM FOR LOCAL VAR MID
	AND R4, R4, 0   ; CLEAR R4
	STR R4, R6, 0   ; SET MID TO ZERO

	LDR R0, R5, 5   ; PUT LOW IN R0
	LDR R1, R5, 6   ; PUT HIGH IN R1
	LDR R3, R5, 4   ; PUT ARR_PTR IN R3

	NOT R2, R0
	ADD R2, R2, 1   ; NEGATING LOW
	ADD R2, R2, R1  ; COMPARING LOW AND HIGH
	BRn RETNEG1

	ADD R0, R0, R1  ; LOW + HIGH
	AND R1, R1, 0   ; CLEARING R1
	ADD R1, R1, 2   ; SET R1 TO 2
	TRAP x80        ; PERFORMING UDIV, (LOW+HIGH)/2
	STR R0, R5, 0   ; STORING LOCAL (DIV OR MID)

	LDR R0, R5, 0   ; GET MID
	ADD R0, R0, R3  ; GET ADDRESS OF MID
	LDR R0, R0, 0   ; GET ARR[MID]
	LDR R1, R5, 7   ; GET X
	NOT R2, R0
	ADD R2, R2, 1   ; NEGATING ARR[MID]
	ADD R2, R2, R1  ; X-ARR[MID]
	BRz FOUND		; ANSWER FOUND IF X == ARR[MID]
	BRp XBIGGER
	LDR R0, R5, 4   ; PUT ARR_PTR IN R0
	LDR R1, R5, 5   ; PUT LOW IN R1
	LDR R2, R5, 7   ; PUT X IN R2
	LDR R3, R5, 0   ; PUT MID IN R3
	ADD R3, R3, -1   ; PUT MID - 1 IN R3

	ADD R6, R6, -4  ;
	STR R2, R6, 3   ; PUSH X INTO STACK
	STR R3, R6, 2   ; PUSH MID-1 INTO STACK
	STR R1, R6, 1   ; PUSH LOW INTO STACK
	STR R0, R6, 0   ; PUSH ARR_PTR INTO STACK
	
	JSR BSEARCH		; CALL BSEARCH(ARRAY, LOW, MID-1, X)
	BR RETURN

RETNEG1
	AND R0, R0, 0   ; CLEARING R0
	ADD R0, R0, -1  ; SETTING ANSWER TO -1
	BR RETURN

FOUND
	LDR R0, R5, 0   ; GET MID
	BR RETURN

XBIGGER
	LDR R0, R5, 4   ; PUT ARR_PTR IN R0
	LDR R1, R5, 6   ; PUT HIGH IN R1
	LDR R2, R5, 7   ; PUT X IN R2
	LDR R3, R5, 0   ; PUT MID IN R3
	ADD R3, R3, 1   ; PUT MID + 1 IN R3

	ADD R6, R6, -4  ;
	STR R2, R6, 3   ; PUSH X INTO STACK
	STR R1, R6, 2   ; PUSH HIGH INTO STACK
	STR R3, R6, 1   ; PUSH MID+1 INTO STACK
	STR R0, R6, 0   ; PUSH ARR_PTR INTO STACK
	
	JSR BSEARCH		; CALL BSEARCH(ARRAY, MID+1, HIGH, X)
	BR RETURN

RETURN
	ADD R6, R5, 0   ; POINT SP TO FP
	STR R0, R5, 3   ; STORE RETURN VALUE IN R2
	LDR R7, R5, 2   ; RESTORE RETURN ADDRESS
	LDR R5, R5, 1   ; POINT R5 TO OLD FP
	ADD R6, R6, 3   ; POINT SP TO RETURN VALUE
	RET

.end

.orig x6000

	.fill -45
	.fill -42
	.fill -30
	.fill -2
	.fill 6
	.fill 15
	.fill 16
	.fill 28
	.fill 51
	.fill 78
	.fill 99
	.fill 178
	.fill 200
	.fill 299
	.fill 491
	.fill 5103

.end

