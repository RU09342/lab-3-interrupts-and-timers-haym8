/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Timer A Interrupt
 * MSP430FR5994
 */

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  // Disable the GPIO power-on default high-impedance mode
  PM5CTL0 &= ~LOCKLPM5;
  P1DIR |= BIT0;                            // P1.0 output
  TB0CCTL0 = CCIE;                             // CCR0 interrupt enabled
  TB0CTL = TBSSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
  TB0CCR0 =  60000;                           // 1.25 Hz

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 Interrupt Service Routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B0_VECTOR
__interrupt void Timer_B (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= BIT0;                            // Toggle P1.0
}
