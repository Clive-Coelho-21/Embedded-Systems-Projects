# Distance Measurement Project

## Components Used:
1. Arduino Nano  
2. 16x2 Liquid Crystal Display (LCD) with I2C Module  
3. HC-SR04 Ultrasonic Sensor  
4. Buzzer  

## Software Used:
1. Arduino IDE

## Working

- This project uses an Arduino Nano and an ultrasonic sensor to measure the distance of nearby objects. 

- The system continuously monitors the distance, and if an object comes closer than 10 cm, the buzzer sounds to provide an audible alert.

- When the distance remains above 10 cm, the buzzer stays off. 

- Additionally, the real-time distance is displayed on a 16x2 LCD screen via the I2C module, providing clear visual feedback to the user.

![Distance Measurement](./Distance_Measurement.jpeg)