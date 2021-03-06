/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Button Based Delay
 * MSP430FR5994
 */

#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	volatile unsigned int i = 0;		  // Make counter

	// Disable the GPIO power-on default high-impedance mode
	PM5CTL0 &= ~LOCKLPM5;

	P1DIR |= BIT0;                            // P1.0 output
	P1OUT &= BIT0;				  // Initialize LED to 0

	// Set up buttons
	P5DIR &= ~BIT6;
	P5OUT |= BIT6;
	P5REN |= BIT6;

	P5DIR &= ~BIT5;
	P5OUT |= BIT5;
	P5REN |= BIT5;

	TA1CCTL0 = CCIE;                        // CCR0 interrupt enabled
	TA1CCR0 = 3276;		       		// 10 Hz clock to sTArt
	TA1CTL = TASSEL_1 + MC_1 + TACLR;       // ACLK, upmode, clear TAR

	__bis_SR_register(GIE);       // Enter LPM3, enable interrupts
	while (1) {
		// If button is pressed
		if ((P5IN & BIT6) != BIT6) {
			i = 0;
			// Count from 0 while button is pressed down
			while ((P5IN & BIT6) != BIT6) {
				P1OUT |= BIT0;
				i++;
			}
			// Assign count to CCR0
			TA1CCR0 = i;
		}
	}
}

// Timer1 A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	P1OUT ^= 0x01;                            // Toggle P1.0
}
