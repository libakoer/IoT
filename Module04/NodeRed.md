# Projects submissions.
Temperature sensor that sends data over MQTT

I then used Node-Red and changed the code around a bit to talk to eachother through the MQTT broker instead.(See [Temperature module for AC](ACTempModule.cpp) and [The code I used before to test functionality](TempModuleLocal.cpp) to see changes in temperature sensor.)
The modified and original versions of the Lock (AC) code are [Lock module for AC](ACLockModule.cpp) and [The code to hopefully not blow up the chips](LockModuleLocal.cpp)
-
![image](https://github.com/user-attachments/assets/e58b3187-4930-4696-af3a-b884ca318247)
After i tested if that worked, i moved on to plotting it all on to a chart.
-
![image](https://github.com/user-attachments/assets/55a20369-d866-4e1b-8490-8aa23863a978)
The dashboard now looks like this.
-
It also reports the temperatures and  when the lock (represents ac unit) is turned on or off
![image](https://github.com/user-attachments/assets/0e861fcc-dbf6-4a7f-8ab7-e7cba01940ab)
