/*
 * Mitchell Hay
 * RU09342
 * Lab 3 Button Interrupt
 * MSP430FR5994
 */

#include <msp430.h>

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
	
  // Disable the GPIO power-on default high-impedance mode
  PM5CTL0 &= ~LOCKLPM5;
	
  P1DIR |= BIT0;                            // Set P1.0 to output direction

  P5IE |=  BIT6;                            // P56 interrupt enabled
  P5IES |= BIT6;                            // P5.6 Hi/lo edge
  P5REN |= BIT6;                            // Enable Pull Up on SW1 (P5.6)
  P5IFG &= ~BIT6;                           // P5.6 IFG cleared

  __bis_SR_register(LPM4_bits + GIE);       // Enter LPM4 w/interrupt
}

// Port 1 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=PORT5_VECTOR
__interrupt void Port_5(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(PORT1_VECTOR))) Port_1 (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= BIT0;                            // P1.0 = toggle
  P5IFG &= ~BIT6;                           // P5.6 IFG cleared
}
