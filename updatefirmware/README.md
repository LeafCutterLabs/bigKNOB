# bigKNOB firmware update
First you need a new firmware:
https://config.qmk.fm/#/leafcutterlabs/bigknob/LAYOUT
![](Media/configurator.png)
Select the functions for the buttons and click compile.
Once the firmware is compiled, download and save the hex file.
![](Media/toolbox.png)
Download/install QMK toolbox.
Select the hex file, set MCU to atmega32u4, and check Auto-Flash.
![](Media/underbutton.jpg)
Press the button under the unit (may have a small hole in the case). The unit should reboot and load the new firmware.
