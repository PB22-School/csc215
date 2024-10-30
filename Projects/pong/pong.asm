; stack_pointer = 0xff00
; for simplicity's sake, we're gonna put all of the game data really close to each other:
;
; PLAYER_1:
; y_1    = 0x00f0 ; the bottom of the paddle
; vsp_1  = 0x00f1 
;
; PLAYER_2:
; y_2    = 0x00f2
; vsp_1  = 0x00f3
;
; BALL:
; ball_x = 0x00f4
; hsp_b  = 0x00f5
; ball_y = 0x00f6
; vsp_b  = 0x00f7
;
; SCORE:
; player_1_score = 0x00f8
; player_2_score = 0x00f9
;
; CONSTANTS:
; distance = 0xff
; paddle_length = 0x0f
; random_number = 0xee00
; 
; first we want to set the stack pointer. We'll put it at ff00.

JMP the_start

.clock
    MVI(E,0x0e)
    MVI(D,0x00)
    INX(BC) ; jump_point
    MOV(B->A)
    CMP(D)
    MOV(A->B)
    JNZ jump_point
    MOV(C->A)
    CMP(D)
    MOV(A->C)
    JNZ jump_point
    INR(A)
    CMP(E)
    JNZ jump_point
    RET

.ball_move
    LDA ball_x
    MOV(A->B)
    LDA hsp_b
    ADD(B)
    STA ball_x
    LDA ball_y
    MOV(A->B)
    LDA vsp_b
    ADD(B)
    STA ball_y
    ; checks if a collision with a paddle has occured
    LDA ball_x
    MVI(B, distance)
    CMP(B) ; if B is greater than A, the carry bit will be set
    RNC ; so if the carry bit is set, the ball overlapped, so DON'T return

    MVI(E, paddle_length)
    LDA y_1
    MOV(A->B)
    LDA y_2
    MOV(A->D)
    LDA ball_y
    CMP(B)
    RNC
    CMP(D)
    RNC
    SUB(E)
    CMP(B)
    RNC
    CMP(D)
    RNC ; after this long thing we are sure that the ball collided with a paddle
    LDA hsp_b ; now we change the direction of the ball.
    MVI(C, 0xff)
    CMP(C)
    MVI(A, 0xff)
    JNZ after
    MVI(A, 0x01)
    STA hsp_b ; after
    LDA vsp_b
    CMP(C)
    JNZ after_2
    MVI(A, 0x01)
    MVI(A, 0xff) ; after_2
    RET

.check_score
    LDA ball_x
    MOV(A->B)
    MVI(A, distance)
    CMP(B) ; reg > A -> Carry
    RNC
    

MVI(H, 0xFF) ; the_start
MVI(L, 0x00)

MVI(E, 0x01)
LDA random_number
ANA(E)
MVI(A, 0x01)
JNZ after
MVI(A, 0xff)
STA hsp_b ; after

MVI(E, 0x02)
LDA random_number
ANA(E)
MVI(A, 0x01)
JNZ after_2
MVI(A, 0xff)
STA vsp_b ; after_2

.ball_move() ; loop
.check_score() ;
.clock()
JMP loop