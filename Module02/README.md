# Module 2

We are going to show here notes for Task 1, 2, 3, 4, and 5 to prove
## Week 1

## Task 1
add together resistor, corrent and led. Led-s only 1 way, red led needs less voltage then blue/white. The color comes from the distance.
R=(Vsupply-Vled)/Iled. R-value of resistor (in class 330 ohm). Ohm is potential energy and how much volume goes through it.



Why esp8266? Automatic daily tasks. Chip is 1 dollar, it should change how we design things. sonoff basic, has relay built in. You can attach various sensors, buttons, little screen and so on. Can connect to usb port. Can be used to bridge hardware and software.

coffe? priced the same as a little coffee.

relator - 


Power Consumption
NodeMCU: Slightly higher power consumption due to the onboard voltage regulator.
WeMos D1 Mini: Lower power consumption, making it better for battery-powered applications.
NodeMCU does not have stackable shields and is more expensive, bigger board

blew up a circut board.

task.2

This task was executed by myself.you can use a seperate power source






## Reflection 2
Blew up a circut board. But made good schematics and tried out different stuff. 
if you but 2 LED-s together, then the light is timmer.Tried 3 without resistor: there is almost no light

## Week 2
## Task 1 Info about Buses

1. one wire - https://docs.google.com/presentation/d/1ym6gIIebMlBZ-dbBXdGK-dlipIwwkTSTDwxm1MmrIkw/edit?usp=sharing
2. RS232 - pc-> modems, printers, computer mice, CNC. Properties: 9-25 wires, 9 pin (db9), speed: 20kbs, max len:15m, special: auto shutdown and auto wakeup, high esd protection. wattage: +-15
3. RS485 - props: 10mbit/s, max len 1200m, immunity against electrical noise. wires: 2,4. Usage: airplanes- light systems, twisted pair cable. Expensive, but the industrie Bus. Base technology is still rs232, just need adapter
4. CAN - low level bus, used in vehicles, industrial automation, medical instruments.Used for communication between electronic controls. speed: 1mbit/s, up to 5, max len 40 m, special: multi-master, priority based, error detection, 2.5 volts,devices: 32, 64 or 127, depends on speed. Reduce wiring and costs, but is still expensive.
5.  I2C and I3C - Interated circut, chipless, standardize sensor communication.  max len 3-4 m. up to 128 devices. 
6. SPI- Serial Peripheral Interface.used for short disctance communication. 4 different cables: master in/out, Sync, Slave select. You can read and write at the same time. Displays, ethernet ports, sd cards. Cheap and fast


## Task 2

Blink and LED. Got everything done fast, set up the breadboard, wrote some code and it worked. Had to search for the timming part and foun new think called PMW. The timming happened not because we lovered the voltage, but because we changed the frequenzy.

## Task 3
Reading analog values. Had some problem with this one, but after asking for help we got it fixed. The problem was we didn't use the A1 input, but only that one registeres the analog values.

## Task 4
Touch sensor actiovation. This task was done smoothly and fast. Breviousl i thought that the middle box was the sensor, but to my suprise it was actually the pins. The accurance was very good and we only got 1 input value even if we touched close to 2.

## Task 5
Mini-Bomb defusal game, this was done by my partner and me over discord communication. He had the breadboard and everything else. Unfortunately there was a cable missing, so we didn't have a chance to finish it :(




