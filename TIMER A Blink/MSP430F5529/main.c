/*
 * Mitchell Hay
 * Lab 3 - Timer A Blink
 * MSP430F5529
*/

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= BIT0;                            // P1.0 output
  TA0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TA0CTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
  TA0CCR0 =  100000;                           // 1.25 Hz

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 Interrupt Service Routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= BIT0;                            // Toggle P1.0
}
