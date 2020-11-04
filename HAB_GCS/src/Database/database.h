#ifndef DATABASE_H
#define DATABASE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <string.h>
#include <sys/stat.h>

bool startDB();
bool checkTable();
bool dropTable();
bool dropDB();
void setID();
void printErr(char *msg);
bool insertDatabase(float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude);
bool closeDB();
bool createDir();

#endif