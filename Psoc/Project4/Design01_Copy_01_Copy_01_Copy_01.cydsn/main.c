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
/* */
static uint8_t LED_NUM[] = {
    0xC0,   //0
    0xF9,   //1
    0xA4,   //2
    0xB0,   //3
    0x99,   //4
    0x92,   //5
    0x82,   //6
    0xF8,   //7
    0x80,   //8
    0x90,   //9
    0x88,   //A
    0x83,   //b
    0xC6,   //C
    0xA1,   //d
    0x86,   //E
    0x8E,   //F 15 
    0xc2,   //G 16
    0x8b,   //h 17
    0xcf,   //I 18
    0xe1,   //J 19
    0x89,   //K 20
    0xc7,   //L 21
    0xab,   //n 22
    0xC0,   //O 23
    0x8c,   //P 24
    0x98,   //q 25
    0xaf,   //r 26
    0x92,   //S 27
    0x87,   //t 28
    0xe3,   //u 29
    0x91,   //y 30
    0xA4,   //Z 31
    0xBF,   //- 32
    0x7F    //. 33 Position
    
};

static uint8_t NAME[] = {
    0x92,   //S 
    0x87,   //t 
    0x88,   //A
};
/* send data function */
static void FourDigit74HC595_sendData(uint8_t data) {
for(uint8_t i = 0; i < 8; i++) {
if(data & (0x80 >> i))
{
Pin_DO_Write(1);
}
else
{
Pin_DO_Write(0);
}
Pin_CLK_Write(1);
Pin_CLK_Write(0);
}
}
/* */
static void FourDigit74HC595_sendOneDigit(uint8_t position, uint8_t digit, uint8_t dot)
{
if(position >= 8) // out of range, clear 7-segment display
{
FourDigit74HC595_sendData(0xFF);
FourDigit74HC595_sendData(0xFF);
}
FourDigit74HC595_sendData(0xFF & ~(1 << position));
if(dot) // if dot is needed
{
FourDigit74HC595_sendData(LED_NUM[digit] & 0x7F);
}
else
{
FourDigit74HC595_sendData(LED_NUM[digit]);
}
Pin_Latch_Write(1); // Latch shift register
Pin_Latch_Write(0);

}
/* [ROW][COLUMN] */
static uint8_t keys[4][3] = {
{1, 2, 3},
{4, 5, 6},
{7, 8, 9},
{10, 0, 11},
};
/* arrays of pointers */
/* function of drive mode configuration */
static void (*COLUMN_x_SetDriveMode[3])(uint8_t mode) = {
COLUMN_0_SetDriveMode,
COLUMN_1_SetDriveMode,
COLUMN_2_SetDriveMode
};
/* column write function */
static void (*COLUMN_x_Write[3])(uint8_t value) = {
COLUMN_0_Write,
COLUMN_1_Write,
COLUMN_2_Write
};
/* read row function */
static uint8 (*ROW_x_Read[4])() = {
ROW_0_Read,
ROW_1_Read,
ROW_2_Read,
ROW_3_Read
};
/* matrix initialization function */
static void initMatrix()
{
for(int column_index = 0; column_index < 3; column_index++)
{
COLUMN_x_SetDriveMode[column_index](COLUMN_0_DM_DIG_HIZ);
}
}
/* keys matrix read function */
static void readMatrix()
{
/* define the length of a row and column */
uint8_t row_counter = sizeof(ROW_x_Read)/sizeof(ROW_x_Read[0]);
uint8_t column_counter = sizeof(COLUMN_x_Write)/sizeof(COLUMN_x_Write[0]);
/* column: iterate the columns */
for(int column_index = 0; column_index < column_counter; column_index++)
{
COLUMN_x_SetDriveMode[column_index](COLUMN_0_DM_STRONG);
COLUMN_x_Write[column_index](0);
/* row: interate throught the rows */
for(int row_index = 0; row_index < row_counter; row_index++)
{
keys[row_index][column_index] = ROW_x_Read[row_index]();
}
/* disable the column */
COLUMN_x_SetDriveMode[column_index](COLUMN_0_DM_DIG_HIZ);
}
}
/* matrix print function */
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
static uint8_t led_counter = 0;
CY_ISR(Timer_Int_Handler2){

uint8_t data[8] = {27,28,10,27,27,28,10,27};


FourDigit74HC595_sendOneDigit(led_counter, data[led_counter], 0);
led_counter++;
if(led_counter>7) led_counter=0;




}


int main(void)
{
CyGlobalIntEnable; /* Enable global interrupts. */
/* Place your initialization/startup code here (e.g. MyInst_Start()) */


uint8_t last_state = 12;

Timer_1_Start();
Timer_Int_StartEx(Timer_Int_Handler2);


}
/* [] END OF FILE */
