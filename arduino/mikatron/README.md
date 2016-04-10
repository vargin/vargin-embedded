# General

Project template is generated with the following command:

```
platformio init --ide clion --board attiny85
```

Source code is uploaded to microcontroller via Arduino UNO ISP, see `platformio.ini`:

```
[env:attiny85]
platform = atmelavr
framework = arduino
board = attiny85
upload_protocol = stk500v1
upload_flags = -P$UPLOAD_PORT -b$UPLOAD_SPEED

# Arduino ISP programmer settings
upload_port = /dev/ttyACM0
upload_speed = 19200
```