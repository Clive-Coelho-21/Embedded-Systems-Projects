# Centralized AC System Using Split ACs

## Components Used:
1. Raspberry Pi 5  
2. ESP-32  
3. Raspberry Pi Pico 2 W 
4. 2x DHT22   
5. 2x IR LED
6. 2x 2N2222A Transistor
7. 2x 470ohm Resistor

## Software Used:
1. Raspberry Pi OS 
2. PlatformIO VS Code Extension -> Arduino
3. Node-Red

## Problem Statement
Most buildings use standalone air conditioners per room, leading to inefficient usage, some ACs run unnecessarily while others are overcooled. Centralized HVAC systems can solve this but are expensive and impractical for spaces with existing AC units. A low-cost solution is needed to centrally and individually control existing ACs without replacing them.

## Project Purpose

This project builds a smart, low-cost AC control system that supports both centralized and per-room control using existing air conditioners.

- A Raspberry Pi provides a web-based control dashboard.

- Wi-Fi microcontrollers near each AC control power via relays and settings via IR.

- Centralized mode applies common settings to all ACs.

- Decentralized mode allows individual room control.

The system improves energy efficiency, reduces operational costs, and upgrades existing AC setups without requiring a full HVAC replacement.

## Working


Make use of the Image in Downloads on 6 Dec 2025