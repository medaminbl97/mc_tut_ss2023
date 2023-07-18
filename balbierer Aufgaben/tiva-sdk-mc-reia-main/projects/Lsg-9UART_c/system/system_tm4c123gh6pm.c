#include <stdint.h>
#include <stdbool.h>

#include "fpu.h"
#include "sysctl.h"

/* System clock frequency in Hz */
uint32_t SystemCoreClock; 


/* Initialize the System and update the SystemCoreClock variable.
 */
void SystemInit (void)
{
    /* Enable FPU */
    FPUEnable();

    /* Set CPU core clock */
#ifdef USE_CORE_CLK_PLL
    SysCtlClockSet(
        SYSCTL_USE_PLL |
        SYSCTL_OSC_MAIN |
        SYSCTL_XTAL_16MHZ |
        SYSCTL_SYSDIV_2_5
    );
#endif
    SystemCoreClock = SysCtlClockGet();
}

/* Updates the SystemCoreClock variable
 */
void SystemCoreClockUpdate (void)
{
    SystemCoreClock = SysCtlClockGet();
}