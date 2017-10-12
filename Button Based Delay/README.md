## Mitchell Hay

# Button Based Delay
This part of the lab had an LED blinking at a set 10 Hz to start. Once a button was pressed down, a counter starts. When the button is released, the counter stops and is the new rate of the LED blinking. The user would control how fast or slow the LED would blink. Even though this lab has been using interrupts, it would make sense to use both interrupts and polling here. The timer uses an interrupt to determine how fast the LED blinks, while the button uses polling to determine how long the button is pressed for. Using polling and interrupts together is essential in this lab.

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
The user clicks the button and holds it down to determine the new rate of the button blink. The longer the button is held, the longer the period of one cycle is.
## Extra Work
Using the MSP430F5529, a "reset" button was added to the program. When this button was clicked, the LED blinking would return back to 10 Hz. While the button to control the button blink rate was done using polling, the reset button was done using an interrupt. That means there were two instances of interrupts and one instance of polling for the extra work section of this part of the lab.

# Known Errors
There are no known errors at this time

# Tasks
* [x] Handle two different types of I/O at once
* [x] Make a program with interrupts while the user adds input
* [x] Combine polling and interrupts
