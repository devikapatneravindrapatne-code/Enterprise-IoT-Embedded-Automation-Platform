# Enterprise IoT & Embedded Automation Platform – Dashboard Details

## 1. Dashboard Overview

The IoT dashboard provides a centralized interface for monitoring environmental parameters, machine conditions, automation states, alerts, and system operation. The dashboard is connected to the ESP32 through the Blynk IoT platform.

The dashboard allows the user to:

- Monitor temperature and humidity.
- Monitor ambient light and motion.
- Monitor machine value and machine status.
- View relay and load states.
- Select AUTO or MANUAL operation.
- Control the relay manually when MANUAL mode is selected.
- Monitor alert messages and alert levels.
- Monitor emergency status.
- Observe historical sensor trends using charts.

---

## 2. Dashboard Title

### ENTERPRISE IoT & EMBEDDED AUTOMATION

The dashboard is organized into functional sections so that environmental monitoring, industrial monitoring, automation control, and alert information can be viewed separately.

---

## 3. Dashboard Sections

The dashboard is divided into the following sections:

### 3.1 Environmental Monitoring

This section displays:

- Temperature
- Humidity
- Ambient Light
- Motion / Sensor Status

The section allows the operator to observe the current environmental conditions.

### 3.2 Industrial Monitoring

This section displays:

- Machine Value
- Machine Status
- Service Status

Machine Value represents the simulated machine parameter generated using the slide potentiometer.

### 3.3 Automation & Control

This section displays and controls:

- Relay State
- Load State
- Operation Mode
- Manual Relay Control

The system supports both AUTO and MANUAL operating modes.

### 3.4 Alerts

This section displays:

- Alert Message
- Alert Level
- Emergency Status

The alert section helps the operator identify normal, warning, and critical operating conditions.

### 3.5 Analytics

Charts are provided for selected parameters to observe their behavior over time.

The dashboard can include:

- Temperature Chart
- Humidity Chart
- Motion Chart

---

# 4. Datastream Configuration

The dashboard uses the following virtual datastream mapping:

| Virtual Pin | Datastream | Purpose |
|-------------|------------|---------|
| V0 | Temperature | Displays temperature |
| V1 | Humidity | Displays humidity |
| V2 | Ambient Light | Displays LDR value |
| V3 | Sensor Status / Motion | Displays motion state |
| V4 | Distance / Machine Value | Displays simulated machine value |
| V5 | Machine Status | Displays machine condition |
| V6 | Service Status / Connection Status | Displays service/connection condition |
| V7 | Relay Status / Switch | Displays relay state |
| V8 | LED / Load Status | Displays load state |
| V9 | Mode Selector / AUTO-MANUAL Display | Displays operating mode |
| V10 | Alert Message | Displays current alert message |
| V11 | Alert Level | Displays alert severity |
| V12 | Emergency Status | Displays emergency condition |
| V13 | Temp Chart | Temperature history |
| V14 | Humidity Chart | Humidity history |
| V15 | Motion Chart | Motion history |
| V16 | Operation Mode Selector | Selects AUTO or MANUAL |
| V17 | Manual Relay Control | Controls relay in MANUAL mode |

> **Note:** The exact displayed datastream names may depend on the Blynk template configuration. The virtual-pin mapping above corresponds to the implemented project logic.

---

# 5. Environmental Monitoring Widgets

## 5.1 Temperature

The temperature widget displays the temperature measured by the DHT22 sensor.

Temperature is also used by the alert system:

- Below 35°C → Normal
- 35°C to below 40°C → Warning
- 40°C or above → Critical

---

## 5.2 Humidity

The humidity widget displays the relative humidity measured by the DHT22 sensor.

Humidity is primarily used for environmental monitoring and dashboard visualization in the current implementation.

---

## 5.3 Ambient Light

The ambient-light widget displays the analog value obtained from the LDR.

The system uses:

`LIGHT_THRESHOLD = 2000`

In AUTO mode, the light condition is combined with motion detection for automatic relay control.

---

## 5.4 Motion

The motion widget displays the state of the PIR sensor.

Typical states are:

- `0` → No Motion
- `1` → Motion Detected

Motion detection is used by the automatic lighting logic and can also contribute to a warning alert.

---

# 6. Industrial Monitoring Widgets

## 6.1 Machine Value

Machine Value represents the simulated machine parameter generated using the slide potentiometer.

Thresholds:

- `≤ 3000` → Normal range
- `> 3000` → Warning
- `> 3500` → Critical

This value is useful for demonstrating machine-condition monitoring.

---

## 6.2 Machine Status

Machine Status provides a simplified indication of the current machine condition.

Example:

`NORMAL`

When the machine value exceeds the defined thresholds, the corresponding alert condition is generated.

---

## 6.3 Service Status

Service Status provides an operational indication of the system.

Example:

`SERVICE OK`

This field can be extended in future versions to indicate maintenance requirements based on repeated abnormal machine conditions.

---

# 7. Automation & Control Widgets

## 7.1 Operation Mode

The system supports two operating modes:

### AUTO

The ESP32 automatically controls the relay based on sensor conditions.

### MANUAL

The operator controls the relay through the dashboard.

---

## 7.2 AUTO Mode Logic

The implemented automatic control rule is:

```text
IF Light Level < 2000
AND Motion Detected
THEN Relay ON
ELSE Relay OFF
