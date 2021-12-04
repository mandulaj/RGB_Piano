# RGB_Piano

Simple LED stip lights controlled by Piano keys

### How it works

I am decoding the MIDI using `aseqdump` on my computer and sending the actions via Serial to a Arduino MEGA, which displays the keys on the WS2812B RGB strip. There is a possiblitity to also change the brightness based on the key velocity, but I haven't implemented that yet. 

-----

![Video Gif](video.gif)

### How to get it working

The implementation is not very user friendly as I tried to get everything working quickly. You will have to modify the `PianoArduino.ino` sketch to match your set up. In particular you have to modify these defines in order to match the number of LEDs on your strip, the number of your keys and the update interval. I used the FastLED library for controling the RGB strip on pin 7 of the Arduino MCU. 


```c
#define NUM_LEDS 74
#define NUM_KEYS 88
#define UPDATE_INT 50
```

You migh also have to play around with some of the offsets in order to get your lights aligned with the keys.


Next, after flashing the sketch to the Arduino, you have to connect your MIDI keyboard and the arduino to the computer and start

```bash
python midi2serial.py
```

This uses `MIDI_CHAN 20` for the MIDI source and `/dev/ttyUSB0` for the Arduino Serial destination. Change those based on your needs.

Hopefully now your computer should be sending the MIDI data over to the Arduino which will be flashing the RGB LEDs.
