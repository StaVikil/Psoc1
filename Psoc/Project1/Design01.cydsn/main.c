/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(int i = 200; i > 30; i = i - 10)
    {
        
        if(Button_Read() == 0){
        LED_B_Write(0);
        LED_G_Write(0);
        LED_R_Write(0);
        CyDelay(i);
        LED_B_Write(1);
        LED_G_Write(1);
        LED_R_Write(1);
        CyDelay(i);
        if(i == 40) i = 200;
        }
        else{
             LED_G_Write(0);
             CyDelay(i);
             LED_G_Write(1);
             LED_R_Write(0);
             CyDelay(i);
             LED_R_Write(1);
             LED_B_Write(0);
             CyDelay(i);
             LED_B_Write(1);
             LED_G_Write(0);
             LED_R_Write(0);
             CyDelay(i);
             LED_G_Write(1);
             LED_R_Write(1);
             LED_G_Write(0);
             LED_B_Write(0);
            CyDelay(i);
             LED_G_Write(1);
             LED_B_Write(1);
             LED_R_Write(0);
             LED_B_Write(0);
             CyDelay(i);
             LED_R_Write(1);
             LED_B_Write(1);
            LED_R_Write(0);
             LED_B_Write(0);
             LED_G_Write(0);
            CyDelay(i);
            LED_R_Write(1);
             LED_B_Write(1);
             LED_G_Write(1);
            
            if(i == 40) i = 200;
            
/*      LED_G_Write(0);
        LED_R_Write(0);
        CyDelay(i);
        
        LED_G_Write(1);
        LED_R_Write(1);
        CyDelay(i);
            if(i == 40) i = 200;
       */
        LED_B_Write(1);
        LED_R_Write(1);
        LED_G_Write(1);
       
            }
        
        }
        /*if(Button_Read() == 1)
        {
        LED_Write(0);
            }
        }
        else 
        {
        LED_Write(1);
        }*/
        /* Place your application code here. */
    }


/* [] END OF FILE */
