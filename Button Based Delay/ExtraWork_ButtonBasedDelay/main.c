/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Button Based Delay
 * MSP430F5529
*/

#include <msp430.h>

volatile unsigned int i = 3276;		  // Make counter for delay

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT

	P1DIR |= BIT0;                            // P1.0 output
	P1OUT &= BIT0;				  // Initialize LED to 0

	// Set up delay button P2.1
	P2DIR &= ~BIT1;
	P2OUT |= BIT1;
	P2REN |= BIT1;

	// Set up reset button P1.1
	// Reset back to 10 Hz
	P1DIR &= ~(BIT1); //set P1.1 input
	P1REN |= BIT1; //enable pull-up resistor
	P1OUT |= BIT1;
	P1IE |= BIT1; //enable the interrupt on P1.1
	P1IES |= ~BIT1; //set to look for falling edge
	P1IFG &= ~(BIT1); //clear interrupt flag

	TA0CCTL0 = CCIE;                          // CCR0 interrupt enabled
	TA0CCR0 = 3276;				  // 10 Hz clock to start
	TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

	__bis_SR_register(GIE);       // Enter LPM3, enable interrupts

	// Loop forever
	while (1) {
		// If button pressed
		if ((P2IN & BIT1) != BIT1) {
			i = 0;
			// Count while button is held down
			while ((P2IN & BIT1) != BIT1) {
				P1OUT |= BIT0;
				i++;
			}
			// Use result of counter as new CCR0
			TA0CCR0 = i;
		}
	}
}

// Timer1 A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
	P1OUT ^= 0x01;                            // Toggle P1.0
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
	if ((P1IN & BIT1) != BIT1) {
		i = 3276;
		TA0CCR0 = i;
	}
}
