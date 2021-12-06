/*******************************************************************************
  MPLAB Harmony Application Source File
  
  Company:
    Microchip Technology Inc.
 * ETML-ES 
 *          Auteur : Ph. Bovey (Philou)
  
  File Name:
    app.c

  Summary:
    This file contains the source code for the MPLAB Harmony application.

  Description:
    This file contains the source code for the MPLAB Harmony application.  It 
    implements the logic of the application's state machine and it may call 
    API routines of other MPLAB Harmony modules in the system, such as drivers,
    system services, and middleware.  However, it does not call any of the
    system interfaces (such as the "Initialize" and "Tasks" functions) of any of
    the modules in the system or make any assumptions about when those functions
    are called.  That is the responsibility of the configuration-specific system
    files.
 * 
 * Modification Date : 15.11.2021
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013-2014 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************
//-- standart library --//
#include <stdint.h>             // using the integer type normalisee 

//-- custom library --// 
#include "app.h"
#include "Mc32DriverLcd.h"      // to use the functionality for the LCD 
                                // BC_2004AB
#include "Mc32DriverAdc.h"      // to user the AD Converter Chanel of PIC
#include "gestion_leds.h"


// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

APP_DATA appData;           // global value using just in this file
                            // and allows to update also the state






// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


/* TODO:  Add any necessary local functions.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Remarks:
    See prototype in app.h. => this function is called in the system_init.c 
 */

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;

    
    /* TODO: Initialize your application's state machine and other
     * parameters.
     */
}


/******************************************************************************
  Function:
    void APP_Tasks ( void )

  Remarks:
    See prototype in app.h.
 * 
 * Auteur : - microchip 
 *          - Ph. Bovey (Philou) 
 * 
 * Modification date : le 15.11.2021
 * 
 * Description : 1) Add the new stat in the switch case
 *               2) Complete the "init" state, with the initialization of the 
 *                  LCD functions and LED activation 
 *               3) Implement the "wait" state - this state does nothing 
 *               4) Impement the "service Task" : reading the ADC ports and 
 *                  displays the raw values 
 * 
 * version : 0.3 
 ******************************************************************************/
void APP_Tasks ( void )
{
    //-- structure declaration --//
    S_ADCResults ADC_portValues;        // reading ports RB0 (An0) and RB1 (An1)
    
    //-- variables declaration --// 
    static uint8_t flagFirstCall_ASST = 0;  // flag to indicate that this is the 
                                            // first time that the ASST state is 
                                            // called 
    
    static uint8_t cmptLeds = 0;            // informtion for the light chaser
    
    uint16_t switchOffLeds = ~LIGHTING_LEDS_PORTS_A;  // 0x7F0C => 0x80F3
    
    

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            //-- initialization of the LCD --//
            lcd_init(); 
            //-- backlight activation --//
            lcd_bl_on(); 
            
            //-- place the pointer on first character of the LCD dispay--// 
            lcd_gotoxy(1,1); 
            //-- display the user msg one first line --// 
            printf_lcd("TP0 LEDS + AD "); 
            
            //-- place the pointer on the second line --// 
            lcd_gotoxy(1,2); 
            printf_lcd("CODE BY Philou"); 
            
            //--place the pointer on the third line --// 
            lcd_gotoxy(1,3); 
            printf_lcd("VERSION 0.1");
            
            //-- AD input initialization -> see the Mc32DriverADC.h --// 
            BSP_InitADC10(); 
            
            /* Light all the LED (LED0 to LED7) with the PLIB --//
               use the Harmony Help : PLIB_PORTS_Write function --//
               writing on the all port => help with schematic => to light the 
               leds, write 0 or shutdown the leds, write 1 => the port A has 16pin 
               see the page 23 on the lab book n°1 (PHILOU Red Book) to the 
               explanation of the bits value */
            PLIB_PORTS_Write(PORTS_ID_0, PORT_CHANNEL_A, LIGHTING_LEDS_PORTS_A); 
            
            //-- writing on the one pin => use the harmony help : 
            //   PLIB_PORTS_PinWrite function
            PLIB_PORTS_PinWrite(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10,0); 
            
            //-- active the timer1 --// 
            /* to see if the timer (instance 0) has been good configured, go 
               to the system_init.c file and check in the function 
               "SYS_Initialize", the function all DRV_TMR0_Initialize();, that
               means that the timer (instace 0) is actived */ 
            DRV_TMR0_Start(); 
            
            //-- update of the state machine --// 
            appData.state = APP_STATE_WAIT; 
            
            //-- end of the INIT State --// 
            break; 
        }

        /* TODO: implement your application state machine.*/
        case APP_STATE_SERVICE_TASKS:
        {
            //-- testing if this is the first time that the ASST state is called --//  
            if(flagFirstCall_ASST == 0)
            {
                //-- Swith off all the LED (LED0 to LED6) with the PLIB --//
                //-- use the Harmony Help : PLIB_PORTS_Set function --//
                /* see the page 23 on the lab book n°1 to the explanation of the 
                /  bits value. The function PLIB_PORTS_Set the AND functionality 
                /  To light the leds, it must applies the 0 the appropriate pin */ 
                PLIB_PORTS_Set(PORTS_ID_0, PORT_CHANNEL_A, switchOffLeds, 0xFFFF);
                
                //-- switch off one led (LED7 - RB10) with the PLIB Function --//
                //-- use the Harmony Help : PLIB_PORTS_PinSet function --//
                /* This function put at 1 (high state) a specific pin */
                PLIB_PORTS_PinSet(PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_10); 
                
                //-- update the flag --
                flagFirstCall_ASST = 1; 
            }    
                
            //-- reading of two potentiometers (R5 et R6) connected on the port 
            //   B - line 25 (RBO - An0) and line 24 (RB1 - An1), for this, use 
            //   the function call "BSP_ReadAllADC" in the MC32DriverAdc.h (.c)
            //   Resolution of ADC is 10bits => values vary between 0 to 1023
            ADC_portValues = BSP_ReadAllADC(); 
            
            //-- user msg on the fourth line affect the raw value of ADC
            lcd_gotoxy(1, 4); 
            printf_lcd("CH0 %04d  CH1 %04d", ADC_portValues.Chan0, 
                       ADC_portValues.Chan1); 
        
            //-- function call : Chenillard --// 
            //ChenillardHautBasSKPIC32(cmptLeds); 
            
            //-- Update of counter --// 
            if(cmptLeds > 7)
                cmptLeds = 0; 
            else 
                cmptLeds++; 
                    
            //-- end of the SERVICE State --// 
            break;
        }
        
        //-- state WAIT without activities --//
        case APP_STATE_WAIT: 
        {
            //-- end of the WAIT state --//  
            break; 
        }

       
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            appData.state = APP_STATE_WAIT; 
            break;
        }
    }
}

/*******************************************************************************
 * Function Name                : APP_UpdateStates 
 * IN/OUT/INOUT Parameters      : APP_STATE New / - / -
 * Description                  : Allow to change de state at each call which 
 *                                will be in an another file .c 
 *                                In this file (.c), you must declare a global 
 *                                value just for this file, for this point use 
 *                                the global done for this point "appData"
 * 
 * Creation date                : 17.08.2020
 * Modification date            : xx.xx.xxxx
 * 
 * Auteur                       : Ph. Bovey (philou) 
 * Version                      : 0.1 
*******************************************************************************/
void APP_UpdateStates(APP_STATES newState)
{
    appData.state = newState;    
}

/*******************************************************************************
 End of File
 */
