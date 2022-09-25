# Feather Star Pointer
Feather Star Pointer

:warning: This is still very experimental :warning:

The goal of this project is to be a  simple star pointing system for push-to telescopes, using the [SkySafari Pro](https://skysafariastronomy.com/skysafari-7-professional-astronomy-telescope-control-software-for-android.html) application on your smartphone.

Components :
- [Adafruit Featherboard ESP32 V2](https://www.adafruit.com/product/5400)
- [Adafruit BNO055 Absolute Orientation Sensor](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor)
- [STEMMA QT / Qwiic JST SH 4-Pin Cable - 50mm Long](https://www.adafruit.com/product/4399)
- [Lithium Ion Polymer Battery](https://www.adafruit.com/product/3898)
- 3D printed case and holder (You will find ready to print STL files in this repo)
- A smartphone (Android/IOS) with the [SkySafari Pro](https://skysafariastronomy.com/skysafari-7-professional-astronomy-telescope-control-software-for-android.html) application

How to build
- There is not soldering involved, just connect the Featherboard, the sensor, and the battery with the cable connectors
- You will need to flash the [binary firmware](https://github.com/jromang/featherstarpointer/tree/main/sketch/fsp)  to the Featherboard)
- You have to glue the 3D printed base to the 3d printed holder

How to use :
- Follow the [calibration procedure](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/device-calibration) at startup : the white LED will turn green when the calibration is finished.
- Add the FSP as a 'basic encoder system' in skysafari, choose 'push-to  Alt-az', and connect using bluetooth. Finally set the encoder settingd to +8192 (both fields).
- Enjoy !
