#include <Arduino.h>
/* SFE_BMP180 library example sketch
This sketch shows how to use the SFE_BMP180 library to read the
Bosch BMP180 barometric pressure sensor.
https://www.sparkfun.com/products/11824
Like most pressure sensors, the BMP180 measures absolute pressure.
This is the actual ambient pressure seen by the device, which will
vary with both altitude and weather.
Before taking a pressure reading you must take a temparture reading.
This is done with startTemperature() and getTemperature().
The result is in degrees C.
Once you have a temperature reading, you can take a pressure reading.
This is done with startPressure() and getPressure().
The result is in millibar (mb) aka hectopascals (hPa).
If you'll be monitoring weather patterns, you will probably want to
remove the effects of altitude. This will produce readings that can
be compared to the published pressure readings from other locations.
To do this, use the sealevel() function. You will need to provide
the known altitude at which the pressure was measured.
If you want to measure altitude, you will need to know the pressure
at a baseline altitude. This can be average sealevel pressure, or
a previous pressure reading at your altitude, in which case
subsequent altitude readings will be + or - the initial baseline.
This is done with the altitude() function.
Hardware connections:
- (GND) to GND
+ (VDD) to 3.3V
(WARNING: do not connect + to 5V or the sensor will be damaged!)
You will also need to connect the I2C pins (SCL and SDA) to your
Arduino. The pins are different on different Arduinos:
Any Arduino pins labeled:  SDA  SCL
Uno, Redboard, Pro:        A4   A5
Mega2560, Due:             20   21
Leonardo:                   2    3
Leave the IO (VDDIO) pin unconnected. This pin is for connecting
the BMP180 to systems with lower logic levels such as 1.8V
Have fun! -Your friends at SparkFun.
The SFE_BMP180 library uses floating-point equations developed by the
Weather Station Data Logger project: http://wmrx00.sourceforge.net/
Our example code uses the "beerware" license. You can do anything
you like with this code. No really, anything. If you find it useful,
buy me a beer someday.
V10 Mike Grusin, SparkFun Electronics 10/24/2013
*/

// Your sketch must #include this library, and the Wire library.
// (Wire is a standard library included with Arduino.):

#include <SFE_BMP180.h>
#include <Wire.h>
#include <data_packet.h>
#include <sensor_payload.h>
#include "DFRobot_OzoneSensor.h"

#define COLLECT_NUMBER   20              // collect number, the collection range is 1-100
#define Ozone_IICAddress ADDRESS_3
#define UV_SENSOR_PIN A0
/*   iic slave Address, The default is ADDRESS_3
       ADDRESS_0               0x70      // iic device address
       ADDRESS_1               0x71
       ADDRESS_2               0x72
       ADDRESS_3               0x73
*/
DFRobot_OzoneSensor Ozone;

double baseline;
double T, P, p0, a;
//int const UV_SENSOR_PIN = A0;
int const NO2_SENSOR_PIN = A1;
int const CO2_SENSOR_PIN = A2;


float NO2resistance; //NO2 variables
float NO2SeriesResistor = 2200;
float NO2measure = 0;
char pressure_on = 1;

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 36.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
#define ZERO_POINT_VOLTAGE_CO2 (0.274) //define the output of the sensor in volts when the concentration of CO2 is 400PPM (Vmeasure/8.5)
#define REACTION_VOLTGAE_CO2 (0.020) //define the voltage drop of the sensor when move the sensor from air into 1000ppm CO2
#define ADC_OFFSET 0

float CO2Curve[3]  =  {2.602,ZERO_POINT_VOLTAGE_CO2,(REACTION_VOLTGAE_CO2/(2.602-3))};

double getPressure();

void setup()
{
  Serial.begin(9600);
  //Serial.println("REBOOT");
  
  
  // Initialize the sensor (it is important to get calibration values stored on the device).

  if (pressure.begin()){
    //Serial.println("BMP180 init success");
    pressure_on = 1;
    }
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    //Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }

  //Serial.println("Calibration parameters");
  //Serial.print("R0 = ");
  //Serial.print(MQ131.getR0());
  //Serial.println(" Ohms");
  //Serial.print("Time to heat = ");
  //Serial.print(MQ131.getTimeToRead());
  //Serial.println(" s");

  baseline = getPressure();

  while(!Ozone.begin(Ozone_IICAddress)) {
    //Serial.println("I2c device number error !");
    delay(1000);
  }  
  //Serial.println("I2c connect success !");
/*   Set iic mode, active mode or passive mode
       MEASURE_MODE_AUTOMATIC            // active  mode
       MEASURE_MODE_PASSIVE              // passive mode
*/
    Ozone.SetModes(MEASURE_MODE_PASSIVE);
}

