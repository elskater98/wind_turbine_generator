# Wind Turbine Generator

This repository takes part of the subject Ubiquitous Computing and Embedded systems project of the University of Lleida, being that one a development of a wind turbine generation farm, as for a real client.  

## Project statement

- Desing and evaluate a multi-purpose device including IoT capabilities.
- The main target is a Wind Turbine Generator Farm (WTGF).
- The engineering department has designed a prototype.
- Our target is to evaluate the prototype and determine its weaknesses.
- The prototype is composed by multiple devices; Supervision station, Data providers and a MQTT Broker.

## Project requirements

- There is just only one Supervision Station for the whole WTGF.
- All sensors are placed far from the Supervision Station.
- Temperature and humidity sensors are placed near to the Rotor Hub.
- The Tower movement sensor is placed in the middle of the tower.
- Sensor measurements must be obtained in Real-Time.
- Sensors are controlled by the Data providers and they will show the current sensor readings.
- Whole WTGF data is transferred to the Supervision Station through a MQTT broker.
- The MQTT broker will show graphically the current number of subscribers.
- The maintenance manager requires access to the last 24h data that should be available graphically on the Supervision Station.

## Prototype Schema
![image](https://user-images.githubusercontent.com/45320338/139112555-7f0f96a8-55df-4fa4-bb71-ad44783073dd.png)

## Data Producer 1
### Material
- ESP-01 -> 3.3 V
- Protoboard 
- LCD Screen
- DHT11 -> 3.5 V
- VCC Protoboard adapter (3.3V, 5V)
- ESP Programmer module
- Wires

## Data Producer 2
### Material
- ESP-01 -> 3.3 V
- Protoboard 
- LCD Display
- Accelerometer (ADXL345) -> 3.3 V
- VCC Protoboard adapter (3.3V, 5V)
- ESP Programmer module
- Wires
- I2C – LCD Adapter

## MQTT Broker
### Material
- NodeMCU
- Breadboard
- MCP23017
- Wires
- Segment LED Bar
- I2C Bus

