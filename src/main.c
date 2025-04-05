// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "numbers.h"
#include "gba.h"
#include "mygbalib.h"


void drawSprite8x8(int numb, int N, int x, int y)
{
    // Gift function: displays sprite number numb on screen at position (x,y), as sprite object N
	 // (x,y) = upper left corner of sprite
	 // numb = number to show on screen
	 // N = when showing multiple number on the screen, must be different for each sprite
	 // 		(eg first sprite = 0, second sprite = 1, ...)
	 // 		moving a sprite -> redrawing with the same N
    *(unsigned short *)(0x7000000 + 8*N) = y | 0x2000;
    *(unsigned short *)(0x7000002 + 8*N) = x;
    *(unsigned short *)(0x7000004 + 8*N) = numb*2;
}

int N = 0; // counter
// NOTE: GBA screen resolution is 240 x 160 -> top left is (0, 0)
// 		each sprite is 8 x 8
int y = SCREEN_HEIGHT / 2 - 4; 	// make sprite vertically centered
int x1 = SCREEN_WIDTH / 2 - 10;	// x position for first digit
int x2 = SCREEN_WIDTH / 2 + 2;	// x position for second dight

void Handler(void)
{
    REG_IME = 0x00; // Stop all other interrupt handling, while we handle this current one
    
	 // NOTE: 3 important registers for interrupts to work
	 // (1) REG_IME (interrupt master enable) -> unless this is set to ‘1’, interrupts will be ignored completely
	 // (2) REG_IE -> to enable a specific interrupt you need to set the appropriate bit in REG_IE
	 // (3) REG_IF -> when an interrupt occurs, the corresponding bit in REG_IF will be set. after handling an interrupt, need to clear the bit again

    if ((REG_IF & INT_TIMER0) == INT_TIMER0) // TODO: replace XXX with the specific interrupt you are handling -> NOTE: make sure it is enabled in REG_IE in main()
    {
        // TODO: Handle timer interrupt her

		  drawSprite(N / 10, 0, x1, y);
		  drawSprite(N % 10, 1, x2, y);
		  N = N + 1;
		  
	 	  if (N >= 100) { // > just in case, shouldn't happen
			 N = 0; // reset counter	
    	  }
    }

    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt`
    
    REG_IME = 0x01;  // Re-enable interrupt handling
}



// -----------------------------------------------------------------------------
// Project Entry Point
// -----------------------------------------------------------------------------
int main(void)
{
	int i;
	
    // Set Mode 2
    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

    // Fill SpritePal
    *(unsigned short *) 0x5000200 = 0;
    *(unsigned short *) 0x5000202 = RGB(31,31,31);

    // Fill SpriteData
    for (i = 0; i < 10*8*8/2; i++)
        spriteData[i] = (numbers[i*2+1] << 8) + numbers[i*2];
    for (i = 0; i < 128; i++)
        drawSprite(0, i, 240, 160);

    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
    REG_IE = INT_TIMER0;	// TODO: complete this line to choose which timer interrupts to enable -> enabled timer 0
    REG_IME = 0x01;			// Enable interrupt handling

    // Set Timer Mode (fill that section and replace TMX with selected timer number)
	
	 // https://gbadev.net/gbadoc/registers.html#timer-registers 
	 // NOTE: 4 frequencies to choose from for GBA timer
	 // (1) 1 cycle (16.78 MHz), i.e., one tick each 59.95 ns
 	 // (2) 64 cycles, i.e., each 3.814 µs
 	 // (3) 256 cycles, i.e., each 15.256 µs
	 // (4) 1024 cycles, i.e., each 61.025 µs
	 
	 // if choose freq 256 cycles:
	 // 	one tick = 15.256 µs -> counter increments every 15.256 µs
	 // 	1 sec = 1 / 15.256E-6 = 65547.98 ticks
	 // 	raise an interrupt when the counter overflows (past 65535)
	 // 	but 65547 > max counter count (65535) so abit mafan (need skip certain interrupt) if use this

	 // if choose freq with 1024 cycles:
	 // 	one tick = 61.025 µs -> counter increments every 61.025 µs
	 // 	1 sec = 1 / 61.025E-6 = 16386.73 ticks
	 // 	raise an interrupt when the counter overflows (past 65535)
	 // 	should start counting at 65535 - 16386 = 49149 = REG_TM0D

    REG_TM0D =	49149;																		// TODO: complete this line to set timer initial value
    REG_TM0CNT |= TIMER_FREQUENCY_1024 | TIMER_ENABLE | TIMER_INTERRUPTS;	// TODO: complete this line to set timer frequency and enable timer
	 // NOTE: TIMER_ENABLE and TIMER_INTERRUPTS and TIMER_FREQUENCY_1024 (or other frequencies) defined in gba.h

    while(1);

	return 0;
}

