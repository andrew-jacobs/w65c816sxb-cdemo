# w65c816sxb-cdemo
This repository contains a demonstration C program for the WDC W65C816 SXB development board. It contains a custom start up module and a simple implementation of the functions needed to make stdio functions work with a serial connection.

## Working with the Code
This project contains a number of headers that contain definitions for WDC processors, boards and peripheral chips.

### CPU
The w65c816.h file contains definitions that are specific to the W65C816 micro-processor. Currently this consists of four macros that enable and disable interrupts. They should be used like functions in program code.
```
void someFunction (void)
{
    enableInterrupts ();

    suspendInterrupts ();
    /* Something critical */
    restoreInterrupts ();

    disableInterrupts ();
}
```
The enableInterrupts() and disableInterrupts() macros directly control the state of the I bit in the status register using CLI and SEI.

The suspendInterrupt() macro saves the state of I flag and then ensures it is interrupts are disabled (e.g. PHP followed SEI). The restoreInterrupts() macro puts the restores the state of the I bit (e.g. PLP). Each use of suspendInterrupts() must have a matching restoreInterrupts() in the same function or your program may crash.

### Board
The w65c816sxb.h file contains definitions that are specific to the W65C816SXB developer board including the main oscillator speed and the addresses of each of the peripheral devices.

Name    | Description
------- | -------------------------------
FCLK    | Main oscillator speed (8 MHz)
ACIA    | Points at the ACIA device
PIA     | Points at the PIA device
USR_VIA | Points at the user VIA device
SYS_VIA | Points at the system VIA device

These #defines are used in conjunction with device macros (decribed later) to access the peripheral registers and the fields within them.

Also included in the board header are a set of prototypes for functions that initialise the board to provide a simple timer and interrupt driven serial I/O.

```
extern void initialise (void);

extern uint32_t millis (void);
extern void delay (uint32_t msec);

extern int16_t aciaTx (uint8_t ch);
extern int16_t aciaRx (int16_t wait);
````

The initialise() function configures the VIAs and ACIA to generate a simple incrementing counter and provide serial I/O via the ACIA.

The delay() function uses the counter to provide a timed delays.


### Devices
Each of the standard WDC periperal chips (i.e. W65C21 PIA, W65C22 VIA and W65C51 ACIA) has its own header file which contains a set of #define'd constants for the data fields in the registers and the values used to select different options.

These constaints follow a standard naming patterns:

- Constants that look like DEVICE_REG_FIELD_MASK resolve to the bit pattern needed to extract a given field from a register. For example ACIA_SR_IRQ_MASK extracts the IRQ bit from the status register (SR) in a W65C51 ACIA. If the data field contains several bits that the mask will extract all of them, for example ACIA_CTL_SBR_MASK can be used to isolate bits 3 down to 0 of an ACIA's control register which hold the 'Selected Baud Rate' (SBR).

- Constants that look like DEVICE_REG_FIELD_VALUE resolve to a value that can be used to set or test a register field. The last part of the name indicates the value appropriate to the field, for example the set of values for the ACIA's baud rate have names like ACIA_CTL_SBR_9600 and ACIA_CTL_SBR_19200.

The internal register structure of each device is modelled with a small structure containing byte values.

> I tried defining the peripheral registers using unions containing bit fields but even after optimisation the code generated was not very good.

Each device header provides macros to access the peripheral registers given a pointer to the device structure. These macros expand into C l-values which can be either read or written to.

For example the macros ACIA_CTL()  provides access to the W65C51's control register


### W65C21 PIA


PIA_

### W65C22 VIA

### W65C51 ACIA