int convertUV (float UVvalue) {
  int index;
  if (UVvalue < 50) {
    index = 0;
  }
  else if (UVvalue < 227) {
    index = 1;
  }
  else if (UVvalue < 318) {
    index = 2;
  }
  else if (UVvalue < 408) {
    index = 3;
  }
  else if (UVvalue < 503) {
    index = 4;
  }
  else if (UVvalue < 606) {
    index = 5;
  }
  else if (UVvalue < 696) {
    index = 6;
  }
  else if (UVvalue < 795) {
    index = 7;
  }
  else if (UVvalue < 881) {
    index = 8;
  }
  else if (UVvalue < 976) {
    index = 9;
  }
  else if (UVvalue < 1079) {
    index = 10;
  }
  else {
    index = 11;
  }
  return index;
}

int  CO2GetPercentage(float volts, float *pcurve)
{
   if ((volts/8.5 )>=ZERO_POINT_VOLTAGE_CO2) {
      return -1;
   } else {
      return pow(10, ((volts/8.5)-pcurve[1])/pcurve[2]+pcurve[0]);
   }
}

void systemDelay(int wait) {
  long unsigned int timeStamp = millis();
  while ((millis() - timeStamp) < wait) { // wait designated time
    // do nothing
  }
}


double getPressure()
{
  char status;

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return (P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}


void loop()
{

  char status;
  double T,P,p0,a;

  int32_t temperature_payload = 0;
  int32_t pressure_payload = 0;
  int32_t altitude_payload = 0;
  int32_t CO2_payload = 0;
  int32_t O3_payload = 0;

  // Loop here getting pressure readings every 10 seconds.

  // If you want sea-level-compensated pressure, as used in weather reports,
  // you will need to know the altitude at which your measurements are taken.
  // We're using a constant called ALTITUDE in this sketch:
  
  // Serial.println();
  // Serial.print("provided altitude: ");
  // Serial.print(ALTITUDE,0);
  // Serial.print(" meters, ");
  // Serial.print(ALTITUDE*3.28084,0);
  // Serial.println(" feet");
  
  // If you want to measure altitude, and not pressure, you will instead need
  // to provide a known baseline pressure. This is shown at the end of the sketch.

  // You must first get a temperature measurement to perform a pressure reading.
  
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.



  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      //Print out the measurement:
      // Serial.print("temperature: ");
      // Serial.print(T,2);
      // Serial.print(" deg C, ");
      // Serial.print((9.0/5.0)*T+32.0,2);
      // Serial.println(" deg F");
      temperature_payload = T*1000;
      
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          //Print out the measurement:
          // Serial.print("absolute pressure: ");
          // Serial.print(P,2);
          // Serial.print(" mb, ");
          // Serial.print(P*0.0295333727,2);
          // Serial.println(" inHg");
          pressure_payload = (P*0.0295333727*1000);

          // The pressure sensor returns abolute pressure, which varies with altitude.
          // To remove the effects of altitude, use the sealevel function and your current altitude.
          // This number is commonly used in weather reports.
          // Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
          // Result: p0 = sea-level compensated pressure in mb

          p0 = pressure.sealevel(P,ALTITUDE); // we're at 1655 meters (Boulder, CO)
          // Serial.print("relative (sea-level) pressure: ");
          // Serial.print(p0,2);
          // Serial.print(" mb, ");
          // Serial.print(p0*0.0295333727,2);
          // Serial.println(" inHg");

          // On the other hand, if you want to determine your altitude from the pressure reading,
          // use the altitude function along with a baseline pressure (sea-level or other).
          // Parameters: P = absolute pressure in mb, p0 = baseline pressure in mb.
          // Result: a = altitude in m.

          a = pressure.altitude(P,baseline);
          // Serial.print("computed altitude: ");
          // Serial.print(a,0);
          // Serial.print(" meters, ");
          // Serial.print(a*3.28084,0);
          // Serial.println(" feet");
          altitude_payload = (int32_t)(a*3.28084*1000);
        }
        else pressure_on = 2; ////Serial.println("error retrieving pressure measurement\n");
      }
      else pressure_on = 3; ////Serial.println("error starting pressure measurement\n");
    }
    else pressure_on = 4; ////Serial.println("error retrieving temperature measurement\n");
  }
  else pressure_on = 5; ////Serial.println("error starting temperature measurement\n");

  /*   Smooth data collection
       COLLECT_NUMBER                    // The collection range is 1-100
*/
  int16_t ozoneConcentration = Ozone.ReadOzoneData(COLLECT_NUMBER);
  O3_payload = ((int32_t)(Ozone.ReadOzoneData(COLLECT_NUMBER)) * 1000);
  // Serial.print("Ozone concentration is ");
  // Serial.print(ozoneConcentration);
  // Serial.println(" PPB.");

  int UVReading = analogRead(UV_SENSOR_PIN); // Get raw sensor reading for UV Sensor
  float UVVolts = UVReading * 5 / 1024.0; //Expected voltage output is between 0V and 1V
  float UV_index = convertUV (UVReading); //Sensor reads a UV index value between 1 and 10
  //  Serial.print ("Raw ADC data: ");
  //  Serial.print (UVReading);
  //  Serial.print ("  UV Index: ");
  //  Serial.println (UV_index);
  int32_t UV_payload = (int32_t)(UV_index * 1000); //Set the value to transmit to Raspberry Pi, increase by a factor of 1000 to maintain resolution

  
  int NO2Reading = analogRead(NO2_SENSOR_PIN) + 1; // Get raw sensor reading for UV Sensor
  float NO2Resistance = NO2SeriesResistor * ((1203.0 / (NO2Reading - ADC_OFFSET)) -1); //Convert reading into resistance value
  float NO2_index = NO2Resistance / 100; //Convert into index
  int32_t NO2_payload = ((int32_t)((NO2_index / 0.0409) / 46.0055))*1000; //Set value to transmit to Raspberry Pi, increase by a factor of a 1000
  // Serial.print ("Raw ADC data: ");
  // Serial.print (NO2Reading);
  // Serial.print ("  NO2 Index: ");
  // Serial.print (NO2_payload/1000);
  // Serial.println (" ppb");


  int CO2Reading = analogRead(CO2_SENSOR_PIN); // Get raw sensor reading for CO2 Sensor
  float CO2Volts = (CO2Reading) * 5 / 1024.0;
  float CO2_index = CO2GetPercentage(CO2Volts, CO2Curve);
  // Serial.print ("Raw ADC data: ");
  // Serial.print (CO2Reading);
  // Serial.print ("  CO2 Index : ");
  if (CO2_index == -1) {
    CO2_payload = 400000; //Set reading to 400 (lowest reading for the sensor)
    // Serial.println ("< 400 ppm"); 
    }
  else {
    CO2_payload = (CO2_index * 1000); // Set value to transmit to Respberry Pi
    // Serial.print(CO2_index); 
    // Serial.println(" ppm");
  }  

//Values for Pi: temperature_payload, pressure_payload, altitute_payload, UV_Payload, NO2_payload, CO2_payload, O3_payload


  
    uint8_t SENSOR_DATA_PAYLOAD[28];
    uint8_t SENSOR_DATA_TX[30];
    struct sensor_data_t *test = create_sensor_payload(pressure_payload,NO2_payload,temperature_payload, UV_payload, CO2_payload, O3_payload, altitude_payload);
    //struct sensor_data_t *test = create_sensor_payload(32,32,3,2,4,2,2);
    sensor_payload_pack(SENSOR_DATA_PAYLOAD, test);
    struct HAB_payload_t *test2 = HAB_payload_create(SENSOR_PAYLOAD, SENSOR_DATA_PAYLOAD);
    HAB_payload_pack(SENSOR_DATA_TX, test2);
    Serial.write(SENSOR_DATA_TX, 30);
    free_HAB_data(test2);
    free_sensor_payload(test);
    while(Serial.available()){
      Serial.read();
    }
    // Serial.write(30);
    systemDelay(5000);
  
}



