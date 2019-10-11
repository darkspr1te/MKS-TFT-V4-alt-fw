## MKS-TFT-V4-alt-fw
**This firmware source code provided here is not for Marlin/3d printer usage**
**pre-compiled .bin files provided are to restore factory funtionality only**

This is not firmware to provide original functionality but reuse the MKS board for a totally different purpose, 
reflash MKS firmware if you wish to use with Marlin.(original factory bootloader provided below)
This firmware is a Bring up of the board to enable the board to be used in new unforseen ways,
Listed below however are the original factory bootloaders for those that may have erased them. I have tested them on my own boards and confirm they work on a blank board, you are still required to flash the latest *firmware* for your device after via the sd-card for full original functionality. 
Thanks to https://github.com/delwinbest for pointing out my readme's poor explination, Hopefully these additions will clarify the difference between factory bootloader, factory firmware & my firmware and bootloaders. 


```
**mks-tft-32-v4-bootrom.bin**
 - For V4 Hardware, V3.0.0 software bootrom , Flash to 0x8000000 using stlink/jtag/bmp, then flash MKSTFT28.BIN via SD card

**MKS-TFT32-factory-boot.bin**
 - For V1/V2 Hardware with LCD Driver ID:9320, TFT28
**TFT_32_v3.0.3.rar**
 - The additional flash files fir V4 hardware including fonts, icons, firmware for flashing after bootrom (0x8007000)
	Can be flashed via SDCARD , filename MKSTFT28.BIN in root is file flashed, does not examine the data on filename'''
```	
	


#####Stm32Duino variant files and boards.txt 

__boards.txt__ additions
```
MKSTFT_F107VC test mkstft
Genericflight.menu.pnum.MKSTFT_F107VC=MKS TFT32 V4
Genericflight.menu.pnum.MKSTFT_F107VC.upload.maximum_size=262144
Genericflight.menu.pnum.MKSTFT_F107VC.upload.maximum_data_size=60032
Genericflight.menu.pnum.MKSTFT_F107VC.build.flash_offset=0x7000
Genericflight.menu.pnum.MKSTFT_F107VC.build.startup_file=-DCUSTOM_STARTUP_FILE
Genericflight.menu.pnum.MKSTFT_F107VC.build.build.ldscript=ldscript.ld
Genericflight.menu.pnum.MKSTFT_F107VC.build.board=MKSTFT_F107VC
Genericflight.menu.pnum.MKSTFT_F107VC.build.series=STM32F1xx
Genericflight.menu.pnum.MKSTFT_F107VC.build.product_line=STM32F107xC
Genericflight.menu.pnum.MKSTFT_F107VC.build.variant=MKSTFT_F107VC
```
if you intend to use full flash etc and not use Makerbase bootloader then also adjust your flashoffset,ram,entry vectors etc




and i compile using maple upload method and then copy bin file to sdcard
```
Genericflight.menu.upload_method.dfuoMethod=Maple DFU Bootloader original
Genericflight.menu.upload_method.dfuoMethod.upload.protocol=maple
Genericflight.menu.upload_method.dfuoMethod.upload.tool=maple_upload
Genericflight.menu.upload_method.dfuoMethod.upload.usbID=1EAF:0003
Genericflight.menu.upload_method.dfuoMethod.upload.altID=1
Genericflight.menu.upload_method.dfuoMethod.build.flash_offset=0x7000
Genericflight.menu.upload_method.dfuoMethod.build.bootloader_flags=-DBL_LEGACY_LEAF -DVECT_TAB_OFFSET={build.flash_offset}
```
