### Arduino ISP:

* https://crycode.de/arduino-als-isp-programmer

|2|4|6|
|-|-|-|
|VCC|MOSI|GND|
|MISO|SCK|RST|
|1|3|5|

```
sudo avrdude -c stk500v1 -b 19200 -P /dev/ttyUSB0 -p m328p -U lfuse:w:0xff:m -U hfuse:w:0xd8:m -U efuse:w:0xff:m -U lock:w:0x2F:m
sudo avrdude -c stk500v1 -b 19200 -P /dev/ttyUSB0 -p m328p -U flash:w:./builds/grids/grids.hex
```

### Midi-Input Implementation
 * Start, Stop, Continue
 * C0 (12) -> Reset Pattern
 * Midi-Probability-Triger ( Velocity < Random )
    * D0 (14) = BD or BD-Acc
    * E0 (16) = SD or SD-Acc
    * F0 (17) = HH or HH-Acc
    * G0 (19) = JP1-A or JP1-B