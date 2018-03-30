
//-------------------------------------------------------------------
//-------------------------------------------------------------------

extern void PUT32 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );
extern void enable_irq ( void );
extern void DOWFI ( void );

extern void uart_init ( void );
extern void uart_send ( unsigned int );
extern void hexstring ( unsigned int );


#define GPFSEL2 0x3F200008
#define GPSET0  0x3F20001C
#define GPCLR0  0x3F200028


#define ARM_TIMER_LOD 0x3F00B400
#define ARM_TIMER_VAL 0x3F00B404
#define ARM_TIMER_CTL 0x3F00B408
#define ARM_TIMER_CLI 0x3F00B40C
#define ARM_TIMER_RIS 0x3F00B410
#define ARM_TIMER_MIS 0x3F00B414
#define ARM_TIMER_RLD 0x3F00B418
#define ARM_TIMER_DIV 0x3F00B41C
#define ARM_TIMER_CNT 0x3F00B420

#define SYSTIMERCLO 0x3F003004
#define GPFSEL1 0x3F200004
#define GPSET0  0x3F20001C
#define GPCLR0  0x3F200028
#define GPFSEL3 0x3F20000C
#define GPFSEL4 0x3F200010
#define GPSET1  0x3F200020
#define GPCLR1  0x3F20002C

#define IRQ_BASIC 0x3F00B200
#define IRQ_PEND1 0x3F00B204
#define IRQ_PEND2 0x3F00B208
#define IRQ_FIQ_CONTROL 0x3F00B210
#define IRQ_ENABLE_BASIC 0x3F00B218
#define IRQ_DISABLE_BASIC 0x3F00B224

volatile unsigned int icount;

//-------------------------------------------------------------------
// THIS IS AN INTERRUPT HANDLER DONT MESS AROUND
void c_irq_handler ( void )
{
    icount++;
    if(icount&1)
    {
        PUT32(GPSET0,1<<21);
        uart_send(0x55);
    }
    else
    {
        PUT32(GPCLR0,1<<21);
        uart_send(0x56);
    }
    PUT32(ARM_TIMER_CLI,0);
}
//-------------------------------------------------------------------
int notmain ( void )
{
    unsigned int ra;

    PUT32(IRQ_DISABLE_BASIC,1);

    ra=GET32(GPFSEL2);
    ra&=~(7<<3);
    ra|=1<<3;
    PUT32(GPFSEL2,ra);

    uart_init();
if(1)
{
    PUT32(ARM_TIMER_CTL,0x003E0000);
    PUT32(ARM_TIMER_LOD,1000000-1);
    PUT32(ARM_TIMER_RLD,1000000-1);
    PUT32(ARM_TIMER_DIV,0x000000F9);
    PUT32(ARM_TIMER_CLI,0);
    PUT32(ARM_TIMER_CTL,0x003E00A2);

    for(ra=0;ra<2;ra++)
    {
        PUT32(GPSET0,1<<21);
        uart_send(0x55);
        while(1) if(GET32(ARM_TIMER_MIS)) break;
        PUT32(ARM_TIMER_CLI,0);

        PUT32(GPCLR0,1<<21);
        uart_send(0x56);
        while(1) if(GET32(ARM_TIMER_MIS)) break;
        PUT32(ARM_TIMER_CLI,0);
    }
    uart_send(0x0D);
    uart_send(0x0A);
}
if(1)
{
    PUT32(ARM_TIMER_CTL,0x003E0000);
    PUT32(ARM_TIMER_LOD,2000000-1);
    PUT32(ARM_TIMER_RLD,2000000-1);
    PUT32(ARM_TIMER_CLI,0);
    PUT32(IRQ_ENABLE_BASIC,1);
    PUT32(ARM_TIMER_CTL,0x003E00A2);
    for(ra=0;ra<3;ra++)
    {
        PUT32(GPSET0,1<<21);
        uart_send(0x55);
        while(1) if(GET32(IRQ_BASIC)&1) break;
        PUT32(ARM_TIMER_CLI,0);

        PUT32(GPCLR0,1<<21);
        uart_send(0x56);
        while(1) if(GET32(IRQ_BASIC)&1) break;
        PUT32(ARM_TIMER_CLI,0);
    }
    PUT32(IRQ_ENABLE_BASIC,0);
    uart_send(0x0D);
    uart_send(0x0A);
}

    PUT32(ARM_TIMER_CTL,0x003E0000);
    PUT32(ARM_TIMER_LOD,500000-1);
    PUT32(ARM_TIMER_RLD,500000-1);
    PUT32(ARM_TIMER_CLI,0);
    PUT32(IRQ_ENABLE_BASIC,1);
    icount=0;
    enable_irq();
    //hexstring(1); //did I hang in the above function?
    PUT32(ARM_TIMER_CTL,0x003E00A2);
    PUT32(ARM_TIMER_CLI,0);

    while(1)
    {
        DOWFI();
        uart_send(0x33);
    }
    return(0);
}
//-------------------------------------------------------------------
//-------------------------------------------------------------------

//-------------------------------------------------------------------
//
// Copyright (c) 2012 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------
