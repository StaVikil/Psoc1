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
int main(void)
{
CyGlobalIntEnable; /* Enable global interrupts. */
/* Place your initialization/startup code here (e.g. MyInst_Start()) */
FourDigit74HC595_sendOneDigit(0, 0x88, 1);

initMatrix();
uint8_t last_state = 12;

int m = 0;
int nm = 5;
for(;;)
{
  /*  
 for(int n=0;n<5000;n++){
 int i = m;

 if(i==nm){
    i=0;
} 
FourDigit74HC595_sendOneDigit(i++, 27, 0);
if(i==nm){
    i=0;
} 
FourDigit74HC595_sendOneDigit(i++, 28, 0);
if(i==nm){
    i=0;
}
FourDigit74HC595_sendOneDigit(i++, 10, 0);
if(i==nm){
    i=0;
 }
FourDigit74HC595_sendOneDigit(i++, 27, 0);
if(m==nm) m=0;
};
 m++;
 */
for(int n=0;n<5000;n++){
 int i = m;

 if(i==nm){
    i=0;
} 
 FourDigit74HC595_sendOneDigit(i++, 11, 0);
if(i==nm){
    i=0;
} 
FourDigit74HC595_sendOneDigit(i++, 10, 0);
if(i==nm){
    i=0;
}
 FourDigit74HC595_sendOneDigit(i++, 21, 0);
if(i==nm){
    i=0;
 }
FourDigit74HC595_sendOneDigit(i++, 23, 0);
if(i==nm){
    i=0;
 }
FourDigit74HC595_sendOneDigit(i++, 17, 0);
if(m==nm) m=0;
};
 m++;


/*for(int n=0;n<5000;n++){
    int i = m;
 FourDigit74HC595_sendOneDigit(i++, 11, 0);
 FourDigit74HC595_sendOneDigit(i++, 10, 0);
 FourDigit74HC595_sendOneDigit(i++, 21, 0);
 FourDigit74HC595_sendOneDigit(i++, 23, 0);
 FourDigit74HC595_sendOneDigit(i++, 17, 0);

};
m++;
*/
    
    
    
};
printMatrix();
for(;;)
{
/* Place your application code here. */
/* Button == 0 -> Button pressed
Button == 1 -> Button released
LED_x_Write(0); -> Turn ON
LED_x_Write(1); -> Turn OFF */
readMatrix();



if(keys[0][0] == 0 && last_state != 1) //is button pressed
{
last_state = 1;
FourDigit74HC595_sendOneDigit(0, 27, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[0][0] == 1 && last_state == 1) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[0][1] == 0 && last_state != 2) //is button pressed
{
last_state = 2;
FourDigit74HC595_sendOneDigit(1, 28, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[0][1] == 1 && last_state == 2) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[0][2] == 0 && last_state != 3) //is button pressed
{
last_state = 3;
FourDigit74HC595_sendOneDigit(2, 10, 0);
LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[0][2] == 1 && last_state == 3) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[1][0] == 0 && last_state != 4) //is button pressed
{
last_state = 4;
FourDigit74HC595_sendOneDigit(3, 27, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[1][0] == 1 && last_state == 4) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[1][1] == 0 && last_state != 5) //is button pressed
{
last_state = 5;
FourDigit74HC595_sendOneDigit(0, 5, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[1][1] == 1 && last_state == 5) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);

}
if(keys[1][2] == 0 && last_state != 6) //is button pressed
{
last_state = 6;
FourDigit74HC595_sendOneDigit(0, 6, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[1][2] == 1 && last_state == 6) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[2][0] == 0 && last_state != 7) //is button pressed
{
last_state = 7;
FourDigit74HC595_sendOneDigit(0, 7, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[2][0] == 1 && last_state == 7) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[2][1] == 0 && last_state != 8) //is button pressed
{
last_state = 8;
FourDigit74HC595_sendOneDigit(0, 8, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[2][1] == 1 && last_state == 8) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[2][2] == 0 && last_state != 9) //is button pressed
{

last_state = 9;
FourDigit74HC595_sendOneDigit(0, 9, 0);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[2][2] == 1 && last_state == 9) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[3][0] == 0 && last_state != 10) //is button pressed
{
last_state = 10;
FourDigit74HC595_sendOneDigit(0, 0, 1);

LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[3][0] == 1 && last_state == 10) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[3][1] == 0 && last_state != 0) //is button pressed
{
last_state = 0;
FourDigit74HC595_sendOneDigit(0, 0, 0);
LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[1][1] == 1 && last_state == 0) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
}
if(keys[3][2] == 0 && last_state != 11) //is button pressed
{
last_state = 11;
FourDigit74HC595_sendOneDigit(0, 1, 1);


LED_R_Write(0); // Turn ON
LED_G_Write(0);
LED_B_Write(0);
printMatrix();
}
if(keys[3][2] == 1 && last_state == 11) //is button released
{
last_state = 12;

LED_R_Write(1); // Turn OFF
LED_G_Write(1);
LED_B_Write(1);
printMatrix();
}
}
}
/* [] END OF FILE */
