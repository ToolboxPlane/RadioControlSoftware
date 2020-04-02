# RadioControlSoftware
## Building and deploy
### Compile
To compile the firmware run:
```
cmake . && make
```

### How to flash to firmware
This assumes that an arduino based board with USB-Bootloader 
is used (mounted at `/dev/ttyACM0`), 
if you use a different programmer change the ```-c``` flag.
```bash
avrdude -p m328p -b 115200 -c arduino -P /dev/ttyACM0 -U flash:w:RadioControlSoftware.hex:i

```


## Output Package
| Channel | Value |
| --- | --- |
| 0 | Right-X |
| 1 | Right-Y |
| 2 | Left-X |
| 3 | Left-Y |
| 4 | Flightmode |
| 5 | Armed |
| 6 | Empty |
| 7 | -RSSI |

All Joystick values are between 0 and 255 with 127 being center.

### Flightmodes
| Flightmode | Number |
| --- | --- |    
| RTH | 0|
| LAUNCH | 1|
| LAND | 2|
| LOITER | 3|
| WAYPOINT | 4
