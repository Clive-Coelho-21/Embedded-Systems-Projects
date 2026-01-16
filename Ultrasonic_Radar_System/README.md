# Distance Measurement Project

## Components Used:
1. Arduino Uno  
2. HC-SR04 Ultrasonic Sensor
3. Buzzer  
4. TowerPro SG90 Servo Motor

## Software Used:
1. Arduino IDE
2. Processing 4 IDE

## Working

- This project recreates a basic RADAR system using an Arduino Uno, a servo motor, and an ultrasonic sensor. 

- The ultrasonic sensor is mounted on the servo motor, which continuously sweeps from 0° to 180° and back from 180° to 0°. 

- The sensor measures distances at each angle, and the data sent to Processing 4 software.  

- When an object is detected at a distance less than 30 cm, the servo motor reduces 30° to 150° and back to focus more on the target and enable faster detection. 

- Additionally, a buzzer is used to provide an audible alert, with the buzzer frequency varying based on the detected distance to indicate proximity.

![RADAR System](./Ultrasonic_RADAR_System.jpeg)