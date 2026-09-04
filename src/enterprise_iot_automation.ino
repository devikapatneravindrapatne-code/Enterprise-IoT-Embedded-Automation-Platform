#define BLYNK_TEMPLATE_ID "TMPL32ZnPitRf"
#define BLYNK_TEMPLATE_NAME "Enterprise IoT Automation"
#define BLYNK_AUTH_TOKEN "YOURS_BLYNK_AUTH_TOKEN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char ssid[] = "Wokwi-GUEST";
char pass[] = "";

#define DHT_PIN       4
#define DHT_TYPE      DHT22

#define LDR_PIN       34
#define PIR_PIN       27
#define MACHINE_PIN   35

#define RELAY_PIN     26

DHT dht(DHT_PIN, DHT_TYPE);
BlynkTimer timer;

// Light
const int LIGHT_THRESHOLD = 2000;


// Machine
const int MACHINE_HIGH_THRESHOLD = 3000;
const int MACHINE_CRITICAL_THRESHOLD = 3500;


// Temperature
const float HIGH_TEMPERATURE = 35.0;
const float CRITICAL_TEMPERATURE = 40.0;

// SENSOR VARIABLES

float temperature = 0.0;
float humidity = 0.0;

int lightLevel = 0;
int motion = 0;
int machineValue = 0;

// CONTROL VARIABLES

int relayState = 0;
int loadState = 0;
int modeSelector = 0;
int manualRelayControl = 0;
int alertLevel = 0;
int emergencyStatus = 0;

// STATUS VARIABLES

String machineStatus = "NORMAL";
String serviceStatus = "SERVICE OK";
String operationMode = "AUTO";
String alertMessage = "SYSTEM NORMAL";

// FUNCTION DECLARATION

void sendSensorData();

// BLYNK CONNECTED

BLYNK_CONNECTED()
{
  Serial.println();
  Serial.println("=================================");
  Serial.println("       BLYNK CONNECTED");
  Serial.println("=================================");

  
  Blynk.syncVirtual(V16);
  Blynk.syncVirtual(V17);

  
  Blynk.virtualWrite(V7, relayState);
  Blynk.virtualWrite(V8, loadState);
  Blynk.virtualWrite(V9, operationMode);
}

BLYNK_WRITE(V16)
{
  modeSelector = param.asInt();

  if (modeSelector == 0)
  {
    operationMode = "AUTO";
  }
  else
  {
    operationMode = "MANUAL";
  }

  Serial.println();
  Serial.println("========== MODE CHANGE ==========");

  Serial.print("V16 Value      : ");
  Serial.println(modeSelector);

  Serial.print("Operation Mode : ");
  Serial.println(operationMode);

  Serial.println("=================================");

 
  Blynk.virtualWrite(V9, operationMode);
}

BLYNK_WRITE(V17)
{
  manualRelayControl = param.asInt();

  Serial.println();
  Serial.println("======= MANUAL RELAY COMMAND =======");

  Serial.print("V17 Value       : ");
  Serial.println(manualRelayControl);

  if (modeSelector == 1)
  {
    if (manualRelayControl == 1)
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);
    }

    relayState = digitalRead(RELAY_PIN);
    loadState = relayState;

    Blynk.virtualWrite(V7, relayState);
    Blynk.virtualWrite(V8, loadState);
  }

  Serial.print("Relay State     : ");
  Serial.println(relayState);

  Serial.print("Load State      : ");
  Serial.println(loadState);

  Serial.println("====================================");
}

// SETUP

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("============================================");
  Serial.println(" ENTERPRISE IoT & EMBEDDED AUTOMATION");
  Serial.println("============================================");

  dht.begin();

  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, LOW);

  relayState = 0;
  loadState = 0;
  modeSelector = 0;
  operationMode = "AUTO";
  manualRelayControl = 0;

  Serial.println();
  Serial.println("Connecting to Blynk...");

  Blynk.begin(
    BLYNK_AUTH_TOKEN,
    ssid,
    pass
  );

  Serial.println("Blynk connection established.");

  timer.setInterval(2000L, sendSensorData);
}

// MAIN LOOP

void loop()
{
  Blynk.run();
  timer.run();
}

// SENSOR + PROCESSING + BLYNK

