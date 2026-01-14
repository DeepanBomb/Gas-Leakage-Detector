## GAS LEAKAGE DETECTOR USING ARDUINO & LORA

• Wireless gas leakage detection system
• Uses Arduino and LoRa communication
• Long-range alert system
• No Wi-Fi or GSM required


## OVERVIEW

• Project consists of two separate units
• Transmitter node detects gas leakage
• Receiver node triggers alert remotely
• Designed for safety monitoring applications


## FEATURES

• Long-range wireless communication using LoRa
• Real-time gas leakage detection
• Low power consumption
• Simple and cost-effective design
• Suitable for remote monitoring


## COMPONENTS USED

• Arduino Uno / Nano (2 units)
• LoRa Module (SX1278 / RA-02) (2 units)
• MQ Gas Sensor (MQ-2 / MQ-5 / MQ-135)
• Buzzer
• LED
• Resistors
• Breadboard
• Jumper wires
• USB or battery power supply


## REPOSITORY STRUCTURE

• Gas-Leakage-Detector
• TransmitterCode.ino  – Arduino code for gas detection and LoRa transmission
• ReceiverCode.ino     – Arduino code for receiving alert and activating alarm
• README.md            – Project documentation


## WORKING PRINCIPLE

• Gas sensor continuously monitors gas concentration
• Sensor outputs analog voltage
• Arduino reads sensor value through ADC
• Threshold comparison is performed
• If gas level exceeds threshold
• Alert data is transmitted via LoRa
• Receiver receives alert message
• Buzzer and LED are activated at receiver end


## CIRCUIT CONNECTIONS – TRANSMITTER NODE

• MQ Gas Sensor AO connected to Arduino analog pin
• LoRa TX connected to Arduino RX
• LoRa RX connected to Arduino TX
• Buzzer connected to Arduino digital pin
• LED connected to Arduino digital pin


## CIRCUIT CONNECTIONS – RECEIVER NODE

• LoRa TX connected to Arduino RX
• LoRa RX connected to Arduino TX
• Buzzer connected to Arduino digital pin
• LED connected to Arduino digital pin
