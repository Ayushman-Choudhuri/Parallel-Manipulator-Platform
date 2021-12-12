# Circle - A Robotic Parallel-Manipulator-Platform

## 1.  Project Description

Circle is an open source 6 DOF robotic parallel manipulator platform. This project was started with the aim of building a stabilization platform for critical payloads like cameras in both linear as well as rotational axes. Additional features will be added as the project matures.   

Project link on my website: https://www.ayushmanchoudhuri.com/circle

## 2. Software

### 2.1 Software Packages Used

#### 2.1.1 Software Development
1. STM32CubeIDE - V1.2.0
2. STM32CubeMX - V6.2.0
3. STM-STUDIO-STM32 - V3.6.0
4. Jupyter Notebook 6.0.1

#### 2.1.2 Hardware Development
1. Solidworks 2018
2. Ultimaker Cura 3.4.1
3. Eagle 9.6.2

### 2.2 Setup

#### 2.2.1 STM Environment

- The Circle_Software.ioc (Software > Circle_Software.ioc) file can be imported into the STM32CubeMX environment and then the pin settings of the STM32F103C8T6 microcontroller can be viewed and modified 
- The .cproject file (Software > .cproject) can be used to import the project into the STM32CUBE IDE Environment.
- Core (Software > Core) contains all the source (Src) and the header files (inc) needed. 
- Variable Viewer (Software>Variable Viewer) contains the .tsc and .tsp files needed to view variables using STM STUDIO

#### 2.2.2 Python - IK Analysis

- The inverse kinematics analysis of the robot can be found in the  "Inverse Kinematics Solver - Python" Folder. The file can be imported into a jupyter notebook and analysed

## 3. Hardware

### 3.1 Controller

The controller is a double sided PCB with the following components mounted on it:
  - DRV8825 Stepper Motor Driver Module
  - STM32F103C8T6 Microcontroller based development board (Blue Pill). The core is an ARM CORTEX M3
  - Mini 360 Step Down Buck Converter Power Module
  - USB to UART TTL 5V 3.3V FT232RL 
  - 3 way DIP switch (To set microstepping mode of the stepper motor drivers)
  - Input port for a MPU 9250 sensor which can be attatched to the end effector for pose feedback
 
 The controller is powered using a 12V 10A SMPS power module

### 3.2 Actuation

The Actuation of the robot links are done using six NEMA 17 4.4 Kgcm motors.

### 3.3 Robot Structure and Links

The robot has a 6 RSS structure. The CAD models can be found in the file - CAD MODELS

### 3.4 Manufacturing

- All the structural support items and end effectors can be 3D printed
- If a 3D printer cannot print the base plates of the robot, they can also be made out of Acrylic sheets (min 5mm) using laser cutting methods
- The S-S links can be made by joining two femals M6 spherical joint bearings using a M6 threaded rod. 

## 4. Future Work
- Closed loop implementation and stablization using MPU 9250 sensor feedback
- Replacement of SMPS with Lithium Polymer Battery
- ROS Implementation 
- Replacing the STM 32 microcontroller with a Raspberry Pi 4

## 5. Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## 6. License

MIT
