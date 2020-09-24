# High Altitude Balloon for Measuring Environmental Pollution MQP '20-21

## CURRENTLY BEING DEVELOPED

## Summary
This is the repository for the High Altitude Balloon Major Qualifying Project(MQP) at Worcester Polytechnic Institute(WPI). The overarching objective of this MQP is to collect environmental data (CO2, NO2, etc.) from the Stratosphere to guage the level of greenhouse gases. The repository is broken into three main code bases (sensor, Groundcontrol station, and payload) for different tasks. The system works by obtaining the sensor data and packaging them into data packets. From there, the data packets are transferred either by UART or Radio, depending on who's sending and receiving. The Sensor obtains and transmit data to the Payload, via the TX/RX pins. Once the data packet has been received, it streams it back down to the the GCS. The GCS confirms integrity with a checksum. **[WIP]**

The GCS and Payload codes were designed for Linux based operating systems.

## Database requirement
**SQLite** was used to record all sensor data, both on the weather balloon and on the GCS. We decided to create two different databases in case the weather balloon became lost/damaged and because the balloon cannot stream data to a cloud service.
* Run `sudo apt-get install sqlite3 libsqlite3-dev`

## HAB_GCS
### Description
This directory houses the code for the the groundcontrol station. 

### How to compile
1. Enter src directory
2. Make sure you have the SQLite libraries(Refer to **Databse requirement**)
3. Run `make` 
4. **WIP**

### Parts
* Any computer running a Linux OS

## HAB_Payload
### Description

### How to compile via SSH
[How to SSH into Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ssh/)

* Make sure you have done **Database requirement**
* Identify the Pi's IP address
  * Run `ifconfig`
  * Suggested: Set static IP
1. Boot up the Pi and the GCS on the same network
2. Run `pi@ip_address` on the GCS in a terminal
3. Enter pi password and you should connect
4. Navigate to the src directory
5. Run `make`
6. **WPI**

### Parts
* Raspberry Pi 4
* 2x GoPro Hero7

## HAB_NANO_Sensor
### Description
An Arduino Nano is used to collect data via sensors. The data is packed and sent to the *Payload*

**Upload code via PlatformIO**

### Parts
* Arduino Nano
* JBtek BMP180 (Barometric Sensor)
* MICS-2714 (NO2 Sensor)
* LM35CZ/NOPB (Temperature Sensor)
* GUVA-S12SD (UV Light Sensor)
* SainSmart MQ131 (Ozone Sensor)
* MG-811 (Gas Sensor)

## MISC
