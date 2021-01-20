# bigKNOB firmware update
First you need a new firmware:
https://config.qmk.fm/#/leafcutterlabs/bigknob/LAYOUT
Select the functions for the buttons and click compile.
Once the firmware is compiled, download and save the hex file.
![](https://github.com/LeafCutterLabs/bigKNOB/blob/master/Media/configurator.png)
Download/install QMK toolbox.
Select the hex file, set MCU to atmega32u4, and check Auto-Flash.
![](https://github.com/LeafCutterLabs/bigKNOB/blob/master/Media/toolbox.png)
Press the button under the unit (may have a small hole in the case). The unit should reboot and load the new firmware.
![](https://github.com/LeafCutterLabs/bigKNOB/blob/master/Media/underbutton.jpg)
