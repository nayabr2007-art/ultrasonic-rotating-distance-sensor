#Rotating Ultrasonic Radar Detector

##📌  Overview 
This project uses an ESP32 to control an HC-SR04 ultrasonic sensor mounted on a micro-servo. It scans a 14cm radius and provides real-time distance and angle feedback via an SSD1306 OLED display and a piezo buzzer alarm. 

##🚀 Features
1. 64 x 128 SSD1306 OLED displays real time distance of closest object, angle of the servo
2. LED, SSD1306 OLED, and active buzzer gives a warning if closest object is within 14cm
3. Servo moves in a 0-180 degrees rotation to detect its surroundings


##🛠️ Hardware Used
1. ESP32 (NodeMCU) 
2. HC-SR04 Ultrasonic Sensor
3. SG90 Micro Servo 
4. SSD1306 OLED Display (I2C) 
5. Active Buzzer 
6. LED 

## 📐 Link to Wokwi
https://wokwi.com/projects/463644443630694401 

## 🔧 Challenges 
1. Torque Stabilization:** Addressed mechanical jitter by securing the servo base to minimize Newton's third law reactions during rotation. 
2. Signal Noise:** Optimized sensor "ping" timing to reduce false positives during motor movement. 

## 📝 Small Note 
In the Wokwi simulation the radar does not move with the servo, but in the physical setup make sure they are connected!

