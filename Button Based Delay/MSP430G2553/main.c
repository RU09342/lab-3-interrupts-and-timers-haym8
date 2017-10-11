#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	volatile unsigned int i = 0;

	P1DIR |= BIT0;                            // P1.0 output
	P1OUT &= BIT0;	// Initialize LED to 0

	// Set up button
	P1DIR &= ~BIT3;
	P1OUT |= BIT3;
	P1REN |= BIT3;

	CCTL0 = CCIE;                          // CCR0 interrupt enabled
	CCR0 = 1200;							// 10 Hz clock to start
	TACTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

	__bis_SR_register(GIE);       // Enter LPM3, enable interrupts
	while (1) {
		if ((P1IN & BIT3) != BIT3) {
			i = 0;
			while ((P1IN & BIT3) != BIT3) {
				P1OUT |= BIT0;
				i++;
			}
			CCR0 = i;
		}
	}
	//__no_operation();                         // For debugger
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
