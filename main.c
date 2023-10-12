/*      includes sections       */
#include "../include/STD_Types.h"
#include "../include/BIT_MATH.h"

#include "../include/GPIO_INTERFACE.h"
#include "../include/MRCC_INTERFACE.h"
#include "../include/EXTI_INTERFACE.h"
#include "../include/NVIC_INTERFACE.h"
#include "../include/SYSTICK_INTERFACE.h"
#include "../include/HLEDMATRIX_INTERFACE.h"
#include "../include/HIR_INTERFACE.h"
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/*      macros used      */
/* Remote Buttons */
#define REMOTE_BUTTON_1 48
#define REMOTE_BUTTON_2 24
#define REMOTE_BUTTON_3 122
#define REMOTE_BUTTON_4 16
#define REMOTE_BUTTON_5 56
#define REMOTE_BUTTON_6 90
#define REMOTE_BUTTON_7 66
#define REMOTE_BUTTON_8 74
#define REMOTE_BUTTON_9 82
#define REMOTE_BUTTON_INC 168
#define REMOTE_BUTTON_DEC 224
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/*      array for led matrix        */
u8 numbers[9][8] = {
    24,
    28,
    30,
    27,
    25,
    24,
    24,
    126,
    0,
    126,
    64,
    64,
    126,
    2,
    2,
    126,
    0,
    126,
    64,
    64,
    126,
    64,
    64,
    126,
    48,
    56,
    44,
    38,
    35,
    127,
    32,
    32,
    0,
    126,
    2,
    2,
    126,
    64,
    64,
    126,
    0,
    126,
    2,
    2,
    126,
    66,
    66,
    126,
    0,
    126,
    64,
    96,
    48,
    24,
    12,
    6,
    0,
    126,
    66,
    66,
    126,
    66,
    66,
    126,
    0,
    126,
    66,
    66,
    126,
    64,
    64,
    126,
};
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

/*      global variables        */
u8 value0 = 1, value1 = 0, counter0 = 0;
extern u8 data;
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

int main(void)
{
    /*      RCC intialization with HSI    */
    MRCC_INIT();

    /*      RCC enable peripherals for GPIOA & SYSCFG       */
    MRCC_ENABLE_PERIPHERAL(RCC_AHB1, RCC_AHB1_GPIOAEN);
    MRCC_ENABLE_PERIPHERAL(RCC_AHB1, RCC_AHB1_GPIOBEN);
    MRCC_ENABLE_PERIPHERAL(RCC_AHB1, RCC_AHB1_GPIOCEN);
    MRCC_ENABLE_PERIPHERAL(RCC_APB2, RCC_APB2_SYSCFG);

    /*      NVIC enable the EXTI15        */
    MNVIC_voidEnableInterrupt(40);

    /*      system tick intializaion and set call back function     */
    MSYSTICK_voidInit();
    MSYSTICK_CallBack(HIR_Data_Handler);

    /*      set EXTI15 for PORTC*/
    MEXTI_voidInterruptSetport(EXTI_LINE15, EXTI_PORTC);
    MEXTI_voidInterruptTrigger(EXTI_LINE15, FALLING_EDGE);
    MGPIO_SetInputPin(PORTC, PIN15, PULL_UP);

    /*      set call back for EXTI15        */
    MEXTI_voidCallBack(HIR_Frame_Hanler, EXTI_LINE15);

    /*      enable EXTI15       */
    MEXTI_voidInterruptEnableDisable(EXTI_LINE15, EXTI_ENABLED);

    /*      led matrix intialization        */
    HLEDMATRIX_VoidInit();
    while (1)
    {

        if (data == REMOTE_BUTTON_INC)
        {
            counter0++;
            if (counter0 == 9)
            {
                counter0 = 0;
            }
            data = 0;
        }
        else if (data == REMOTE_BUTTON_DEC)
        {
            counter0--;
            if (counter0 == 255)
            {
                counter0 = 8;
            }
            data = 0;
        }
        else if (data == REMOTE_BUTTON_1)
        {
            counter0 = 1 - 1;
        }
        else if (data == REMOTE_BUTTON_2)
        {
            counter0 = 2 - 1;
        }
        else if (data == REMOTE_BUTTON_3)
        {
            counter0 = 3 - 1;
        }
        else if (data == REMOTE_BUTTON_4)
        {
            counter0 = 4 - 1;
        }
        else if (data == REMOTE_BUTTON_5)
        {
            counter0 = 5 - 1;
        }
        else if (data == REMOTE_BUTTON_6)
        {
            counter0 = 6 - 1;
        }
        else if (data == REMOTE_BUTTON_7)
        {
            counter0 = 7 - 1;
        }
        else if (data == REMOTE_BUTTON_8)
        {
            counter0 = 8 - 1;
        }
        else if (data == REMOTE_BUTTON_9)
        {
            counter0 = 9 - 1;
        }

        for (u8 i = 0; i < 10; i++)
        {
            HLEDMATRIX_VoidSDisplay(numbers[counter0]);
        }
    }

    return 0;
}
