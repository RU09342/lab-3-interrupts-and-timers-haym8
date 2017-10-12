/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Button Interrupt
 * MSP430F5529
*/

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  P1DIR |= BIT0;                            // Set P1.0 to output direction
  P2IE |=  BIT1;                            // P2.1 interrupt enabled
  P2IES |= BIT1;                            // P2.1 Hi/lo edge
  P2REN |= BIT1;                            // Enable Pull Up on SW2 (P2.1)
  P2IFG &= ~BIT1;                           // P2.1 IFG cleared

  __enable_interrupt();                     // Interrupt enabled
  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= BIT0;                            // P1.0 = toggle
  P2IFG &= ~BIT1;                           // P2.1 IFG cleared
}
