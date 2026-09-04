# Alert System

## Project
Enterprise IoT & Embedded Automation Platform

## 1. Introduction

The alert system is responsible for monitoring abnormal sensor and machine conditions and assigning an appropriate alert level.

The ESP32 continuously monitors:

- Temperature
- Machine condition
- Motion status

Based on configured thresholds, the system classifies the operating condition as:

- Normal
- Warning
- Critical

The alert information is also transmitted to the IoT dashboard.

---

## 2. Alert Parameters

The following parameters are used for alert generation:

| Parameter | Purpose |
|---|---|
| Temperature | Detect high or critical temperature |
| Machine Value | Monitor machine operating condition |
| Motion | Used as a warning condition |
| Alert Level | Indicates severity of the detected condition |
| Emergency Status | Indicates whether a critical emergency exists |
| Alert Message | Displays current system condition |

---

## 3. Configured Thresholds

The alert system uses the following thresholds:

```text
HIGH_TEMPERATURE = 35°C
CRITICAL_TEMPERATURE = 40°C

MACHINE_HIGH_THRESHOLD = 3000
MACHINE_CRITICAL_THRESHOLD = 3500
