# Non-contact-Thermometer v1.0
A low cost non-contact (infrared) Thermometer mainly based on Arduino and MLX90614 infrared temperature sensor

![Infrared Thermometer](https://github.com/xprogramer/Non-contact-Thermometer/blob/master/schema.jpg?raw=true "image description")

![Wiring schema](https://github.com/xprogramer/Non-contact-Thermometer/blob/master/schema.jpg?raw=true "image description")

# Table of contents
* [Overview] (#overview)
* [Features] (#features)
* [Hardware] (#hardware)
* [Memory] (#memory)
* [Perspectives] (#perspectives)

# Overview
This project is about a non-contact thermometer that measures the object temperatures without touching them. The project is mainly based on Arduino nano, MLX90614 infrared temperature sensor and some other hardwares (check the list below). The whole hardware is embedded within a pistol, and the latter has been printed using a 3D printer. This thermometer includes a pointing laser to figure out the direction of the pistol, and does not point necessarily to the targeted point that we want to measure its temperature.
If the device is powered with sufficient current, and all the sensors are properly initialized, the buzzer makes two beeps. Conversely, the buzzer makes three beeps continuously and the screen show an error message.
In the illustrated prototype, I have used Arduino pro mini instead of Arduino nano, because I do not have Arduino nano with Mega328 micro-controller.

# Features
The Nokia 5110 LCD has been used in this project to benefit from its size and features, where we can draw anything including figures, graphs and different shapes. Another particularity of this project is the use of distance sensor (i.e. VL53L0X) to measure the distance between the pistol and the target point. The main reason to measure the distance is to avoid the contact with objects, and to the end it is very useful in the case of infected persons/objects (e.g. Covid-19). We draw the distance from the target (cm), the ambient temperature (°C) and the object temperature (°C). 

# Hardware
- The pistol model is made using a 3D printer and designed for Arduino nano. On the right side of the pistol, there is a rectangular hole to fit the USB connector of the Arduino. It was designed to make an update of the software without opening the cover, and to log data into the computer as well.
- The device uses MLX90614 sensor to measure the object temperature and the ambient temperature. It works using I2C protocol.
- The device uses VL53L0X sensor to measure the distance from the targeted object. This sensor based on time of flight technology that makes it accurate in contrast to other technologies (e.g. ultrasonic sensor). This sensor could be replaced with its upgraded sensor VL6180X to get more accurate distance (both use I2C protocol).
- The laser diode has been used to show the direction of the pistol and the target object. It points on the targeted surface (e.g. forehead) and does not point on the targeted point.
_ The voltage regulator MP1584 is used to draw a constant voltage 3.3v used to power-up the sensors and the screen.
- The push button is used to swap from IDLE to active mode and vice-versa.
- The switch button to power on/power off the device.
- A 9v battery to power the system.

# Memory
The current program (v1.0) uses approximately 22.9k of program memory, which requires a micro-controller with 30k of memory at least. In the case of Atmega328, it uses 74% of program memory and 57% of dynamic memory. It is worth mentioning that once the dynamic memory exceeds 75%, the Arduino program becomes instable. Adafruit VL53L0X library is expensively consuming, where it takes 17.3k of program memory, whereas Adafruit MLX90614 library takes 5.3k of program memory.

# Perspectives
The major limit of the current version of this device is the power consumption, where it draws important current because of the laser and the screen lights. In addition, I did not take into consideration the 3D printing errors during the CAD design, where I have found some issues to embed all the electronics (especially the screw holes). The electronic part of the push button has not been taken into consideration in the CAD design.
The minimal working distance of VL53L0X is approximately 20mm, and we must take this limit into consideration to show the real distance between the pistol and the targeted object.
As an important drawback in the current version is the buzzer tone. As we use the delay function to make a ring, we make a small blockage for a period of time, and consequently releasing the push button will not power off the laser and nor change the screen.

As perspectives for further improvements:
- Implement a minimal library for VL53L0X sensor to reduce the program size and to run on the most of micr-ocontrollers;
- Add a light sensor to manage the screen lights;
- Make ergonomic design of the pistol;
- Measure the battery level and show it on the screen;
- Implement an independent buzzer ring system to overcome the blockage;
- Design a circuit using PIR infrared (D203S) instead of MLX90614 to reduce the total cost;
- Reduce the laser power to optimise the power consumption;
- It will be better to design a PCB to reduce the wire lengths and quantity.
