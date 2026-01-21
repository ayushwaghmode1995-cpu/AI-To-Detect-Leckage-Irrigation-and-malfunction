Smart Water Leakage Detection & Control System (ESP32)
📌 Overview

This project implements a smart water leakage detection system using three flow sensors and an electromagnetic solenoid valve controlled by a relay.
An ESP32 continuously monitors water flow at three different pipeline positions and automatically shuts off water supply when leakage is detected.

🧠 System Concept

The system uses comparative flow analysis:

Sensor 1 (Upstream) – Main inlet flow

Sensor 2 (Middle) – Intermediate section

Sensor 3 (Downstream) – End section

If the flow rate at one sensor differs significantly from the others, the system assumes leakage at that section and closes the solenoid valve.

🔧 Hardware Requirements

ESP32 Development Board

3 × Water Flow Sensors (Hall-effect type)

1 × Relay Module (Active LOW)

1 × Solenoid Valve

External power supply for valve (if required)

Jumper wires & piping setup

📍 Pin Configuration
Component	ESP32 Pin	Description
Flow Sensor 1	GPIO 13	Upstream sensor
Flow Sensor 2	GPIO 12	Middle sensor
Flow Sensor 3	GPIO 14	Downstream sensor
Relay Module	GPIO 35	Controls solenoid valve
⚙️ How the Code Works
1️⃣ Pulse Counting (Interrupt-Based)

Each flow sensor outputs pulses proportional to water flow.

void IRAM_ATTR pulseCounter1() { pulseCount1++; }


Interrupts ensure accurate pulse counting

volatile variables prevent data inconsistency

ISR functions are stored in IRAM for ESP32 stability

2️⃣ Flow Rate Calculation

Flow rate is calculated every 1 second:

flowRate = pulseCount / 7.5;


Assumption: 7.5 pulses = 1 liter/minute
(Adjust according to your flow sensor’s datasheet)

Pulse counters are reset after each measurement cycle.

3️⃣ Leakage Detection Logic

A threshold-based comparison is used:

const float leakageThreshold = 0.5; // L/min


Leakage is detected if:

One sensor differs from the other two sensors by more than the threshold

Examples:

Leak near upstream → Sensor 1 differs

Leak in middle → Sensor 2 differs

Leak downstream → Sensor 3 differs

4️⃣ Relay & Solenoid Control

The relay is active LOW:

Condition	Relay State	Valve
Normal flow	HIGH	Open
Leakage detected	LOW	Closed
digitalWrite(RELAY_PIN, LOW);  // Stop water flow

🚨 System Behavior Summary
Scenario	Action
Normal flow	Water supply ON
Leakage detected	Water supply OFF
Leakage cleared	Water supply resumes
📊 Serial Monitor Output

Example output:

Flow Rate 1: 4.2 L/min
Flow Rate 2: 4.1 L/min
Flow Rate 3: 2.9 L/min
Leakage Detected: Downstream (Sensor 3)
Water flow stopped due to leakage!
--------------------

⚠️ Assumptions & Limitations

Sensors are properly calibrated

Pipeline pressure is stable

Pulses are evenly distributed

Very small leaks may require threshold tuning

No filtering for turbulence (can be improved)

🔮 Possible Improvements

Moving average filtering

Data logging (SD card / cloud)

GSM or WiFi alerts

OLED display

Auto-retry valve reopening

Machine learning–based detection

🧪 Tested On

ESP32 Dev Module

Generic Hall-effect water flow sensors

5V relay module (active LOW)

📝 Author Notes

This system is suitable for:

Smart homes

Industrial pipelines

Water conservation systems

Automated safety shutoff applications
