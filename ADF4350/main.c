
#include <STC15Fxxxx.H>

void DelayUs2x(unsigned char t);
void DelayMs(unsigned int t);
sbit CLK=P2^5;
sbit LE=P2^2;
sbit DATA=P1^2;
//Set Registers
#define R0 0X2C0010
#define R1 0X800E1A9
#define R2 0X18004E42
#define R3 0X4B3
#define R4 0XCC803C
#define R5 0X580005


#include <stc15fxxxx.h>
/*************Constant****************/

#define MAIN_Fosc                               22118400L       //Main clock
#define serial_one_read_max         32                  //Buffer length
#define serial_one_baud_rate        115200L        
#define Timer1_Reload                       (65536UL -(MAIN_Fosc / 4 / serial_one_baud_rate))  
#define Freq_init                   1800000     

/*************variables****************/
u8  serial_one_read_data[serial_one_read_max];  
u8  serial_one_read_count=0;                                        
char buffer[serial_one_read_max];
unsigned long f; 

//port initiate
void serial_one_init()
{
    SCON |= 0x40;               //8 bits data
    P_SW1 &=  ~0xc0;       
    TR1 = 0;                   
    AUXR &= ~0x01;     //S1 BRT Use Timer1;
    TMOD &= ~(1<<6);   //Timer1 set As Timer
    TMOD &= ~0x30;     //Timer1_16bitAutoReload;2
    AUXR |=  (1<<6);    //Timer1 set as 1T mode
    TH1 = (u8)(Timer1_Reload >> 8);
    TL1 = (u8)Timer1_Reload;
    TR1  = 1;                   
    PS = 1; 
    REN = 1;    
    ES  = 1;    

    EA = 1;     
}

//delay 10ms
void Delay10ms()        //@22.1184MHz
{
    unsigned char i, j, k;

    _nop_();
    _nop_();
    i = 1;
    j = 216;
    k = 35;
    do
    {
        do
        {
            while (--k);
        } while (--j);
    } while (--i);
}

//send 1 byte
void serial_one_send_byte(u8 dat)
{
    SBUF = dat;//send data
    while(!TI);
    TI=0;           
}


void serial_one_send_string(u8 *dat)
{
    while(*dat)
        serial_one_send_byte(*dat++);
}


void serial_one_send_length_string(u8 *dat,u8 length)
{
    u8 i=0;
    for(;i < length;i++)
        serial_one_send_byte(dat[i]);
}

/********************* interruption of port1************************/
void UART1_int (void) interrupt UART1_VECTOR
{
    if(RI)
    {
        RI = 0;
        serial_one_read_data[serial_one_read_count] = SBUF;
        if(++serial_one_read_count > serial_one_read_max) 
            serial_one_read_count = 0;
    }

//  if(TI)
//  {
//  }
}

//Function that writes to the ADF435x via the SPI port.
//--------------------------------------------------------------------------------
void WriteToADF435X(unsigned long BUF)
{unsigned char i = 0,	j = 0;
  unsigned long ValueToWrite = 0;
  ValueToWrite =BUF;
  CLK=0;LE=0;
  for(j=0; j<32; j++)
     {if(0x80000000 == (ValueToWrite & 0x80000000))
       {DATA=1;}   //Send one to SDO pin
       else{DATA=0;}   //Send zero to SDO pin   
       CLK=1;
       ValueToWrite <<= 1; //Rotate data
       CLK=0;
      }
  CLK=0;
  LE=1;LE=0;
}
void  WriteFreq(unsigned long Freq)	 //137500KHZ
{float Freq_temp;
 unsigned long 	INT,FRAC,MODE=3125; 
 unsigned long R0_temp=0;  //Control INT  FRAC
 unsigned long R4_temp=0; // 2.2GHZ--4.4GHZ/1.1GHZ--2.2GHZ/550MHZ--1.1GHZ/275MHZ--550MHZ/137.5MHZ--275MHZ
 unsigned long  Out_Divider,RF_Divider; 
if((34375<=Freq)&&(Freq<68750))  {Out_Divider=6;RF_Divider=64;}   //ADF4351
if((68750<=Freq)&&(Freq<137500)) {Out_Divider=5;RF_Divider=32;}   //ADF4351                                                          
if((137500<=Freq)&&(Freq<275000)){Out_Divider=4;RF_Divider=16;} 
if((275000<=Freq)&&(Freq<550000)){Out_Divider=3;RF_Divider=8;}
if((550000<=Freq)&&(Freq<1100000)){Out_Divider=2;RF_Divider=4;}
if((1100000<=Freq)&&(Freq<2200000)){Out_Divider=1;RF_Divider=2;}
if((2200000<=Freq)&&(Freq<4400000)){Out_Divider=0;RF_Divider=1;}

  R4_temp=((R4&0XFF8FFFFF)|(Out_Divider<<20));
  WriteToADF435X(R4_temp);
 
 Freq_temp=Freq;   
 Freq_temp=(Freq_temp*RF_Divider)/25000;
     INT  =(int)Freq_temp;
	 FRAC=	(Freq_temp-INT)*MODE;
R0_temp=((INT<<15)|(FRAC<<3))&0x7fffff8;
 WriteToADF435X(R0_temp);

}


void main(void)
{ 
 DelayMs(5000);
 //initiate twice
 WriteToADF435X(R0);
 WriteToADF435X(R1);
 WriteToADF435X(R2);
 WriteToADF435X(R3);
 WriteToADF435X(R4);
 WriteToADF435X(R5);   
 
 WriteToADF435X(R0);
 WriteToADF435X(R1);
 WriteToADF435X(R2);
 WriteToADF435X(R3);
 WriteToADF435X(R4);
 WriteToADF435X(R5);

 Delay10ms();//delay 10ms
 Delay10ms();//delay 10ms
 serial_one_init();//initiate port

 WriteFreq(Freq_init); 
 while(1)
 {
    if(serial_one_read_count > 0)//if data received
    {
      Delay10ms();//delay
      //serial_one_send_length_string(serial_one_read_data,serial_one_read_count);
      serial_one_read_count = 0;
	  WriteFreq(serial_one_read_data);	
    }
 }

}



void DelayUs2x(unsigned char t)
{
 while(--t);
}

void DelayMs(unsigned int t)
{
     
 while(t--)
 {
     //delay 1ms
     DelayUs2x(245);
	 DelayUs2x(245);
 }
}

