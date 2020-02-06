
FOLDERS :=$(shell find . -type d)
FOLDERS:=$(addprefix -I, $(FOLDERS))

CFLAGS := -nostdlib -nostartfiles -ffreestanding\
		 -Wall -mcpu=cortex-m3 -march=armv7-m -mthumb \

CFLAGS :=$(CFLAGS) $(FOLDERS)

FILES :=$(shell find . -name '*.c')
OBJ:=$(patsubst %.c, %.o,$(FILES))

start: binary.bin




boot.o:	./core/boot.s
		#1 Готовим ассемблерный файл
		arm-none-eabi-as ./core/boot.s -o boot.o
		

bin: $(FILES)
		#2 компилим
		arm-none-eabi-gcc $(FILES) $(CFLAGS) -c
		

build.elf: bin boot.o
		#3 Линкуем
		arm-none-eabi-ld -o build.elf -T link.ld  *.o # -M 

binary.bin: build.elf
		#4 Извлекаем бинарные данные
		arm-none-eabi-objcopy build.elf binary.bin -O binary
		
		
dizass: $(FILES)
		arm-none-eabi-gcc $(FILES) $(CFLAGS) -S

upload: binary.bin
		#Загружаем в МК
		sudo stm32flash -w binary.bin  -v -g 0x000000000800099c /dev/ttyUSB0



clean:
		rm -f $(shell find . -name '*.o')
		rm -f $(shell find . -name '*.elf')
		rm -f $(shell find . -name '*.bin')



