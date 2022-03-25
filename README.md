# UltrasonicSensorFilter

This simple code make output from Ultrasonic Sensor for Arduino more stable and not sharped.

# Features:
- more stable output data
- delete output frames with incorrect data(like sharp rise for 1 frame, data below 0)
- speedStart(); 

<br/><br/>

<b>BEFORE FILTER:</b>
![image](https://user-images.githubusercontent.com/98188315/160198172-cb6d7e94-e96f-4216-b179-79a53a4e375b.png)
Sudden spike
<br/><br/><br/>
<b>AFTER FILTER:</b>
![image](https://user-images.githubusercontent.com/98188315/160197745-858e7bea-eecb-49e3-ba15-3959cfb623f5.png)
No spikes
