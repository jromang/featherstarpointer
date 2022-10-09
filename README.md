# Feather Star Pointer

:warning: **Azimuth accuracy is based on a magnetometer : so currently, you can have a 2° error margin in azimuth**

The goal of this project is to be a  simple star pointing system for push-to telescopes, using the [SkySafari Pro](https://skysafariastronomy.com/skysafari-7-professional-astronomy-telescope-control-software-for-android.html) application on your smartphone.

### Components
- [Adafruit Featherboard ESP32 V2](https://www.adafruit.com/product/5400)
- [Adafruit BNO055 Absolute Orientation Sensor](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor)
- [STEMMA QT / Qwiic JST SH 4-Pin Cable - 50mm Long](https://www.adafruit.com/product/4399)
- [Lithium Ion Polymer Battery](https://www.adafruit.com/product/3898)
- 3D printed case and holder (you will find [ready to print STL](https://github.com/jromang/featherstarpointer/tree/main/stl) files in this repo)
- A smartphone (Android/IOS) with the [SkySafari Pro](https://skysafariastronomy.com/skysafari-7-professional-astronomy-telescope-control-software-for-android.html) application
- Optional [Jack JST PH 2.0/2.0mm Male/Female](https://fr.aliexpress.com/item/1005002657347265.html?spm=a2g0o.order_list.0.0.21ef5e5bcTvBVH)
- Optional [Self locking switch](https://fr.aliexpress.com/item/4000164264475.html?spm=a2g0o.order_list.0.0.6cba5e5b0LTYn6)

### How to build
- There is not soldering involved, just connect the Featherboard, the sensor, and the battery with the cable connectors
- You will need to flash the [binary firmware](https://github.com/jromang/featherstarpointer/tree/main/sketch/fsp)  to the Featherboard
- You have to glue the 3D printed base to the 3d printed holder

### How to use
- Follow the [calibration procedure](https://learn.adafruit.com/adafruit-bno055-absolute-orientation-sensor/device-calibration) at startup : the white LED will turn red when the calibration is finished.
- Add the FSP as a 'basic encoder system' in skysafari, choose 'push-to  Alt-az', and connect using bluetooth. Finally set the encoder settings to +8192 (both fields).
- The red LED will start to blink when the battery is low.
- Enjoy !

### Pictures

 ![Mounted on scope](https://github.com/jromang/featherstarpointer/raw/main/media/mounted.jpeg)
 
 ![Inside](https://github.com/jromang/featherstarpointer/raw/main/media/inside.jpeg)
 
 ![Switch](https://github.com/jromang/featherstarpointer/blob/main/media/switch2.jpeg)
 
 ![3D Model](https://github.com/jromang/featherstarpointer/raw/main/media/openscad_model.png)
 
 ![SkySafari](https://www.webastro.net/uploads/monthly_2019_08/Screenshot_2019-08-28-13-16-45-940_com.simulationcurriculum.skysafari5pro.png.d8d3513f8f01f341cc7b48845134fe49.png)
