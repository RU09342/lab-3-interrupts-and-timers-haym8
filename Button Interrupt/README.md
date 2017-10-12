## Mitchell Hay

# Button Interrupt
When a button was pressed in the previous lab, the press would be handled by a method called polling. This meant that the button status was constantly checked. A more efficient way of doing this is using interrupts. In this part of the lab, a button interrupt would be implemented. An interrupt works by calling a method when the button is pressed. The processor is not always looking out for it, and handles the button press when the interrupt is triggered. Doing this saves a lot of power, as the CPU does not always need to be on. Only when the interrupt strikes is when the processor would need to do work. For this lab, an interrupt would be used to toggle an LED light.

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
The LED turns on and off based on the user's input, which in this case is a button. When the button is pressed, the LED switches states.

# Known Errors
There are no known errors at this time. 

# Tasks
* [x] Review circuit design knowledge
* [x] Choose appropriate values for circuit elements
* [ ] Implement an offboard UART connection
