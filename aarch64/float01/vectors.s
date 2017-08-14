
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

skip:


    //set EL1 to aarch64
    mov x1,#0x80000000
	msr	hcr_el2,x1

    //disable traps
    //before 00C50838
    //Just set the res1 bits
    ldr x0,=0x00C00800
	msr	sctlr_el1,x0
    //after 0x00C00800

    ldr x0,=0x00300000
    msr cpacr_el1,x0

	mov	x0,#0x3c5  
	msr	spsr_el2,x0
    //ldr x0,=enter_el1
	adr	x0,enter_el1
	msr	elr_el2, x0
	eret
enter_el1:



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

.globl GETPC
GETPC:
    mov x0,x30
    ret

.globl BRANCHTO
BRANCHTO:
    mov w30,w0
    ret


.globl getel
getel:
    mrs x0, CurrentEL
    ret

.globl read_fpexc
read_fpexc:
    mrs x0,fpexc32_el2
    ret


.globl read_cpacr
read_cpacr:
    mrs x0,cpacr_el1
    ret

.globl dummy
dummy:
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
