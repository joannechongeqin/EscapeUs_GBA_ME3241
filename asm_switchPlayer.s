.GLOBL switchPlayer
.extern activePlayerIndex
.extern players     

@ --- C code version in player.c ---
@ void switchPlayer() {
@     playerStop(); // stop current player before switching
@     int originalIndex = activePlayerIndex;
@     do {
@         activePlayerIndex = (activePlayerIndex + 1) % NUM_PLAYERS;
@     } while (players[activePlayerIndex].enteredGoal && activePlayerIndex != originalIndex);
@ }


switchPlayer:
    swp     r4, r4, [sp]	        @ Pop last input argument from stack and put it in r4
    stmfd   sp!, {r4-r11, lr}       @ Save content of r4-r11 and link register into the sp register

    @ --- start of main function code ---

    BL  playerStop                  @ call playerStop()

    LDR r1, =activePlayerIndex      @ r1 = address of activePlayerIndex     -> cuz activePlayerIndex is a variable so =activePlayerIndex returns an address 
    LDR r2, [r1]                    @ r2 = originalIndex                    -> go to r1 and load the value at that address into r2
    MOV r3, #2            			@ r3 = NUM_PLAYERS = 2 in our case      -> cuz NUM_PLAYERS is a #define constant so this has to be hardcoded
    LDR r4, =players                @ r4 = base address of Player[] array
    MOV r5, #32                     @ r5 = size of a Player struct (8 int x 4 bytes/int = 32 bytes)
	LDR r6, [r1]					@ r6 = candidateIndex

loop:
    ADD r6, r6, #1                  @ candidateIndex = candidateIndex + 1

    @ following two lines are for r6 = (activePlayerIndex + 1) % NUM_PLAYERS -> ARM assembly does not have a direct MOD instruction
    CMP   r6, r3                    @ compare candidateIndex with NUM_PLAYERS
    MOVEQ r6, #0                    @ wrap around and set r6 to 0 if candidateIndex == NUM_PLAYERS

    STR  r6, [r1]                   @ store new activePlayerIndex

    MUL  r7, r6, r5                 @ r7 = activePlayerIndex * size of Player struct
    ADD  r8, r4, r7                 @ r8 = address of players[activePlayerIndex]
    LDR  r9, [r8, #28]              @ load players[activePlayerIndex].enteredGoal (8th attribute, offset 28 in struct)

    CMP  r9, #0                     @ enteredGoal == 0 means valid switch, exit
    BEQ  done

    CMP  r6, r2                     @ exit if cycled back to originalIndex
    BEQ  done

    B    loop                       @ loop again

    @ --- end of main function code ---

done:
    @ Exit from function
    ldmfd   sp!, {r4-r11, lr}       @ Recover past state of r4-r11 and link register from sp register
    swp     r4, r4, [sp]			@ Restore state of r4
    mov     pc, lr				    @ Branch back to lr (go back to C code that called this function)

