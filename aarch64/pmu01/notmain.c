
// 2  outer corner
// 4
// 6
// 8  TX out
// 10 RX in

extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void dummy ( unsigned int );

extern void uart_init ( void );
extern void uart_send ( unsigned int );
extern unsigned int uart_recv ( void );
extern void hexstring ( unsigned int );
extern void hexstrings ( unsigned int );
extern void uart_flush ( void );

unsigned int read_PMCR ( void );
void write_PMCR ( unsigned int );
unsigned int read_PMCEID0 ( void );
unsigned int read_PMCEID1 ( void );
unsigned int read_PMUSERENR ( void );
void write_PMUSERENR ( unsigned int );
unsigned int read_PMSELR ( void );
void write_PMSELR ( unsigned int );
unsigned int read_PMEVTYPER0 ( void );
void write_PMEVTYPER0 ( unsigned int );
unsigned int read_PMEVTYPER1 ( void );
void write_PMEVTYPER1 ( unsigned int );
unsigned int read_PMCCFILTR ( void );
void write_PMCCFILTR ( unsigned int );
void write_PMCNTENSET ( unsigned int );
void write_PMCNTENCLR ( unsigned int );
unsigned int read_PMCCNTR ( void );
void TEST1 ( unsigned int );
void TEST2 ( unsigned int );
void TEST3 ( unsigned int, unsigned int  );

int notmain ( void )
{
    //unsigned int ra;
    //unsigned int rb;

    uart_init();
    hexstring(0x12345678);
    hexstring(read_PMCR()); //0x41033000
    //When enabled, PMCCNTR_EL0 counts every clock cycle. This is the reset value.
    hexstring(read_PMCEID0());
    //67FFBFFF 
    hexstring(read_PMCEID1());
    //00000000 
    hexstring(read_PMUSERENR());
    write_PMUSERENR(read_PMUSERENR()|0xD); //should just leave it zero
    hexstring(read_PMUSERENR());

    write_PMSELR(0);
    hexstring(read_PMEVTYPER0());
    write_PMSELR(1);
    hexstring(read_PMEVTYPER1());
    
    write_PMSELR(0);
    write_PMEVTYPER0(0x00000008);
//0x0008 , INST_RETIRED, Instruction architecturally executed
//The counter increments for every architecturally executed instruction.

    write_PMSELR(0);
    hexstring(read_PMEVTYPER0());
    write_PMSELR(1);
    hexstring(read_PMEVTYPER1());
    hexstring(read_PMCCFILTR());
    write_PMCCFILTR(0x00000000);
    hexstring(read_PMCCFILTR());
    write_PMCR(read_PMCR()|0x7);

    
    write_PMCNTENSET(0x80000001);
    //dummy(0);
    write_PMCNTENCLR(0x80000001);
    hexstring(read_PMCCNTR());
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    hexstring(read_PMCCNTR());

    //write_PMCR(read_PMCR()&(~0x7));
    //write_PMCR(read_PMCR()|0x7);
    write_PMCR(read_PMCR()|0x7);
    TEST1(0x80000001);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST1(0x80000001);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST2(0x80000001);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST2(0x80000001);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST2(0x80000001);
    hexstring(read_PMCCNTR());

    
    write_PMCR(read_PMCR()|0x7);
    TEST3(0x80000001,0x10000);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST3(0x80000001,0x10000);
    hexstring(read_PMCCNTR());
    write_PMCR(read_PMCR()|0x7);
    TEST3(0x80000001,0x1000);
    hexstring(read_PMCCNTR());



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
