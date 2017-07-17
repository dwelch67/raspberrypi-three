
//-------------------------------------------------------------------
//-------------------------------------------------------------------

.globl _start
_start:
    b skip
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang

    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang
    b hang

    b irq_handler





skip:
    mov sp,#0x08000000
    bl notmain
hang: b hang

.globl PUT32
PUT32:
  str w1,[x0]
  ret

.globl GET32
GET32:
    ldr w0,[x0]
    ret

.globl enable_irq
enable_irq:
    ldr x1,=0x00080000
    msr vbar_el2,x1
    //msr vbar_el3,x1
    //route to EL3
    //mrs x0,scr_el3
    //orr x0,x0,#8
    //orr x0,x0,#4
    //orr x0,x0,#2
    //msr scr_el3,x0
    //clear/enable irq bit in PSTATE
    msr daifclr,#2
    ret

irq_handler:
    //19 up are callee saved
    //so we have to preserve all below?
    stp x0,x1,[sp,#-16]!
    stp x2,x3,[sp,#-16]!
    stp x4,x5,[sp,#-16]!
    stp x6,x7,[sp,#-16]!
    stp x8,x9,[sp,#-16]!
    stp x10,x11,[sp,#-16]!
    stp x12,x13,[sp,#-16]!
    stp x14,x15,[sp,#-16]!
    stp x16,x17,[sp,#-16]!
    stp x18,x19,[sp,#-16]!

    //mrs x0,esr_el3
    bl c_irq_handler

    ldp x18,x19,[sp],#16
    ldp x16,x17,[sp],#16
    ldp x14,x15,[sp],#16
    ldp x12,x13,[sp],#16
    ldp x10,x11,[sp],#16
    ldp x8,x9,[sp],#16
    ldp x6,x7,[sp],#16
    ldp x4,x5,[sp],#16
    ldp x2,x3,[sp],#16
    ldp x0,x1,[sp],#16
    eret

.globl DOWFI
DOWFI:
    wfi
    //msr daifset,#2
    ret


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
