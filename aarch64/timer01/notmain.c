
// 2  outer corner
// 4
// 6
// 8  TX out
// 10 RX in

extern unsigned int GET32 ( unsigned int );
extern void PUT32 ( unsigned int, unsigned int );
extern void uart_init ( void );
extern void hexstring ( unsigned int );
extern void hexstrings ( unsigned int );

unsigned int read_cntpct_el0 ( void );

#define SYSTIMERCLO 0x3F003004

int notmain ( void )
{
    unsigned int ra,rb;
    uart_init();
    hexstring(0x12345678);


    //set to 0x06AAAAAB for us giving almost the same as the system timer
    //gives 19.2Mhz.
    //PUT32(0x40000008,0x80000000);
    //reduces but doesnt completely cover the gap to the system timer
    PUT32(0x40000008,0x06AAABC9);

    while(1)
    {
        ra=GET32(SYSTIMERCLO);
        rb=read_cntpct_el0();

        hexstrings(ra);
        hexstrings(ra-rb);
        hexstring(rb);
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
