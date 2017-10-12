/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Button Based Delay
 * MSP430G2553
 */

#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	volatile unsigned int i = 0;		  // Make counter

	P1DIR |= BIT0;                            // P1.0 output
	P1OUT &= BIT0;				  // Initialize LED to 0

	// Set up button
	P1DIR &= ~BIT3;
	P1OUT |= BIT3;
	P1REN |= BIT3;

	CCTL0 = CCIE;                          // CCR0 interrupt enabled
	CCR0 = 1200;		               // 10 Hz clock to start
	TACTL = TASSEL_1 + MC_1 + TACLR;       // ACLK, upmode, clear TAR

	__bis_SR_register(GIE);       // Enter LPM3, enable interrupts
	while (1) {
		// If button is pressed
		if ((P1IN & BIT3) != BIT3) {
			i = 0;
			// Count from 0 while button is pressed
			while ((P1IN & BIT3) != BIT3) {
				P1OUT |= BIT0;
				i++;
			}
			// Assign count to CCR0
			CCR0 = i;
		}
	}
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
	P1OUT ^= 0x01;                            // Toggle P1.0
}
