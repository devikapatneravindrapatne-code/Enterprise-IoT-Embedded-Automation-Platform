# Automation Logic

## Project
Enterprise IoT & Embedded Automation Platform

## 1. Introduction

This document explains the automation logic implemented in the Enterprise IoT & Embedded Automation Platform.

The system uses multiple sensor inputs connected to the ESP32 controller and applies predefined decision rules to control the relay/load automatically. It also supports manual control through the IoT dashboard.

The automation system is designed to:

- Monitor environmental and machine-related parameters.
- Automatically control the connected load.
- Support AUTO and MANUAL operating modes.
- Detect abnormal conditions.
- Update system status on the IoT dashboard.
- Improve system reliability and reduce unnecessary manual intervention.

---

## 2. Input Parameters

The ESP32 continuously monitors the following parameters:

| Parameter | Description |
|---|---|
| Temperature | Environmental temperature measured using DHT22 |
| Humidity | Environmental humidity measured using DHT22 |
| Light Level | Ambient light intensity measured using LDR |
| Motion | Motion detection using PIR sensor |
| Machine Value | Simulated machine condition using potentiometer |
| Mode Selector | Selects AUTO or MANUAL operation |
| Manual Relay Control | Controls relay manually in MANUAL mode |

---

## 3. Operating Modes

The system supports two operating modes:

### AUTO Mode

In AUTO mode, the ESP32 controls the relay automatically based on sensor readings.

The automation rule used is:

```text
IF Light Level < LIGHT_THRESHOLD
AND Motion is Detected
THEN
    Relay = ON
ELSE
    Relay = OFF
