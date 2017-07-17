
// 2  outer corner
// 4
// 6
// 8  TX out
// 10 RX in

extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern void dummy ( unsigned int );

extern void uart_init ( void );
extern void uart_send ( unsigned int );

#define GPFSEL2 0x3F200008
#define GPSET0  0x3F20001C
#define GPCLR0  0x3F200028

int notmain ( void )
{
    unsigned int ra;
    unsigned int rb;

    ra=GET32(GPFSEL2);
    ra&=~(7<<3);
    ra|=1<<3;
    PUT32(GPFSEL2,ra);

    uart_init();

    while(1)
    {
        for(rb=0;rb<32;rb++)
        {
            PUT32(GPSET0,1<<21);
            uart_send(0x55);
            for(ra=0;ra<0x100000;ra++) dummy(ra);
            PUT32(GPCLR0,1<<21);
            uart_send(0x56);
            for(ra=0;ra<0x100000;ra++) dummy(ra);
        }
        uart_send(0x0D);
        uart_send(0x0A);
    }

    return(0);
}

//-------------------------------------------------------------------------
//
// Copyright (c) 2014 David Welch dwelch@dwelch.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------
