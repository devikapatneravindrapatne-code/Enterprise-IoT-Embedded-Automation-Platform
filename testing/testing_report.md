# Enterprise IoT & Embedded Automation Platform – Testing Report

## 1. Introduction

Testing is an important part of the Enterprise IoT & Embedded Automation Platform because it verifies whether the sensors, ESP32 controller, automation logic, IoT dashboard, relay control, and alert system operate as expected.

The system was tested using the Wokwi simulation environment and the Blynk IoT dashboard. Testing focused on sensor monitoring, automation behavior, manual control, alert generation, dashboard communication, and system response.

---

## 2. Testing Objectives

The main objectives of testing are:

- Verify correct operation of the ESP32 controller.
- Verify sensor readings and sensor-state detection.
- Verify automatic relay control.
- Verify manual relay control.
- Verify AUTO and MANUAL operating modes.
- Verify temperature and machine-value alert thresholds.
- Verify emergency-status operation.
- Verify Blynk dashboard data updates.
- Verify relay and load status.
- Identify possible system limitations and failures.
- Validate the overall system workflow.

---

## 3. Testing Environment

The project was tested using the following environment:

| Component | Testing Environment |
|-----------|---------------------|
| Microcontroller | ESP32 |
| Simulation Platform | Wokwi |
| IoT Platform | Blynk IoT |
| Temperature/Humidity Sensor | DHT22 |
| Light Sensor | LDR |
| Motion Sensor | PIR |
| Machine Parameter | Slide Potentiometer |
| Actuator | Relay |
| Simulated Load | LED / DC Motor |
| Communication | Wi-Fi |
| Monitoring | Serial Monitor + Blynk Dashboard |

---

## 4. Testing Methodology

The system was tested using a combination of:

### 4.1 Functional Testing

Functional testing verifies whether each component performs its intended function.

Examples:

- Sensor reading
- Relay switching
- Dashboard updating
- AUTO mode
- MANUAL mode
- Alert generation

### 4.2 Integration Testing

Integration testing verifies communication between different parts of the system.

The following interfaces were tested:

```text
Sensors
   ↓
ESP32
   ↓
Processing
   ↓
Automation / Alert Logic
   ↓
Relay
   ↓
Load

ESP32
   ↓
Wi-Fi
   ↓
Blynk IoT
   ↓
Dashboard
