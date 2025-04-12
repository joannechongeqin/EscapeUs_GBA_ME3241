// -----------------------------------------------------------------------------
// C-Skeleton to be used with HAM Library from www.ngine.de
// -----------------------------------------------------------------------------
#include "game.h"

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
    // Set Mode 2
    *(unsigned short *) 0x4000000 = 0x40 | 0x2 | 0x1000;

    fillPalette();
    fillSprites();

    // testLetters();

    // initialize game
    gameState = MAIN_MENU;
    showMainMenu();

    // Set Handler Function for interrupts and enable selected interrupts
    REG_INT = (int)&Handler;
    REG_IE = INT_TIMER0;	// choose which timer interrupts to enable -> enabled timer 0
    REG_IME = 0x01;			// Enable interrupt handling

    // Set Timer Mode
    // --> TIMER_FREQUENCY_1024 --> 61.025 micro seconds per tick
    // --> interrupt every 100 Hz (10 ms) --> 0.01 s / (61.025e-6) = 164 ticks
    REG_TM0D = 65208 - 164;													// set timer initial value
    REG_TM0CNT |= TIMER_FREQUENCY_1024 | TIMER_ENABLE | TIMER_INTERRUPTS;	// set timer frequency and enable timer

    while(1);

	return 0;
}
