#include<lpc21xx.h>
#include"lcd.h"
#define c0 (IOPIN1&(1<<18))
#define c1 (IOPIN1&(1<<19))
#define c2 (IOPIN1&(1<<27))
#define c3 (IOPIN1&(1<<28))

#define r0 1<<15
#define r1 1<<16
#define r2 1<<17

unsigned int key_lut[3][4]={{1,2,3,4},{5,6,7,8},{9,0,0,0}};
unsigned int keyscan(void)
{
unsigned char row_val,col_val;
IODIR1|=r0|r1|r2;
while(1)
{
IOCLR1=r0|r1|r2;
IOSET1=c0|c1|c2|c3;
while((c0&&c1&&c2&&c3)==1);

//test for r0
IOCLR1=r0;
IOSET1=r1|r2;

if((c0&&c1&&c2&&c3)==0)
{
row_val=0;
break;
}

//test for r1

IOCLR1=r1;
IOSET1=r0|r2;

if((c0&&c1&&c2&&c3)==0)
{
row_val=1;
break;
}

//test for r2

IOCLR1=r2;
IOSET1=r1|r0;

if((c0&&c1&&c2&&c3)==0)
{
row_val=2;
break;
}
}
if(c0==0)
col_val=0;
else if(c1==0)
col_val=1;
else if(c2==0)
col_val=2;
else
col_val=3;
delay_ms(150);
while((c0&c1&&c2&&c3)==0);
return key_lut[row_val][col_val];
}
//main function
int main()
{
int res;
LCD_INIT();
LCD_STR("3X4 KEYPAD");
while(1)
{
LCD_COMMAND(0xc0);
res=keyscan();
LCD_DATA((res%10)+48);
delay_ms(1000);
LCD_COMMAND(0x01);
}
}