void sendSensorData()
{
  float newTemperature = dht.readTemperature();

  if (!isnan(newTemperature))
  {
    temperature = newTemperature;
  }

  float newHumidity = dht.readHumidity();

  if (!isnan(newHumidity))
  {
    humidity = newHumidity;
  }

  lightLevel = analogRead(LDR_PIN);
  motion = digitalRead(PIR_PIN);
  machineValue = analogRead(MACHINE_PIN);

Serial.print("DEBUG Machine Value = ");
Serial.println(machineValue);

Serial.print("DEBUG Critical Threshold = ");
Serial.println(MACHINE_CRITICAL_THRESHOLD);

if (machineValue >= 3500)
{
  machineStatus = "CRITICAL";
}
else if (machineValue >= 3000)
{
  machineStatus = "HIGH";
}
else
{
  machineStatus = "NORMAL";
}

Serial.print("DEBUG Machine Status = ");
Serial.println(machineStatus);

  // 7. SERVICE STATUS
  
  if (machineValue >= MACHINE_HIGH_THRESHOLD)
  {
    serviceStatus = "SERVICE REQUIRED";
  }
  else
  {
    serviceStatus = "SERVICE OK";
  }

  // 8. OPERATION MODE + RELAY
 
  if (modeSelector == 0)
  {
    operationMode = "AUTO";

    if (
      lightLevel < LIGHT_THRESHOLD &&
      motion == 1
    )
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);
    }
  }
  else
  {
     operationMode = "MANUAL";

    if (manualRelayControl == 1)
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);
    }
  }

  // 9. ACTUAL RELAY STATUS

  relayState = digitalRead(RELAY_PIN);

  // 10. LOAD STATUS
 
  loadState = relayState;

  // 11. RESET ALERTS
  
  alertLevel = 0;
  emergencyStatus = 0;
  alertMessage = "SYSTEM NORMAL";

  // 12. CRITICAL ALERT
 
  if (
    machineValue >= MACHINE_CRITICAL_THRESHOLD ||
    temperature >= CRITICAL_TEMPERATURE
  )
  {
    alertLevel = 2;
    emergencyStatus = 1;


    if (
      machineValue >= MACHINE_CRITICAL_THRESHOLD &&
      temperature >= CRITICAL_TEMPERATURE
    )
    {
      alertMessage = "MACHINE & TEMP CRITICAL";
    }
    else if (machineValue >= MACHINE_CRITICAL_THRESHOLD)
    {
      alertMessage = "MACHINE CRITICAL";
    }
    else
    {
      alertMessage = "TEMPERATURE CRITICAL";
    }
  }

  // 13. WARNING ALERT
 
  else if (
    machineValue >= MACHINE_HIGH_THRESHOLD ||
    temperature >= HIGH_TEMPERATURE ||
    motion == 1
  )
  {
    alertLevel = 1;
    emergencyStatus = 0;


    if (machineValue >= MACHINE_HIGH_THRESHOLD)
    {
      alertMessage = "SERVICE REQUIRED";
    }
    else if (temperature >= HIGH_TEMPERATURE)
    {
      alertMessage = "HIGH TEMPERATURE";
    }
    else if (motion == 1)
    {
      alertMessage = "MOTION DETECTED";
    }
  }

  // 14. BLYNK ENVIRONMENT DATA
 
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, lightLevel);
  Blynk.virtualWrite(V3, motion);

  // 15. BLYNK MACHINE DATA
 
  Blynk.virtualWrite(V4, machineValue);
  Blynk.virtualWrite(V5, machineStatus);
  Blynk.virtualWrite(V6, serviceStatus);

  // 16. BLYNK AUTOMATION STATUS
  
  Blynk.virtualWrite(V7, relayState);
  Blynk.virtualWrite(V8, loadState);
  Blynk.virtualWrite(V9, operationMode);

  // 17. BLYNK ALERTS
 
  Blynk.virtualWrite(V10, alertMessage);
  Blynk.virtualWrite(V11, alertLevel);
  Blynk.virtualWrite(V12, emergencyStatus);

  // 18. BLYNK CHARTS
  
  Blynk.virtualWrite(V13, temperature);
  Blynk.virtualWrite(V14, humidity);
  Blynk.virtualWrite(V15, motion);

  // 19. SERIAL MONITOR
  
  Serial.println();
  Serial.println("========== SYSTEM STATUS ==========");

  // Environment
  Serial.print("Temperature     : ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity        : ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Light           : ");
  Serial.println(lightLevel);

  Serial.print("Motion          : ");
  Serial.println(motion);


  // Machine
  Serial.print("Machine Value   : ");
  Serial.println(machineValue);

  Serial.print("Machine Status  : ");
  Serial.println(machineStatus);

  Serial.print("Service Status  : ");
  Serial.println(serviceStatus);


  // Mode
  Serial.print("Operation Mode  : ");
  Serial.println(operationMode);

  Serial.print("Mode Selector   : ");
  Serial.println(modeSelector);

  Serial.print("Manual Control  : ");
  Serial.println(manualRelayControl);


  // Relay
  Serial.print("Relay           : ");
  Serial.print(relayState);

  if (relayState == 1)
  {
    Serial.println(" (ON)");
  }
  else
  {
    Serial.println(" (OFF)");
  }


  // Load
  Serial.print("Load            : ");
  Serial.print(loadState);

  if (loadState == 1)
  {
    Serial.println(" (ON)");
  }
  else
  {
    Serial.println(" (OFF)");
  }


  // Alerts
  Serial.print("Alert Message   : ");
  Serial.println(alertMessage);

  Serial.print("Alert Level     : ");
  Serial.println(alertLevel);

  Serial.print("Emergency       : ");
  Serial.println(emergencyStatus);

  Serial.println("===================================");
}
