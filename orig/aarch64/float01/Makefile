
ARMGNU ?= aarch64-none-elf

AOPS = --warn --fatal-warnings
COPS = -Wall -O2 -nostdlib -nostartfiles -ffreestanding 

gcc : kernel8.img

all : gcc

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.srec
	rm -f *.elf
	rm -f *.list
	rm -f *.img

vectors.o : vectors.s
	$(ARMGNU)-as $(AOPS) vectors.s -o vectors.o

notmain.o : notmain.c
	$(ARMGNU)-gcc $(COPS) -c notmain.c -o notmain.o

fun.o : fun.c 
	$(ARMGNU)-gcc $(COPS) -c fun.c -o fun.o

periph.o : periph.c 
	$(ARMGNU)-gcc $(COPS) -c periph.c -o periph.o

kernel8.img : memmap vectors.o periph.o notmain.o fun.o
	$(ARMGNU)-ld vectors.o periph.o notmain.o fun.o -T memmap -o notmain.elf
	$(ARMGNU)-objdump -D notmain.elf > notmain.list
	$(ARMGNU)-objcopy --srec-forceS3 notmain.elf -O srec notmain.srec
	$(ARMGNU)-objcopy notmain.elf -O binary kernel8.img


