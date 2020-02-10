# stm32f103c8

Болванка для работы с STM32F103 / void & raw project for STM32F103
==================================================================

как пользоваться / how using
----------------------------

1) скачать/установить тулчейн / install toolchain

        $ sudo apt install gcc-arm-none-eabi

2) установить stm32flash / install stm32flash

        $ sudo apt install stm32flash

3) скачать проект / clone project

        $ git clone https://github.com/Denis-Maksimov/stm32f103c8.git

4) поёрзать шаловливыми ручками в проекте (но в основном в main.c) можно добавить новых файлов 
/ edit main.c and other files and/or create new *.c files

        $ nano ./main/main.c    (you are in stm32f103c8 folder)

5) для компиляции и сборки / for compile & build only

        $ make                  (You must be in the stm32f103c8 folder)

6) для компиляции и сборки и прошивки МК / for bootload programm in microcontroller

        $ make upload

optional:

*) дизассемблирование / disassembly

        $ make dizass

описание
--------
ещё не готово.. / TODO
