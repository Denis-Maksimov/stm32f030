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


Структура проекта
=================

В корне проекта лежат файлы:

- link.ld    -> это скрипт линковщика для распределения памяти прошивки
- Makefile   -> это скрипт для сборки и прошивки
- .gitignore -> для игнорирования системой контроля версий лишних файлов (например бинарников)

и две папки:

папка core
----------
в ней находится ассемблерный файл boot.s. В начале идёт адрес вершины стека адрес начала программы таблица векторов прерываний. Программа берёт своё начало на метке "start" на которой происходит зануление оперативной памяти, проброс инициализированных переменных из флеша в оперативку, ну и прыжок в main

папка main
----------
в корне папки файлы init и main - это код для прикладной программы.
Вложенные папки представляют собой тот или иной функционал железа (periph), переключения контекста для организации простейшей многопоточности (system), внешние устройства(devices) и различные библиотеки (stdLib,modbus[TODO]).  

Добавление новых файлов и папок не требует правки Makefile, но имена файлов должны быть уникальными

заметки
=================

- для записи по адресу применять REGISTER(адресс);
- при компиляции папки "выворачиваются", т.о. не важно где заголовочный файл, а где исходник.
