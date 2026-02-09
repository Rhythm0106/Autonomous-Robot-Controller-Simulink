# Autonomous Mobile Robot (AMR) Controller 

![MATLAB](https://img.shields.io/badge/MATLAB-R2022b%2B-orange)
![Simulink](https://img.shields.io/badge/Simulink-MBD-blue)
![Embedded C](https://img.shields.io/badge/Code_Generation-Embedded_C-green)
![Status](https://img.shields.io/badge/Testing-100%25_Coverage-brightgreen)

## Project Overview
This project involves the complete **Model-Based Design (MBD)** lifecycle of a safety-critical control system for an autonomous mobile robot. 

The controller processes LIDAR-based distance sensor inputs to perform real-time obstacle avoidance, navigation logic, and emergency safety interventions. The system was designed in **Simulink/Stateflow**, verified using **Simulink Test Manager** (achieving 100% functional coverage), and deployed as optimized **Embedded C code** for real-time targets.



## 🚀 Key Features
* **Robust State Machine:** Stateflow logic handling navigation states (`MoveForward`, `TurnLeft`, `TurnRight`, `Stop`) and high-priority interrupts (`EmergencyStop`, `LowBattery`).
* **Kinematic Simulation:** Closed-loop verification with a differential drive plant model ($x, y, \theta$).
* **Automated Verification:** Test Suite created using Simulink Test Manager covering 4 distinct scenarios.
* **Requirements Traceability:** Full bidirectional linking between design blocks and functional requirements (R1–R15) using Simulink Requirements.
* **Code Generation:** Production-ready C code generated via Embedded Coder for the Generic Real-Time (GRT) target.


## 🛠️ System Architecture

### 1. Control Logic (The "Brain")
The decision-making core is built using a **Finite State Machine (FSM)** in Stateflow. It prioritizes safety signals over navigation commands.

* **Inputs:** `Front_Dist`, `Left_Dist`, `Right_Dist` (LIDAR), `E_Stop`, `Bat_Volt`
* **Outputs:** `v_cmd` (Linear Velocity), `w_cmd` (Angular Velocity)



### 2. Safety Mechanisms
* **Obstacle Avoidance:** Automatically transitions to turning states if the path is blocked ($< 0.5m$).
* **Trap Detection:** Detects "Dead End" scenarios and halts motion.
* **Emergency Override:** Hard-coded priority transition to `Stop` state ($v=0$) if E-Stop is triggered or Battery drops below $10V$.


## Verification & Testing
The system underwent rigorous verification using **Simulink Test Manager**. Automated test callbacks were used to inject sensor faults and verify system response.

| Test Case | Scenario | Outcome |
| :--- | :--- | :--- |
| **TC_01** | Front Obstacle Detection | ✅ PASSED |
| **TC_02** | Left Avoidance Logic | ✅ PASSED |
| **TC_03** | Trap Condition (All Blocked) | ✅ PASSED |
| **TC_04** | Emergency Stop & Battery Fault | ✅ PASSED |



## 📂 Repository Structure
```text
├── src/
│   ├── Robot_Controller.c       # Generated Source Code (Embedded C)
│   ├── Robot_Controller.h       # Generated Header File
├── model/
│   ├── Robot_Controller.slx     # Main Simulink Model
│   ├── Robot_Reqs.slreqx        # Requirements Link File
├── tests/
│   ├── Robot_Tests.mldatx       # Automated Test Suite
├── docs/
│   ├── Traceability_Matrix.pdf  # Proof of Requirements Linking
│   ├── Coverage_Report.pdf      # Test Verification Report
└── README.md
