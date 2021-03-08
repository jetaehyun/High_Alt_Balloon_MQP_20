# High Altitude Balloon for Measuring Environmental Pollution MQP '20-21

## CURRENTLY BEING DEVELOPED

## About this project
This is the repository for the High Altitude Balloon Major Qualifying Project(MQP) at Worcester Polytechnic Institute(WPI). The overarching objective of this MQP is to collect Greenhouse Gas(GHG) (CO2, NO2, etc.) emissions and other data (e.g. temperature, UV, etc.) from the Stratosphere. The repository is broken into three main code bases (Sensor, Ground Control Station(GCS), and Payload) for different tasks. The system works by obtaining the sensor data and packaging them into data packets. From there, the data packets are transferred by USB and Radio. The Sensor obtains and transmits data to the Payload, via USB. Once the data packet has been received, it streams it back down to the the GCS via WiFi bridge. The data packet's integrity is confirmed with a checksum. 

# Table of Contents
- [About this project](#about-this-project)
- [Tools and Software](#devices-software)
- [Libraries](#libraries)
- [Ground Control Station](#hab_gcs)
- [Payload (Weather Balloon)](#hab_payload)
  * [How to compile via SSH](#how-to-compile-via-ssh)
- [Sensors](#hab_nano_sensor)
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
**SQLite** was used to record all sensor data, on the payload and on the GCS. We decided to create two different databases in case we lost/damaged the payload and because the payload cannot stream data to a cloud service.
* Run `sudo apt-get install sqlite3 libsqlite3-dev`

**screen** to run the payload program on a different process after connecting via SSH
* Run `sudo apt-get install screen`

## HAB_GCS
### Description
To receive the data that is being sent to the ground, a GCS is necessary to capture the incoming sensor data. The GCS can be any computer that runs a Linux based OS. 

### How to run program
1. Enter src directory
2. Make sure you have the required libraries installed
3. Run `make` 
4. Run `./gcs.exe`

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
6. Run `./gcs.exe`

## HAB_NANO_Sensor
### Description
To collect sensor data, while keeping in mind of the physical dimensions of the payload, an Arduino UNO was selected. The UNO is tasked with reading the sensor data and packing them for transmission to the ***HAB_Payload***. Note. make sure that there are no *Serial.println()* or any other functions that write to the data line except for the one that writes the sensor data. If you do not, you have have garbage data on the receiving end.

### How to upload program
Open visual studio code and import the directory via **PlatformIO**. The .ini file should automaticaly be recognized and it should allow you to upload new code.

## Project Components
### Ground Control Station
* Any Linux machine
* Ubiquiti dish
* Ubiquity antenna
### Payload (Weather Balloon)
* Raspberry Pi 4
* 2x GoPro Hero7
* Webcam (**WIP**)
* Sensor
* Ubiquiti antenna
### Sensor
* Arduino UNO
* [JBtek BMP180 (Pressure, Altitude, Temperature Sensor)](https://www.amazon.com/JBtek-Barometric-Pressure-Temperature-Altitude/dp/B00UUS12PO)
* [MICS-2714 (NO2 Sensor)](https://acrobotic.com/products/brk-00007)
* [Adafruit UV Sensor](https://www.adafruit.com/product/1918)
* [Gravity I2C Ozone Sensor](https://www.amazon.com/Gravity-Sensor-Arduino-Raspberry-0-10ppm/dp/B086MSZRFN/ref=sr_1_5?dchild=1&keywords=ozone+sensor&qid=1612297440&sr=8-5) 
* [DFRobot Analog CO2 Gas Sensor](https://www.amazon.com/gp/product/B00R5CCH7U/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
