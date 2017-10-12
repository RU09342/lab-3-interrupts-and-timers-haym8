## Mitchell Hay

# Timer A Interrupt
Similar to the button, internal timers can also trigger interrupts. Timer interrupts happen when the timer counts up to a certain value. This can be very handy, and in this part of the lab it would be used to blink an LED with a 50% duty cycle.

# Devices
* MSP430F5529
* MSP430FR2311
* MSP430FR5994
* MSP430FR6989
* MSP430G2553

# Getting Started
## Dependencies
Each device requires no outside dependencies. Everything needed to run the program is included in the folder. Each folder is labeled with the device it is meant for.
## Setup
Each of the device projects in this part of the lab can be imported into Code Composer Studio and run from there. To import it, open CCS and select File -> Import -> Code Composer Studio -> CCS Project and select the desired directory.

# Functionality
## Usage
There is nothing that needs to be done by the user once the program is loaded onto the device. There will be an LED blinking at a constant rate. Nothing can be done to change this rate, as it is controlled by a timer in the microcontroller.

# Known Errors
There are no known errors at this time

# Tasks
* [x] Use timers to blink LED
* [x] Learn about timer interrupts
