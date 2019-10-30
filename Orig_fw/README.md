# MKS-TFT-V4-orig-fw
Original bootloader for MKS-TFT32 V1 & V4 Hardware
For use with Marlin board using MKS firmware

```
**MKS-TFT32-v4-factory-boot.bin**
 - For V4 Hardware, V3.0.0 software bootrom , Flash to 0x8000000 using stlink/jtag/bmp, then flash MKSTFT28.BIN via SD card
**mks-tft-32-fw-dump.ino 
 - Simple arduino program written to backup the bootloader , has to have bootvect of 0x7000 for original boot loader to execute , take compiled bin from arduino compile dir and place on sdcard with firmware 
 filename applicable to your model 
**MKS-TFT32-v1-factory-boot.bin**
 - For V1/V2 Hardware with LCD Driver ID:9320, TFT28
**TFT_32_v3.0.3.rar**
 - The additional flash files for V4 hardware including fonts, icons, firmware for flashing after bootrom (0x8007000)
	Can be flashed via SDCARD , filename MKSTFT28.BIN in root is file flashed, does not examine the data on filename
	'''
```	
	