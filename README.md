AI-Based Smart Irrigation Leakage & Malfunction Detection System
📌 Project Overview
This project implements an intelligent irrigation monitoring system that detects water leakage and flow malfunction in an irrigation pipeline using multiple flow sensors and an automatic control valve (relay-controlled solenoid).
The system continuously compares real-time water flow at three different pipeline locations:
Upstream
Middle
Downstream
By analyzing the difference in flow rates, the system intelligently detects leakage or abnormal flow and automatically stops water supply to prevent water wastage.
🎯 Objectives
Detect leakage in irrigation pipelines
Identify faulty or abnormal flow conditions
Automatically stop water flow when leakage is detected
Reduce water wastage and improve irrigation efficiency
Enable real-time monitoring via Serial Monitor
🧠 Why This Is an AI-Based System?
Although this project does not use Machine Learning, it qualifies as AI-based (Rule-Based Intelligence) because:
It analyzes sensor data in real time
Applies logical decision-making rules
Detects anomalies based on threshold comparisons
Takes autonomous actions without human intervention
This falls under Artificial Intelligence – Expert / Rule-Based Systems.
🛠️ Hardware Components
ESP32 / Arduino-compatible microcontroller
3 × Water Flow Sensors (Hall Effect type)
Relay Module (Active LOW)
Solenoid Valve
Power Supply
Pipes & connectors
💻 Software & Technologies
Arduino IDE
Embedded C/C++
Interrupt-based sensor reading
Serial communication
Threshold-based decision logic
🔌 Pin Configuration
Component
Pin
Flow Sensor 1 (Upstream)
GPIO 13
Flow Sensor 2 (Middle)
GPIO 12
Flow Sensor 3 (Downstream)
GPIO 14
Relay Module
GPIO 35
⚙️ Working Principle
1️⃣ Flow Measurement
Each flow sensor generates pulses proportional to water flow.
Interrupts count pulses accurately in real time.
Flow rate is calculated every 1 second using:
Copy code

Flow Rate (L/min) = Pulse Count / 7.5
2️⃣ Intelligent Leakage Detection
The system compares flow rates between all three sensors.
If the difference exceeds a predefined threshold, leakage is detected.
The system identifies the exact location of leakage:
Upstream
Middle
Downstream
3️⃣ Automatic Water Control
If leakage is detected:
Relay is activated
Solenoid valve closes
Water flow is stopped immediately
If no leakage:
Water flow continues normally
🧮 Leakage Detection Logic
Copy code
Text
If |Flow1 - Flow2| > Threshold AND |Flow1 - Flow3| > Threshold → Upstream Leakage
If |Flow2 - Flow1| > Threshold AND |Flow2 - Flow3| > Threshold → Middle Leakage
If |Flow3 - Flow1| > Threshold AND |Flow3 - Flow2| > Threshold → Downstream Leakage
Threshold used:
Copy code

0.5 L/min
📟 Serial Monitor Output
Displays real-time flow rate of each sensor
Shows leakage detection messages
Indicates relay and water flow status
Example:
Copy code

Flow Rate 1: 2.3 L/min
Flow Rate 2: 1.1 L/min
Flow Rate 3: 1.0 L/min
Leakage Detected: Upstream
Water flow stopped due to leakage!
🚨 Features
✔ Real-time monitoring
✔ Automatic leakage detection
✔ Precise leakage location identification
✔ Automatic water cutoff
✔ Low-cost & scalable solution
✔ Suitable for farms & smart irrigation systems
🔮 Future Enhancements
Integrate Machine Learning for adaptive thresholds
Cloud-based monitoring using IoT (MQTT / Firebase)
Mobile app alerts
Data logging & analytics
Solar-powered deployment
🎓 Academic Relevance
Final Year Engineering Project
Domains:
Artificial Intelligence (Rule-Based Systems)
Embedded Systems
Smart Agriculture
IoT & Automation
