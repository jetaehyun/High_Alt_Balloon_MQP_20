# High Altitude Balloon for Measuring Environmental Pollution MQP '20-21

## CURRENTLY BEING DEVELOPED

## About this project
This is the repository for the High Altitude Balloon Major Qualifying Project(MQP) at Worcester Polytechnic Institute(WPI). The overarching objective of this MQP is to collect environmental data (CO2, NO2, etc.) from the Stratosphere to guage the level of greenhouse gases. The repository is broken into three main code bases (Sensor, Ground Control Station, and Payload) for different tasks. The system works by obtaining the sensor data and packaging them into data packets. From there, the data packets are transferred either by UART or Radio, depending on who's sending and receiving. The Sensor obtains and transmit data to the Payload, via the TX/RX pins. Once the data packet has been received, it streams it back down to the the GCS. The GCS confirms integrity with a checksum. **[WIP]**

# Table of Contents
- [About this project](#about-this-project)
- [Communication](#communication)
- [Libraries](#libraries)
- [Ground Control Station](#hab_gcs)
- [Payload (Weather Balloon)](#hab_payload)
  * [How to compile via SSH](#how-to-compile-via-ssh)
- [Sensors](#hab_nano_sensor)
- [Project Components](#project-components)

## Communication
Communication between the weather balloon and ground control station was established with a wifi bridge via a Ubiquiti Antenna and Dish. Our estimated altitude will be around 90,000 ft. The two devices have an estimated range of around 130,000 ft when configured to 10 MHz.

 * [Equipment Configuration](https://www.instructables.com/How-to-Stream-Video-Pictures-and-Data-From-90000ft/)
 * [Ubiquiti LiteBeam Wireless Bridge](https://www.amazon.com/Ubiquiti-LBE-5AC-GEN2-US-LiteBeam-Wireless-Bridge/dp/B06Y2JH7PV/ref=sr_1_6?dchild=1&keywords=ubiquiti+ac+lite+5ghz&qid=1603571919&sr=8-6)
 * [Ubiquiti LiteBeam Sector](https://www.amazon.com/Ubiquiti-LiteBeam-802-11ac-Built-LBE-5AC-16-120-US/dp/B019M0KK44/ref=sr_1_11?dchild=1&keywords=ubiquiti+ac+lite+5ghz&qid=1603571919&sr=8-11)

## Libraries
### SQLite
**SQLite** was used to record all sensor data, both on the weather balloon and on the GCS. We decided to create two different databases in case the weather balloon became lost/damaged and because the balloon cannot stream data to a cloud service.
* Run `sudo apt-get install sqlite3 libsqlite3-dev`

## HAB_GCS
### Description
To receive the data that is being broadcasted to the ground, a Ground Control Station is necessary to capture the incoming sensor data. The GCS can be any computer that runs a Linux based OS. 

### How to compile
1. Enter src directory
2. Make sure you have the SQLite dev library
3. Run `make` 
4. **WIP**

## HAB_Payload
### Description
The Payload is designed to read the incoming sensor data from the NANO and send it back down to the ground. A Raspberry Pi 4 was used for key reasons: OS, lightweight, and SSH ability.

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
6. **WIP**

## HAB_NANO_Sensor
### Description
To collect sensor data, while keeping in mind of the physical dimensions of the balloon, an Arduino Nano was selected. The NANO is tasked with reading the sensor data and packing them for transmission to the ***HAB_Payload***.

### How to compile
Simply open the appropriate directly via **PlatformIO**. The configuration should automatically be recognized, allowing you to edit and upload new alterations.


## Project Components
### Ground Control Station
* Any Linux machine
### Payload (Weather Balloon)
* Raspberry Pi 4
* 1x GoPro Hero7
* Webcam (**WIP**)
### Sensor
* Arduino Nano
* JBtek BMP180 (Barometric Sensor)
* MICS-2714 (NO2 Sensor)
* LM35CZ/NOPB (Temperature Sensor)
* GUVA-S12SD (UV Light Sensor)
* SainSmart MQ131 (Ozone Sensor)
* MG-811 (Gas Sensor)
