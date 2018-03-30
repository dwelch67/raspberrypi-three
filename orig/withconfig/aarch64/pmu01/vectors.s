
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

//.space 0x80000-0x0020,0

skip:
    mrs x0,mpidr_el1
    mov x1,#0xC1000000
    bic x1,x0,x1
    cbz x1,zero
not_zero:
    wfi
    b not_zero
zero:

    mov sp,#0x08000000
    bl notmain
hang: b hang

.globl PUT32
PUT32:
  str w1,[x0]
  ret

.globl PUT8
PUT8:
  strb w1,[x0]
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

.globl mpidr
mpidr:
    mrs x0,mpidr_el1
    ret

.globl getel
getel:
    mrs x0, CurrentEL
    ret


.globl read_PMCR
read_PMCR:
    mrs x0, PMCR_EL0
    ret

.globl write_PMCR
write_PMCR:
    msr PMCR_EL0, x0
    ret

.globl read_PMCEID0
read_PMCEID0:
    mrs x0, PMCEID0_EL0
    ret

.globl read_PMCEID1
read_PMCEID1:
    mrs x0, PMCEID1_EL0
    ret

.globl read_PMUSERENR
read_PMUSERENR:
    mrs x0, PMUSERENR_EL0
    ret

.globl write_PMUSERENR
write_PMUSERENR:
    msr PMUSERENR_EL0,x0
    ret


.globl read_PMSELR
read_PMSELR:
    mrs x0, PMSELR_EL0
    ret

.globl write_PMSELR
write_PMSELR:
    msr PMSELR_EL0,x0
    ret

.globl read_PMEVTYPER0
read_PMEVTYPER0:
    mrs x0, PMEVTYPER0_EL0
    ret

.globl write_PMEVTYPER0
write_PMEVTYPER0:
    msr PMEVTYPER0_EL0,x0
    ret

.globl read_PMEVTYPER1
read_PMEVTYPER1:
    mrs x0, PMEVTYPER1_EL0
    ret

.globl write_PMEVTYPER1
write_PMEVTYPER1:
    msr PMEVTYPER1_EL0,x0
    ret

.globl read_PMCCFILTR
read_PMCCFILTR:
    mrs x0, PMCCFILTR_EL0
    ret

.globl write_PMCCFILTR
write_PMCCFILTR:
    msr PMCCFILTR_EL0,x0
    ret



.globl write_PMCNTENSET
write_PMCNTENSET:
    msr PMCNTENSET_EL0,x0
    ret

.globl write_PMCNTENCLR
write_PMCNTENCLR:
    msr PMCNTENCLR_EL0,x0
    ret


.globl read_PMCCNTR
read_PMCCNTR:
    mrs x0, PMCCNTR_EL0
    ret


.globl dummy
dummy:
    ret



.globl TEST1
TEST1:
    msr PMCNTENSET_EL0,x0
    msr PMCNTENCLR_EL0,x0
    ret

   
.globl TEST2
TEST2:
    msr PMCNTENSET_EL0,x0
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    msr PMCNTENCLR_EL0,x0
    ret


.globl TEST3
TEST3:
    msr PMCNTENSET_EL0,x0
    nop
test3x:
    subs w1,w1,#1
    b.ne test3x
    msr PMCNTENCLR_EL0,x0
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
