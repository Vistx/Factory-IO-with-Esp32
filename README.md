

# FactoryIO with ESP32 

![Untitled](https://github.com/user-attachments/assets/da7fff78-f270-4078-a151-05525448e1ac)



## Description 


This repository contains code to establish communication between an ESP32 and Factory IO, specifically for controlling the "Pick and Place XYZ" scene using real-life buttons and a joystick.

## Files and usage

- **Factory IO with Esp32/Factory io Server** - Esp32 Code.
-  **Pick & Place XYZ ESp32**.factoryio - Modified scene.

### Software and Libraries

- FactoryIO
- VS Code with  PlatformIO 
- [This](https://github.com/emelianov/modbus-esp8266) Modbus TCP/IP library for Esp32


### Schematics

![Espconnections](https://github.com/user-attachments/assets/35309a41-43f6-40ca-bb7e-44e5c8a13491)

-   **Pin 21, 22** → Button inputs (FactoryIO Z+ and Z-)
-   **Pin 23** → Joystick switch (FactoryIO Vacuum Actuator)
-   **Pin 32** → Joystick X pin (FactoryIO X+ and X-)
-   **Pin 33** → Joystick Y pin (FactoryIO Y+ and Y-)


### Usage 

Upload the given code to the ESP32, then go to the Serial Monitor and grab the output IP address.

Next, navigate to **File > Drivers > Configuration** in Factory IO and paste the IP address into the **Host** section. After that, connect and start the scene.

![Untitled1](https://github.com/user-attachments/assets/b1b65c92-7c40-4ff8-9173-fd29a16da723)


## Results
Video
