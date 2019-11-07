**for Original firmware see https://github.com/darkspr1te/MKS-TFT-V4-orig-fw

**Alternate firmware for MKS-TFT
basic bring up of board, working lcd, speaker, uart0,uart1, spi mem, sdcard

** Alternate bootloader 
https://github.com/delwinbest/stm32f107_bootloader


**  backup bootloader
https://github.com/delwinbest/stm32f107_boot_rom_reader
or mine via mks orig repo and it's based on arduino + stm32duino official repo 
 

Files contained here:-

lcd-test - Basic lcd test , landscape , original code from UTFT lib


Working :-
LCD, Buzzer, SDCARD, Touch screen, EEPROM, flash, UART1/2 
*Does not need bootloader any more, faster development flashing via SWD 


To Do:-
fix LCD init code, add additional pins to variant.h 



