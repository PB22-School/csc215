CR      EQU     0DH
LF      EQU     0AH
CTRLZ   EQU     1AH

RCONF   EQU     1
WCONF   EQU     2
RBUFF   EQU     10

RBOOT   EQU     0
BDOS    EQU     5
TPA     EQU     100H


ORG TPA

START:  
        LXI     SP, STAK

START1: 
        CALL    SPMSG
        DB      'FIRST NUMBER:', CR, LF, 0
        CALL    CIMSG

        CALL    BUFBIN
        MOV     C, B

        CALL    CCRLF
        CALL    SPMSG
        DB      'SECOND NUMBER:', CR, LF, 0
        CALL    CIMSG

        CALL    BUFBIN
        MOV     A, C

        CALL    BUFASCII

        CALL    CCRLF
        LXI     H, INBUF+2
        CALL    COMSG
        CALL    CCRLF

        JMP     RBOOT

; CONSOLE CHARACTER TO REGISTER A MASKED WITH 7 BITS
CI:
        PUSH    B
        PUSH    D
        PUSH    H
        MVI     C, RCONF
        CALL    BDOS
        ANI     7FH
        POP     H
        POP     D
        POP     B
        RET

; CHARACTER IN REGISTER A OUTPUTTED TO CONSOLE
CO:
        PUSH    B
        PUSH    D
        PUSH    H
        MVI     C, WCONF
        MOV     E, A
        CALL    BDOS
        POP     H
        POP     D
        POP     B
        RET

CCRLF:
        MVI     A, CR
        CALL    CO
        MVI     A, LF
        JMP     CO

; MESSAGE POINTED TO BY HL
COMSG:
        MOV     A, M
        ORA     A
        RZ
        CALL    CO
        INX     H
        JMP     COMSG

; INPUT CONSOLE MESSAGE TO BUFFER
CIMSG:
        PUSH    B
        PUSH    D
        PUSH    H
        LXI     H, INBUF+1
        MVI     M, 0
        DCX     H
        MVI     M, 80
        XCHG
        MVI     C, RBUFF
        CALL    BDOS
        LXI     H, INBUF+1
        MOV     E, M
        MVI     D, 0
        DAD     D
        INX     H
        MVI     M, 0
        POP     H
        POP     D
        POP     B
        RET

; MESSAGE POINTED TO BY STACK OUT TO CONSOLE
SPMSG:
        XTHL
        XRA     A
        ADD     M
        INX     H
        XTHL    
        RZ
        CALL    CO
        JMP     SPMSG

; ASCII (A) -> BINARY (A)
TOBIN:
        CPI     '0'
        JC      TOBINRET        ; A < 48 (0)?
        CPI     ':'             ; A > 58 (':' = '9' + 1)?
        JNC     TOBINRET
        SUI     '0'             ; DE-OFFSETS BY ASCII 0
        RET

        TOBINRET:

        MVI     A, 1
        RET

; BINARY (A) -> ASCII (A)
TOASCII:
        CPI     0
        JC      TOASCIIRET        ; A < 0?
        CPI     10
        JNC     TOASCIIRET        ; A > 9?
        ADI     '0'               ; OFFSETS BY ASCII 0
        RET

        TOASCIIRET:

        MVI     A, '?'
        RET

; DEBUG PRINT
DBGPR:
        PUSH    A

        CALL    CCRLF

        MVI     A, 'B'
        CALL    CO
        CALL    CCRLF
        MOV     A, B
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, B
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        MVI     A, 'C'
        CALL    CO
        CALL    CCRLF
        MOV     A, C
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, C
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        MVI     A, 'D'
        CALL    CO
        CALL    CCRLF
        MOV     A, D
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, D
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        MVI     A, 'E'
        CALL    CO
        CALL    CCRLF
        MOV     A, E
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, E
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        MVI     A, 'H'
        CALL    CO
        CALL    CCRLF
        MOV     A, H
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, H
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        MVI     A, 'L'
        CALL    CO
        CALL    CCRLF
        MOV     A, L
        CALL    TOASCII
        CALL    CO
        CALL    CCRLF
        MOV     A, L
        CALL    CO
        CALL    CCRLF
        CALL    CCRLF

        POP     A
        RET
        
; A = A * B
MULTIPLY:
        
        PUSH    B
        PUSH    D
        MVI     C, 1
        MVI     D, 0
        MOV     E, A

        LOOP:

        MOV     A, E
        ANA     C

        JZ      NOINC
        MOV     A, D
        ADD     B
        MOV     D, A

        NOINC: 
        MOV     A, B
        RAL
        STC
        CMC
        MOV     B, A
        MOV     A, C
        RAL
        MOV     C, A

        JNC     LOOP
        MOV     A, D
        POP     D
        POP     B
        RET

; A = INT(A / B)
; B = A % B
DIVIDE:

        PUSH    D
        MVI     C, 0    ; COUNTER
        MVI     D, 0    ; SUM
        MOV     E, A

        ADDLOOP:

        INR     C
        MOV     A, D
        ADD     B
        MOV     D, A

        CMP     E

        JNC     DIVNE   ; (D+B) > E?
        JZ      DIVE    ; (D+B) = E?
        JMP     ADDLOOP

        DIVNE:

        DCR     C

        DIVE:

        MOV     A, D
        SUB     B
        MOV     B, A    ; B = D - B
        MOV     A, E
        SUB     B
        MOV     B, A    ; B = E - (D - B)
        MOV     A, C    ; A = C
        POP     D       
        RET



; INBUF (ASCII) -> B (BINARY)
BUFBIN:

        LXI     H, INBUF+1
        MVI     B, 0

        ; MAYBE CR + LF IS IN HERE???
        ; MAYBE DOESN'T MATTER, MAYBE HAVE TO MAKE OTHER CHARS = 0

        BUFLOOP:

        INX     H
        MOV     A, M
        ORA     A
        RZ
        MVI     A, 10
        CALL    MULTIPLY
        MOV     B, A
        MOV     A, M
        CALL    TOBIN
        ADD     B
        MOV     B, A

        JMP     BUFLOOP

; A (BINARY) -> INBUF (ASCII)
BUFASCII:

        LXI     H, INBUF+1
        MVI     C, 0
        PUSH    A

        LENGTHLOOP:
        MVI     B, 1O
        CALL    DIVIDE
        INR     C
        ORA     A
        JNZ     LENGTHLOOP

        POP     A

        INX     H
        MVI     M, 0

        LXI     H, INBUF+2
        MVI     B, 0
        DAD     B

        BASCIILOOP:

        MVI     B, 10
        CALL    DIVIDE
        PUSH    A

        MOV     A, B
        CALL    TOASCII

        DCX     H
        MOV     M, A

        POP     A

        ORA     A

        JNZ     BASCIILOOP

        ;INX     H
        ;MVI     M, 10
        RET

DS      64
STAK:   DB      0

INBUF:  DS      83
        END