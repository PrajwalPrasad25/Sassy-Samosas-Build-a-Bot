# Sassy-Samosas-Build-a-Bot
This is the repository for the Senior Problem statement of Build-A-Bot 2.0 of Parsec 5.0 in IIT Dharwad <br>
### Team Members <br>
1. Yashas Subramanya <br>
2. Farhaan Nasir <br>
3. Prajwal N Prasad <br>
4. Saipushkar Nagaraj <br>
<br>
### Components Used <br>
1. ESP32 - DoItDevKit V1 <br>
2. VL53L0X - Time Of Flight Sensor <br>
3. PCA 9685 Servo Motor Driver <br>
4. MG995 - Servo Motors <br>
5. USB - Breakout Board <br>
<br>
### Supporting Files: <br>
1. CodeFile.ino - File containing codes to drive the servo motors and capture depth data from the ToF sensor <br>
2. test.py - File to read data from serial monitor and write to a csv file <br>

### Drive Link containing the visuals of the project
https://drive.google.com/drive/folders/1j751zQ_TMDxlf-sAFE4ER19XNdLMLdK1?usp=sharing

###Drive Link containing Design Files and Motion Study
https://drive.google.com/drive/folders/1MiDCNzK-_Yx1yznZclDlqzyDPRkQbYrt?usp=sharing

The objective of the project was to prioritize time over accuracy, with the target of 3 minutes to scan the object. In accordance with this constraint, we have set a disc rotation of 22.5 degrees for every sweep of the robotic arm. 
The code can be modified and the actuators recalibrated to set the disc rotation at a lower angle(say, 2 degrees) to capture more data, and subsequently, a more acccurate scan.
