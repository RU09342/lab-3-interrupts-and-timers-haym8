/*
 * Mitchell Hay
 * Lab 3 Button Based Delay
 * MSP430F5529
*/

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  volatile unsigned int i = 0;

  P1DIR |= BIT0;                            // P1.0 output
  P1OUT &= BIT0;	// Initialize LED to 0

  // Set up button
  P2DIR &= ~BIT1;
  P2OUT |= BIT1;
  P2REN |= BIT1;

  P1DIR &= ~BIT1;
  P1OUT |= BIT1;
  P1REN |= BIT1;

  TA1CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA1CCR0 = 3276;							// 10 Hz clock to start
  TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, upmode, clear TAR

  __bis_SR_register(GIE);       // Enter LPM3, enable interrupts
	while (1) {
		if ((P2IN & BIT1) != BIT1) {
			i = 0;
			while ((P2IN & BIT1) != BIT1) {
				P1OUT |= BIT0;
				i++;
			}
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
