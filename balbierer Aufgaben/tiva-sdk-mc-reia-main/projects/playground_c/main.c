#include <stdint.h>
#include <stdbool.h>

/* Driverlib includes */
#include "inc/hw_memmap.h"
#include "pin_map.h"

#include "gpio.h"
#include "sysctl.h"
#include "systick.h"
#include "timer.h"


void init_pwm_channels()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeTimer(GPIO_PORTF_BASE, GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    GPIOPinConfigure(GPIO_PF1_T0CCP1);
    GPIOPinConfigure(GPIO_PF2_T1CCP0);
    GPIOPinConfigure(GPIO_PF3_T1CCP1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);

    TimerLoadSet(TIMER0_BASE, TIMER_B, 10000);
    TimerMatchSet(TIMER0_BASE, TIMER_B, 9000);

    TimerLoadSet(TIMER1_BASE, TIMER_A, 10000);
    TimerMatchSet(TIMER1_BASE, TIMER_A, 9000);

    TimerLoadSet(TIMER1_BASE, TIMER_B, 10000);
    TimerMatchSet(TIMER1_BASE, TIMER_B, 9000);

    TimerEnable(TIMER0_BASE, TIMER_B);
    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER1_BASE, TIMER_B);
}


int main()
{
    SysTickPeriodSet(7999999);
    SysTickIntEnable();
    SysTickEnable();

    init_pwm_channels();

    TimerMatchSet(TIMER0_BASE, TIMER_B, 1000);
    TimerMatchSet(TIMER1_BASE, TIMER_B, 7000);
    TimerMatchSet(TIMER1_BASE, TIMER_A, 9000);

    while (1)
    {
        __asm ("nop");
    }
    return 0;
}

void SysTick_Handler()
{
   
}