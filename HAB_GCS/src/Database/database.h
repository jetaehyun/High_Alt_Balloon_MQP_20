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
bool insertDatabase(int id, float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude);
bool closeDB();
bool createDir();

static int callback(void* data, int argc, char** argv, char** azColName) 
{ 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    printf("\n"); 
    return 0; 
} 

#endif