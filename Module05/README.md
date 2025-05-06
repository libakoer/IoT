## Module 5
# System building blocks
So far we've mainly used platformio to write c++ code on almost everything, and while there are libraries that use python or graphical interfaces we've found just writing the code ourselves has been the most consistent in actually making progress. 
# Pain Points
There are a lot of small real life problems like wire connectivity or 1 character errors that might not show an error but completly break the connection with the broker 
# Scaling up
Using node-red has been extremly easy and consistent for our group so far, it really makes connecting systems with mqtt a breeze and the extensions and libraries are easy enough to use that. Haven't hit any real roadblocks with it yet, but maybe that's because we haven't used it for large enough projects.
# Device management
IOTEmpower with it's OTA flashing and oneliners has been very useful the times we have got it to work, but it's definetly doable with just platformio as well.
# Integration
Neither of us have much experience with IOTKnit but it seems like a decent alternative to node-red, but both of us prefer node-red over it so far.
# Miniproject 1 
- Important commands
 - mqtt_broker - starts mqtt
 - mqtt_listen  - looks for all mqtt posts on the broker
 - deploy (serial) - deploys code in setup.cpp
 - iot menu - opens graphical menu for the system
 - adopt - flashing using a dongle
 - iot doc serve - shows the documentation locally
# Miniproject 2 First node
Updated IOTEmpower and followed 
![image](https://github.com/user-attachments/assets/30a9cf24-95da-4e55-81f1-1ed4323ad60f)
also flashed the second button controller for 2nd node miniproject through serial, couldn't get the ota flashing working without deploying through a serial first. The guides keep saying to use a dongle but I don't think we were provided one. (in hindsight this would make sense, because the documentation says "To reconfigure wifi of a previously used IoTempower node (if the node never has been flashed with IoTempower before, use deploy serial to flash it)...")
![image](https://github.com/user-attachments/assets/bb5e88c5-63fb-4577-bac6-2152be396a06)


# Miniproject 3 Second node - 2 buttons controlling 1 light
Note that we didn't have a single button to use, so the node-red code is purely theoretical and while the cpp code deploys properly i couldn't actually test it with a physical button. (Tested if the reset button of various models could be used to replace, didn't seem to work) But the code was given so i doubt the validity of it needs to be tested.
![image](https://github.com/user-attachments/assets/c11e4d70-b68b-402a-b5ae-415be93b2606)

While having all the documents, local web pages and node-red running the iot laptop seems to have run out of memory.
![image](https://github.com/user-attachments/assets/53fe37b6-0ac7-4fbc-a080-3fdf9a0e0a84)

Inside the Toggle:
Did have to change the code a bit, so that the payload would match strings for our 
![image](https://github.com/user-attachments/assets/c18b8cfc-9553-40e5-87de-e70906ccdf54)


# Access control system
Made the RFID and distance code in iotempower and finally got it working. The lock system was done also, and used everything on the old node red, without changing the topics.

# Liquid measuring project for suitability in use on a boat
- Scale - The scale we used could handle up to about 500g of weight on it, but it was accurate in weighing up to that point. Calibrated using tiny weights to make sure. Needs a stable base to give accurate readings, so a rocking boat would not suit it well.
- Ultrasonic Distance sensor - Not sure if it's inherent to the sensor we used or if our code was faulty, but when tracking the distance of objects moving fast enough, the readings would get wildly inaccurate, usually thinking the object was comically far away, despite moving about 20 cm away. As long as the object itself is close to stationary the accuracy is very good, up to half a centimeter differences can be detected. We solved this by averaging about 5 readings for any one that was shown on the dashboard. Would be fine in using in a boat, but the readings would be relatively inaccurate on their own assuming there were waves. 
- Soil moisture Capacitive - Looked in to the sensor on this subtask. The ones we were given are very low quality, missing a capacitor (it's just bridged through) and likely missing a built in resistor (can't test myself but other boards with the previous issue have this problem very commonly). It uses a m555 chip, which tends to have both of these issues. I have included an image showing off the problems in  the images tab.
Despite that, assuming you have a good quality chip, (following the reccomendations from this video https://youtu.be/IGP38bz-K48?si=9fgruOmTIOg0KAjY) this sensor is far more resistant to corrosion compared to the other moisture sensor. 
- Water Digital Capacitive - These sensors corrode extremely quickly when powered on for extended periods of time, to fix this we only powered on the sensor every 5 seconds and only for the stabilization of the reading and then the reading itself. We averaged the readings locally and then sent to the dashboard as well, due to the varying nature of the readings. The sensor itself is meant to be submerged in water, but the chip and wiring are exposed, while being only a couple cm above the expected water level. The sensor was at the very least very consistent in the water level readings. This one would detect the presence of oil, but would need the code modified and likely a second sensor to help with identifying if the capacitivity has changed due to less water or the influx of oil on the sensor. Needs the electronics coated to not short circuit constantly.
# Database
-Added Database to findings, so it would be able to summarise on the data we have collected. For that I binded the data output which we got from nodes to node red, which transfers it to the database aswell. on the screenshots it's able to see, how it does it