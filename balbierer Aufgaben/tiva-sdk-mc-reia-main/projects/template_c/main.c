#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"
#include "gpio.h"
#include "sysctl.h"
#include "systick.h"


int main()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

    SysTickPeriodSet(7999999);
    SysTickIntEnable();
    SysTickEnable();


    while (1)
    {
        __asm ("nop");
    }
    return 0;
}

void SysTick_Handler()
{
    uint8_t pv = (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2) > 0 ? 0 : GPIO_PIN_2);
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, pv);
}