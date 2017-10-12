#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  volatile unsigned int i = 0;		    // Make counter

  // Disable the GPIO power-on default high-impedance mode
  PM5CTL0 &= ~LOCKLPM5;

  P1DIR |= BIT0;                            // P1.0 output
  P1OUT &= BIT0;			    // Initialize LED to 0

  // Set up buttons
  P1DIR &= ~BIT1;
  P1OUT |= BIT1;
  P1REN |= BIT1;

  P1DIR &= ~BIT1;
  P1OUT |= BIT1;
  P1REN |= BIT1;

  TB1CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TB1CTL |= TBSSEL__ACLK | MC__UP | TBCLR; // ACLK, continuous mode, clear TBR
  TB1CCR0 = 3276;                           // 10 Hz

  __bis_SR_register(GIE);       // Enter LPM3, enable interrupts
	while (1) {
		// If button is pressed
		if ((P1IN & BIT1) != BIT1) {
			i = 0;
			// Count while button is being pressed
			while ((P1IN & BIT1) != BIT1) {
				P1OUT |= BIT0;
				i++;
			}
			// Assign count to CCR0
			TB1CCR0 = i;
		}
	}
}

// Timer1 A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER1_B0_VECTOR
__interrupt void TIMER1_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER1_A0_VECTOR))) TIMER1_A0_ISR (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= 0x01;                            // Toggle P1.0
}
