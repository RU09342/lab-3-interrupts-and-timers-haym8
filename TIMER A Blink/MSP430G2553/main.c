/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Timer A Interrupt
 * MSP430G2553
 */

#include <msp430.h>

int main(void) {
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P1DIR |= 0x01;                            // P1.0 output
	CCTL0 = CCIE;                             // CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
	CCR0 = 60000;				  // 1.25 Hz

	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 Interrupt Service Routine
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
