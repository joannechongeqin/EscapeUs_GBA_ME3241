// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "gba.h"
#include "mygbalib.h"


// NOTE: GBA screen resolution is 240 x 160 -> top left is (0, 0)

void Handler(void)
{
    REG_IME = 0x00; // Stop all other interrupt handling, while we handle this current one

    if ((REG_IF & INT_TIMER0) == INT_TIMER0) // specify the interrupt you are handling -> NOTE: make sure it is enabled in REG_IE in main()
    {
		checkbutton();
    }

    REG_IF = REG_IF; // Update interrupt table, to confirm we have handled this interrupt
    
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

	fillPalette();
	fillSprites();

    // // Fill SpritePal
    // *(unsigned short *) 0x5000200 = 0;
    // *(unsigned short *) 0x5000202 = RGB(31,31,31);

    // // Fill SpriteData
    // for (i = 0; i < 10*8*8/2; i++)
    //     spriteData[i] = (numbers[i*2+1] << 8) + numbers[i*2];
    // for (i = 0; i < 128; i++)
    //     drawSprite(0, i, 240, 160);

    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
    REG_IE = INT_TIMER0;	// choose which timer interrupts to enable -> enabled timer 0
    REG_IME = 0x01;			// Enable interrupt handling

    // Set Timer Mode
	// --> TIMER_FREQUENCY_1024 --> 61.025 µs per tick
	// --> interrupt every 50 Hz (20 ms) --> 0.02 s / (61.025e-6) = 328 ticks
    REG_TM0D = 65208 - 328;													// set timer initial value
    REG_TM0CNT |= TIMER_FREQUENCY_1024 | TIMER_ENABLE | TIMER_INTERRUPTS;	// set timer frequency and enable timer
	// NOTE: TIMER_ENABLE and TIMER_INTERRUPTS and TIMER_FREQUENCY_1024 (or other frequencies) defined in gba.h

    while(1);

	return 0;
}


