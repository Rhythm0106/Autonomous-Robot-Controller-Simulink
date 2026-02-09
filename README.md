Autonomous Mobile Robot (AMR) Controller 🤖

📌 Project Overview

This project involves the design, simulation, and verification of a safety-critical control system for a differential drive Autonomous Mobile Robot (AMR).

Using Model-Based Design (MBD) principles, the controller processes LIDAR-based distance sensors to perform real-time obstacle avoidance, navigation logic, and emergency safety interventions. The system was verified using automated test harnesses and compiled into Embedded C code for real-time deployment.

🚀 Key Features

Stateflow Logic: Robust Finite State Machine (FSM) handling navigation states (MoveForward, TurnLeft, TurnRight, Stop) and high-priority interrupts (EmergencyStop, LowBattery).

Kinematic Simulation: Closed-loop simulation with a differential drive plant model ($x, y, \theta$).

Automated Verification: Test Suite created using Simulink Test Manager achieving 100% functional coverage.

Requirements Traceability: Full bidirectional linking between design blocks and requirements (R1–R15) using Simulink Requirements.

Code Generation: Production-ready C code (.c/.h) generated via Embedded Coder for the GRT target.

🛠️ System Architecture

1. Control Logic (The "Brain")

The decision-making core is built in Stateflow. It processes sensor inputs against safety thresholds (0.5m) to determine the robot's behavior.

Inputs: Front_Dist, Left_Dist, Right_Dist, E_Stop, Bat_Volt

Outputs: v_cmd (Linear Velocity), w_cmd (Angular Velocity)

[Insert your screenshot of the Stateflow Chart here]

2. Safety Mechanisms

Obstacle Avoidance: Automatically transitions to turning states if path is blocked.

Trap Detection: Stops completely if all directions are blocked.

Emergency Override: Hard-coded priority transition to Stop state ($v=0$) if E-Stop is triggered or Battery < 10V.

✅ Verification & Testing

The system underwent rigorous verification using Simulink Test.

Test Case

Scenario

Outcome

TC_01

Front Obstacle Detection

✅ PASSED

TC_02

Left Avoidance Logic

✅ PASSED

TC_03

Trap Condition (All Blocked)

✅ PASSED

TC_04

Emergency Stop & Battery Fault

✅ PASSED

Test Results:

[Insert your screenshot of the 4 Green Checkmarks from Test Manager here]

📂 Repository Structure

├── src/
│   ├── Robot_Controller.c       # Generated Source Code
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


💻 How to Run

Clone the repository.

Open MATLAB (R2022b or later recommended).

Open model/Robot_Controller.slx.

Run the simulation to visualize the kinematic path.

To run automated tests, open tests/Robot_Tests.mldatx in Simulink Test Manager and click Run.

🔮 Future Improvements

Implement a PID Controller for smoother velocity transitions (Rate Limiting).

Add sensor noise models to simulate real-world LIDAR inaccuracy.

Migrate the generated code to an STM32 or Arduino hardware target.

Author: Rhythm Shah
