# High Altitude Balloon for Measuring Environmental Pollution MQP '20-21

## About this project
<img src="https://www.wpi.edu/sites/default/files/inline-image/Offices/Marketing-Communications/WPI_Inst_Prim_FulClr.png" alt="wpi logo" height="400" width="500"/>

This is the repository for the High Altitude Balloon Major Qualifying Project(MQP) at Worcester Polytechnic Institute(WPI). The objective of this MQP was to collect Greenhouse Gas(GHG) (e.g. CO2, NO2, O3) emissions and other data (e.g. temperature, UV, pressure, altitude) from the Stratosphere. The repository is broken into three main code bases (Sensor, Ground Control Station(GCS), and Payload) for different tasks. The system works by obtaining the sensor data and packaging them into data packets. From there, the data packets are transferred by USB and/or radio. The Sensor obtains and transmits data to the Payload, via USB. Once the data packet has been received, it streams it back down to the the GCS via WiFi bridge. The data packet's integrity is confirmed with a checksum. 

# Table of Contents
- [About this project](#about-this-project)
- [Devices and Software](#devices-software)
- [Libraries](#libraries)
- [Ground Control Station](#hab_gcs)
- [Payload (Weather Balloon)](#hab_payload)
  * [How to compile via SSH](#how-to-compile-via-ssh)
- [Sensors](#hab_nano_sensor)
- [Data streaming](#data-streaming)
- [Project Components](#project-components)

## Devices-Software

### Devices
Communication between the payload and GCS was established with a wifi bridge via a Ubiquiti Antenna and Dish. Our estimated altitude during launch was around 70,000+ ft. However, the two devices have an estimated range of around 130,000 ft when configured to 10 MHz.

 * [Equipment Configuration](https://www.instructables.com/How-to-Stream-Video-Pictures-and-Data-From-90000ft/)
 * [Ubiquiti LiteBeam Wireless Bridge](https://www.amazon.com/Ubiquiti-LBE-5AC-GEN2-US-LiteBeam-Wireless-Bridge/dp/B06Y2JH7PV/ref=sr_1_6?dchild=1&keywords=ubiquiti+ac+lite+5ghz&qid=1603571919&sr=8-6)
 * [Ubiquiti LiteBeam Sector](https://www.amazon.com/Ubiquiti-LiteBeam-802-11ac-Built-LBE-5AC-16-120-US/dp/B019M0KK44/ref=sr_1_11?dchild=1&keywords=ubiquiti+ac+lite+5ghz&qid=1603571919&sr=8-11)
 
### Software
Software for development purposes

 * [Visual Studio Code](https://code.visualstudio.com/)
 * [PlatformIO](https://platformio.org/) - VSCode extension
   * Requirements:
     * [Arduino extension on VSCode](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)
     * [Arduino IDE](https://www.arduino.cc/en/software)

## Libraries

**SQLite** was used to record all the sensor data, on the payload and GCS. We decided to create two different databases in case we lost/damaged the payload and because the payload itself cannot stream data to a cloud service.
* Run `sudo apt-get install sqlite3 libsqlite3-dev`
* [Export](https://www.sqlitetutorial.net/sqlite-tutorial/sqlite-export-csv/) to CSV

**screen** to run the payload program on a different process after connecting via SSH
* Run `sudo apt-get install screen`

## HAB_GCS
### Description

To receive the data that is being sent to the ground, a GCS is necessary to capture the incoming sensor data. The GCS can be any computer that runs a Linux based OS. 

When viewing the data, you will most likely run into a database filled with a large number of data points. Using SQL commands will provide easy viewing. For example, you can view the sensor data at, say, 16,000 ft or higher. Our tests generally provided about 2 hours worth of data, which was quite massive, so this will helpful.

### How to run program
1. Enter src directory
2. Make sure you have the required libraries installed
3. Run `make` 
4. Run `./gcs`

## HAB_Payload
### Description

The Payload is designed to read the incoming sensor data from the UNO and send it back down to the ground. A Raspberry Pi 4 was used for 4 key reasons: OS, lightweight, cost and SSH.

### How to compile via SSH
[How to SSH into Raspberry Pi](https://www.raspberrypi.org/documentation/remote-access/ssh/)

**SETUP**
* Make sure you have done **Libraries**
* Identify the Pi's IP address
  * Run `hostname -I`
  * [Suggested: Set static IP](https://www.raspberrypi.org/documentation/configuration/tcpip/)
* Identify serial port - this is needed to read the the data being sent by the NANO
  * Run `dmesg | grep tty` to find open ports
  
  
1. Assuming you correctly configured the WiFI bridge, power on the payload and GCS.
2. Run `[username]@[pi_hostname].local` on the GCS in a terminal
3. Enter password of username
4. Navigate to the src directory
5. Run `make` to build the program
6. Run `./gcs`

## HAB_UNO_Sensor
### Description

To collect sensor data, while keeping in mind of the physical dimensions of the payload, an Arduino UNO was selected. The UNO is tasked with reading the sensor data and packing them for transmission to the ***HAB_Payload***. 

Note. make sure that there are no `Serial.println()` or any other functions that write to the data line except for the ones that write the sensor data. If you do not do this, you will have garbage data on the receiving end.

### How to upload program
Open visual studio code and import the directory via **PlatformIO**. The .ini file should automatically be recognized and it should allow you to upload new code.

## Data Streaming

To further add onto the real-time data streaming capabilities of this project, the ThingSpeak API is utilized. Upon receiving data from the Payload, the GCS will send a POST request to their server. This will allow you to view the data in a more sensible manner. Also, this service provides various features that could prove useful to you: live streaming on youtube, import CSV, public access.

To use the ThingSpeak functionality, you will have to create an account on ThingSpeak and create a channel. This channel should possess 7 fields, one for each sensor: Pressure, NO2, Temp, UV, CO2, Ozone, Altitude; read the Doxygen for `sendData()` in `postData.c` to understand what parameters are required. You will also require an API key, which will be provided once you create a channel. There are two keys, **Write API Key** and **Read API Keys**, make sure you the write key.

Refer to [ThingSpeak](https://community.thingspeak.com/documentation%20.../api/) to understand how the API works

## Project Components
### Ground Control Station
* Any Linux machine
* Ubiquiti dish


### Payload (Weather Balloon)
* Raspberry Pi 4
* 2x GoPro Hero7
* Sensor
* Ubiquiti antenna


### Sensor
* Arduino UNO
* [JBtek BMP180 (Pressure, Altitude, Temperature Sensor)](https://www.amazon.com/JBtek-Barometric-Pressure-Temperature-Altitude/dp/B00UUS12PO)
* [MICS-2714 (NO2 Sensor)](https://acrobotic.com/products/brk-00007)
* [Adafruit UV Sensor](https://www.adafruit.com/product/1918)
* [Gravity I2C Ozone Sensor](https://www.amazon.com/Gravity-Sensor-Arduino-Raspberry-0-10ppm/dp/B086MSZRFN/ref=sr_1_5?dchild=1&keywords=ozone+sensor&qid=1612297440&sr=8-5) 
* [DFRobot Analog CO2 Gas Sensor](https://www.amazon.com/gp/product/B00R5CCH7U/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
