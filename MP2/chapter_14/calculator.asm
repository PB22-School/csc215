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
        DB      'INPUT FIRST NUMBER:', CR, LF, 0
        CALL    CIMSG
        CALL    CCRLF

        CALL    BUFBIN
        MOV     C, B    ; FIRST NUMBER -> C

        CALL    CCRLF
        CALL    SPMSG
        DB      'INPUT SECOND NUMBER:', CR, LF, 0
        CALL    CIMSG
        CALL    CCRLF

        CALL    BUFBIN  ; SECOND NUMBER -> D
        MOV     D, B

        ;JMP     RBOOT

        CALL    CCRLF
        CALL    SPMSG
        DB      'TYPE YOUR CHOICE:', CR, LF, CR, LF, '1) ADD', CR, LF, '2) SUBTRACT', CR, LF, '3) MULTIPLY', CR, LF, '4) DIVIDE', CR, LF, CR, LF, 'CHOICE: ',0
        CALL    CIMSG

        CALL    BUFBIN
        CALL    CCRLF
        CALL    CCRLF

        MOV     A, B

        CPI     1
        JZ      STARTADD

        CPI     2
        JZ      STARTSUB

        CPI     3
        JZ      STARTMULT

        CPI     4
        JZ      STARTDIV

        JMP     RBOOT

STARTADD:

        MOV     A, C
        ADD     D

        PUSH    A

        CALL    SPMSG
        DB      'RESULT OF ADDITION: ', 0

        JMP     STARTDONE

STARTSUB:

        MOV     A, C
        SUB     D

        PUSH    A

        CALL    SPMSG
        DB      'RESULT OF SUBTRACTION: ', 0

        JMP     STARTDONE

STARTMULT:

        MOV     A, C
        MOV     B, D

        CALL    MULTIPLY

        PUSH    A

        CALL    SPMSG
        DB      'RESULT OF MULTIPLICATION: ', 0

        JMP     STARTDONE

STARTDIV:

        MOV     A, C
        MOV     B, D

        CALL    DIVIDE

        MOV     C, A    ; RESULT  -> C
        MOV     D, B    ; MODULUS -> D

        CALL    SPMSG
        DB      'RESULT OF DIVISION: ', 0

        MOV     A, C

        CALL    BINBUFASCII

        LXI     H, INBUF+2
        CALL    COMSG
        CALL    CCRLF

        CALL    SPMSG
        DB      'WITH REMAINDER: ', 0

        MOV     A, D
        PUSH    A

STARTDONE:

        POP     A

        CALL    BINBUFASCII

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

; PRINTS A NEW LINE
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
        PUSH    B
        MVI     C, 0    ; COUNTER
        MVI     D, 0    ; SUM
        MOV     E, A

        ADDLOOP:

        INR     C
        MOV     A, D
        ADD     B
        MOV     D, A

        CMP     E
        
        JZ      DIVE    ; (D+B) = E?
        JNC     DIVNE   ; (D+B) > E?
        JMP     ADDLOOP

        DIVNE:

        ; GREATER THAN
        DCR     C
        MOV     A, E
        ADD     B
        SUB     D
        MOV     E, A

        JMP     DEBRANCH

        DIVE:

        ; EQUAL
        MVI     E, 0

        DEBRANCH:
        
        MOV     A, C
        POP     B
        MOV     B, E

        POP     D       
        RET

; BUFFER -> REFFUB
BUFFREV:

        PUSH    B
        PUSH    D

        LXI     H, INBUF+1

        MOV     C, M
        MVI     B, 0

        INR     C

        REVLOOP:

        INX     H
        PUSH    H

        DCR     C
        DCR     C

        ; ; DEBUG
        ; MOV     A, C
        ; CALL    TOASCII
        ; CALL    CO
        ; MVI     A, ':'
        ; CALL    CO
        ; MOV     A, C
        ; ANI     7FH
        ; CALL    CO
        ; CALL    CCRLF
        ; ; DEBUG

        MOV     A, C
        CPI     0
        ;DCR     C

        JZ      REVDONE
        JM      REVDONE
        MOV     D, M
        DAD     B
        MOV     A, M
        MOV     M, D

        POP     H
        MOV     M, A

        JMP     REVLOOP

        REVDONE:

        POP     H

        POP     D
        POP     B
        RET

; INBUF (ASCII) -> B (BINARY)
BUFBIN:

        LXI     H, INBUF+1
        MVI     B, 0

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
BINBUFASCII:

        PUSH    A
        PUSH    B
        PUSH    D

        LXI     H, INBUF+2
        MVI     C, 0

        ; CALL    CO

        BASCIILOOP:

        MVI     B, 10
        CALL    DIVIDE

        ; A = INT(A / B)
        ; B = A % B

        MOV     D, A

        MOV     A, B
        CALL    TOASCII
        MOV     M, A

        INX     H
        INR     C
        
        MOV     A, D

        ORA     A
        JNZ     BASCIILOOP

        MVI     M, 0
        LXI     H, INBUF+1
        MOV     M, C

        CALL    BUFFREV

        POP     D
        POP     B
        POP     A

        RET


DS      64
STAK:   DB      0

INBUF:  DS      83
        END