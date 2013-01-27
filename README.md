# CuePie - Raspberry Pi and Cuecat get friendly

## Build

```bash
gcc -o cuepie cuepie.c
```

## Run

```bash
./cuepie /dev/input/event1
```

Cuepie assumes event0 if you don't give it an arguement.  If your cuecat is the only usb input device plugged into your raspberry pi, this is most likely correct.  

Outside of our current scope, you could set up udev rules to give the cuecat something more obvious like /dev/input/cuecat, then you never have to worry about what else gets plugged in.

## Current Status

it gets scans correctly, and outputs them to stdout.   

## Hopeful endpoint

Service running on rPi that catches cuecat attach, and pumps barcodes scanned into a file/fifo/pipe to a program.

## Liberally stolen from:
http://www.thelinuxdaily.com/2010/05/grab-raw-keyboard-input-from-event-device-node-devinputevent/

