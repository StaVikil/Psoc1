#include "project.h"

static void (*COLx_SetDriveMode[3]) (uint8_t mode) = {
    COL0_SetDriveMode,
    COL1_SetDriveMode,
    COL2_SetDriveMode
};

static void (*COLx_Write[3]) (uint8_t value) = {
    COL0_Write,
    COL1_Write,
    COL2_Write
};

static uint8 (*ROWx_Read[4]) () = {
    ROW0_Read,
    ROW1_Read,
    ROW2_Read,
    ROW3_Read,
};

static uint8_t keys[4][3];

static void matriIinit()
{
    for(int i = 0; i < 3; i++)
    {
        COLx_SetDriveMode[i](COL0_DM_DIG_HIZ);
    }
    
}

static void readMatrix()
{
    uint8_t row_count = sizeof(ROWx_Read)/sizeof(ROWx_Read[0]);
    uint8_t col_count = sizeof(COLx_Write)/sizeof(COLx_Write[0]);
    
    for(int col_index = 0; col_index < col_count; col_index++)
    {
        
        COLx_SetDriveMode[col_index] (COL0_DM_STRONG);
        COLx_Write[col_index](0);
        
        for(int row_index = 0; row_index < row_count; row_index++)
        {
            keys[row_index][col_index] = ROWx_Read[row_index]();
        }
        COLx_SetDriveMode[col_index] (COL0_DM_DIG_HIZ);
    }
    
}

void printMatrix()
{
    SW_Tx_UART_PutCRLF();
    for (int row_index = 0; row_index < 4; row_index++)
    {
        for(int column_index = 0; column_index < 3; column_index++)
        {
            SW_Tx_UART_PutHexInt(keys[row_index][column_index]);

            SW_Tx_UART_PutString(" ");
        }
        SW_Tx_UART_PutCRLF();
    }
    SW_Tx_UART_PutCRLF();
}

int main(void)
{
    SW_Tx_UART_PutString("Software UART");
    SW_Tx_UART_PutCRLF();
    SW_Tx_UART_PutString("Lab3");
    SW_Tx_UART_PutCRLF();
    SW_Tx_UART_PutString("Maks");
    SW_Tx_UART_PutCRLF();
    SW_Tx_UART_PutCRLF();
    uint8_t last_state = 0;
    matriIinit();
    LED_B_Write(0);
    LED_R_Write(0);
    LED_G_Write(0);
    for(;;)
    {
      int n;
       
        readMatrix();
        if(keys[0][0] == 0 && last_state !=1)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            SW_Tx_UART_PutString("Button 1 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
           n = 1;
            last_state = 1;
           
        }

        if(keys[0][1] == 0 && last_state !=2)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_G_Write(0);
            SW_Tx_UART_PutString("Button 2 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 2;
        }

        if(keys[0][2] == 0 && last_state !=3)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
           LED_B_Write(0);
             SW_Tx_UART_PutString("Button 3 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 3;
        }

        if(keys[1][0] == 0 && last_state !=4)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            LED_G_Write(0);
            SW_Tx_UART_PutString("Button 4 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 4;
        }

        if(keys[1][1] == 0 && last_state !=5)
        {
           LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            LED_B_Write(0);
            SW_Tx_UART_PutString("Button 5 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 5;
        }

        if(keys[1][2] == 0 && last_state !=6)
        {
            LED_B_Write(1);
            LED_G_Write(1);
            LED_R_Write(1);
            LED_G_Write(0);
             LED_B_Write(0);
            SW_Tx_UART_PutString("Button 6 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 6;
        }

        if(keys[2][0] == 0 && last_state !=7)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            SW_Tx_UART_PutString("Button 7 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 7;
        }
 if(keys[2][1] == 0 && last_state !=8)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_G_Write(0);
            SW_Tx_UART_PutString("Button 8 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 8;
        }

        if(keys[2][2] == 0 && last_state != 9)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_B_Write(0);
            SW_Tx_UART_PutString("Button 9 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 9;
        }

        if(keys[3][0] == 0 && last_state != 10)
        {
            LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            LED_G_Write(0);
            SW_Tx_UART_PutString("Button * active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 10;
        }

        if(keys[3][1] == 0 && last_state !=11)
        {
             LED_B_Write(1);
            LED_R_Write(1);
            LED_G_Write(1);
            LED_R_Write(0);
            LED_B_Write(0);
            SW_Tx_UART_PutString("Button 0 active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
            n = 1;
            last_state = 11;
        }

        if(keys[3][2] == 0 && last_state !=12)
        {
             LED_B_Write(1);
            LED_G_Write(1);
            LED_R_Write(1);
            LED_G_Write(0);
             LED_B_Write(0);
            SW_Tx_UART_PutString("Button # active");
            printMatrix();
            SW_Tx_UART_PutCRLF();
           
            n = 1;
            last_state = 12;
        }
       
        
        
       
         
    
    }
        
}
