#ifndef POSTDATA_H
#define POSTDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

bool connectWithServer();
void closeConnection();
void sendData(float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude);

#endif