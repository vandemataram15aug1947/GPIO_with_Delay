// Included Files
//
#include "F28x_Project.h"
#include "driverlib.h"
#include "device.h"

void GPIO_use_init(void);
//
// Main
//
void main(void)
{
    // Initialize System Control:
    // PLL, WatchDog, enable Peripheral Clocks
    InitSysCtrl();
    // Initialize GPIO:
    // InitGpio - Sets all pins to be muxed to GPIO in input mode with pull-ups enabled.
    InitGpio();
    // Clear all interrupts and initialize PIE vector table:
    // Disable CPU interrupts
    DINT;
    // Initialize the PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags are cleared.
    InitPieCtrl();
    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;
    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    InitPieVectTable();
    // Initialize used GPIO:
    GPIO_use_init();
    // Empty loop
    for(;;) {
        DELAY_US(500000);
        // The toggle registers are used to drive specified GPIO pins
        // to the opposite level without disturbing other pins.
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        // The set registers are used to drive specified GPIO pins high
        // without disturbing other pins.
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;
        // Writing to the GPyDAT register clears or sets the corresponding
        // output latch
        // The GPyDAT registers have a lag between when the register is written
        // to when the new pin value is reflected back in the register.
        // Be careful!
        GpioDataRegs.GPADAT.bit.GPIO0 = 1;
        DELAY_US(500000);
        // The toggle registers are used to drive specified GPIO pins
        // to the opposite level without disturbing other pins.
        GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
        //The clear registers are used to drive specified GPIO pins low
        // without disturbing other pins.
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
        // Writing to the GPyDAT register clears or sets the corresponding
        // output latch
        // The GPyDAT registers have a lag between when the register is written
        // to when the new pin value is reflected back in the register.
        // Be careful!
        GpioDataRegs.GPADAT.bit.GPIO0 = 0;
    }
}

void GPIO_use_init(void)
{
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;   // Enable pullup on GPIO
    GpioDataRegs.GPASET.bit.GPIO0 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;  // Pin = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;   // GPIO = output

    GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;   // Enable pullup on GPIO
    GpioDataRegs.GPASET.bit.GPIO31 = 1;   // Load output latch
    GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;  // Pin = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;   // GPIO = output

    GpioCtrlRegs.GPBPUD.bit.GPIO34 = 0;   // Enable pullup on GPIO
    GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // Load output latch
    GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;  // Pin = GPIO
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;   // GPIO = output
    EDIS;
}
//
// End of File
//
