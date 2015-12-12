;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Your Name Here: HONGRUI ZHENG
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

        .orig x3000

        LD R6, STACK
        LD R0, N
        ADD R6, R6, -1 
        STR R0, R6, 0 
        JSR ODD_SUM
        LDR R1, R6, 0
        ADD R6, R6, 2
        ST R1, ANSWER
        HALT

STACK   .fill xF000
N       .fill 10
ANSWER  .fill 999


ODD_SUM 
        ADD R6, R6, -3  ; POINT R6 TO OLDFP
        STR R7, R6, 1   ; STORE RETURN ADDRESS
        STR R5, R6, 0   ; STORE OLDFP ONTO STACK
        ADD R5, R6, -1  ; CREATE NEWFP POINTS ONE UP OLDFP


        LDR R0, R5, 4   ; R0 = N
        BRnz RET0       ; IF N <= 0 RETURN ZERO


        AND R0, R0, 1   ;
        BRz RETSUM
        BR RETSUMPLUSN

RETSUM
        LDR R0, R5, 4   ;
        ADD R0, R0, -1  ; N-1
        ADD R6, R6, -1  ;
        STR R0, R6, 0   ; ODD_SUM(N - 1)
        JSR ODD_SUM
        BR RETURN

RETSUMPLUSN
        LDR R0, R5, 4
        ADD R0, R0, -1  ; N-1
        ADD R6, R6, -1  ;
        STR R0, R6, 0   ; ODD_SUM(N - 1)
        JSR ODD_SUM
        LDR R3, R5, 4
        ADD R2, R2, R3
        BR RETURN

RET0
        AND R2, R2, 0   ; SETTING R2 = 0
        BR RETURN


RETURN 
        ADD R6, R5, 0  ;POINT SP TO FP
        STR R2, R5, 3  ;STORE RETURN VALUE IN R2
        LDR R7, R5, 2  ;RESTORE RETURN ADDRESS
        LDR R5, R5, 1  ;POINT R5 TO OLD FP
        ADD R6, R6, 3  ;POINT SP TO RETURN VALUE RETURN ADDRESS
        RET


        .end
