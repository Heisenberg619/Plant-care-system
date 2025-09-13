# Automatic Temperature and Humidity Control System

## Description
This project implements a simple automatic control system for regulating temperature and soil moisture. It uses an STM32F401 Nucleo microcontroller with SHT40 temperature sensor and a capacitive soil moisture sensor. Two actuators, a 12V cooler and a 12V solenoid valve, are controlled to maintain desired environmental conditions.

The system continuously monitors the environment and logs data via UART communication to a PC for further analysis.

## Requirements
- STM32F401 Nucleo board
- SHT40 temperature sensor
- Capacitive soil moisture sensor
- 12V cooler
- 12V solenoid valve
- MOSFET modules for switching actuators
- STMCubeIDE for programming the microcontroller

## Usage
1. Connect the sensors and actuators to the STM32 board according to the schematic.
2. Open the project in STMCubeIDE and flash the code to the board.
3. Launch Realterm (or any UART terminal) to monitor sensor data.
4. The cooler and solenoid valve will automatically turn on/off based on the measured values.

## Project Structure
- `main.c` – main program loop, manages reading sensors and controlling actuators
- `adc.c` – handles analog-to-digital conversion for the soil moisture sensor
- `i2c_sht40.c` – communicates with the temperature sensor via I2C
- `timer.c` – implements delay and timer-based functionality
- `uart.c` – manages UART communication for data logging

## License
This project is for personal and educational use.
