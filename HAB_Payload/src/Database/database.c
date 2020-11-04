#include "database.h"

sqlite3 *db;
int primary_key_id = 0;
const char *table = "CREATE TABLE Sensor ("
                    "sensorID INT PRIMARY KEY NOT NULL, "
                    "pressure_sensor REAL, "
                    "NO2_sensor REAL, "
                    "temp_sensor REAL, "
                    "UV_sensor REAL, "
                    "CO2_sensor REAL, "
                    "Ozone_sensor REAL, "
                    "Altitude Real);";

/**
 * @brief print SQL error message and free
 * 
 * @param msg error message to print
 */
void printErr(char *msg)  {
    fprintf(stderr, "SQL Error: %s\n", msg);
    sqlite3_free(msg);
}

/**
 * @brief callback function for SQL query
 * 
 * @param data 
 * @param argc 
 * @param argv 
 * @param azColName 
 * @return int 
 */
int callback(void* data, int argc, char** argv, char** azColName) { 
    int i; 
    fprintf(stderr, "%s: ", (const char*)data); 
  
    for (i = 0; i < argc; i++) { 
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL"); 
    } 
  
    printf("\n"); 
    return 0; 
} 

/**
 * @brief set current primary key id 
 * 
 * @param data 
 * @param argc 
 * @param argv 
 * @param azColName 
 * @return int 
 */
int setIDCallback(void* data, int argc, char** argv, char** azColName) {
    int currPrimeKey = atoi(argv[0]); 
    
    if(argc == 0) {

        primary_key_id = 0;
    } else {

        primary_key_id = currPrimeKey + 1;
    }

    return 0; 
}

/**
 * @brief query the last known id and set it via callback
 * 
 */
void setID() {
    
    const char *query = "SELECT sensorID FROM Sensor ORDER BY sensorID DESC LIMIT 1;";
    
    char *err = 0;
    int rc = 0;

    rc = sqlite3_exec(db, query, setIDCallback, 0, &err);
    
    if(rc != SQLITE_OK) {
        printErr(err);

    }

}

/**
 * @brief starts database
 * 
 * @return true successful
 * @return false failed to open db
 */
bool startDB() {
    printf("----------------------------------------------------------------------------\n\n");
    
    createDir(); 

    sqlite3_open("DataLog/sensor_data.db", &db);
   
    char *err = 0;
    int ok = sqlite3_exec(db, table, callback, 0, &err);

    if(ok != SQLITE_OK) {
        printErr(err);

    }
    else {
        printf("Sensor table created...");
    }

    setID();

    printf("\n\n----------------------------------------------------------------------------\n\n");

    return true;
}

/**
 * @brief closes db
 * 
 * @return true if closed
 * @return false if not closed
 */
bool closeDB() {
    printf("----------------------------------------------------------------------------\n\n");

    if(db == NULL) {
        printf("Nothing to close...\n\n");
        return false;
    }

    sqlite3_close(db);
    printf("DB closed...\n\n");
    printf("----------------------------------------------------------------------------\n\n");

    return true;

}

/**
 * @brief inserts data into db
 * 
 * @param pressure_sensor 
 * @param NO2_sensor 
 * @param temp_sensor 
 * @param UV_sensor 
 * @param CO2_sensor 
 * @param Ozone_sensor 
 * @param altitude
 * @return true inserted successfully
 * @return false failed to insert
 */
bool insertDatabase(float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude) {    
    char insert[1024] = {'\n'};
    
    sprintf(insert, "INSERT INTO Sensor VALUES(%d, %f, %f, %f, %f, %f, %f, %f);", primary_key_id, pressure_sensor, NO2_sensor, temp_sensor, UV_sensor, CO2_sensor, Ozone_sensor, altitude);
    primary_key_id++;

    char *err = 0;
    int rc = sqlite3_exec(db, insert, callback, 0, &err);

    if(rc != SQLITE_OK) {
        printErr(err);
        return false;
    }

    printf("Sensor data inserted...\n");
    memset(insert, 0, sizeof(insert));
    return true;
}

/**
 * @brief queries entire db, use to check
 * 
 * @return true query successful
 * @return false table does not exist
 */
bool checkTable() {
    const char *select = "SELECT * FROM Sensor;";

    char *err = 0;
    int rc = sqlite3_exec(db, select, callback, 0, &err);

    if(rc != SQLITE_OK) {
        printErr(err);
        return false;
    }

    return true;

}

/**
 * @brief drops Table from DB
 * 
 * @return true table dropped
 * @return false table did not drop - maybe doesn't exist
 */
bool dropTable() {
    const char *drop = "DROP TABLE Sensor;";

    char *err = 0;
    int rc = sqlite3_exec(db, drop, callback, 0, &err);

    if(rc != SQLITE_OK) {
        printErr(err);        
        return false;
    }

    printf("Sensor table has been dropped...\n");

    return true;
}

/**
 * @brief WARNING! WILL DELETE DATABASE...
 * 
 * @return true db file deleted
 * @return false db file not deleted
 */
bool dropDB() {

    if(db != NULL) {
        printf("Close DB connection...\n");
        return false;
    }

    printf("Database has been dropped...\n");
    remove("DataLog/sensor_data.db");
    return true;
}

/**
 * @brief Create directory for db 
 * 
 * @return true created
 * @return false !created
 */
bool createDir() {
    
    int ok = mkdir("DataLog", 0777);

    if(ok == -1) {
        printf("DataLog directory already exists...\n");
        return false;
    }

    printf("DataLog directory created...\n");
    return true;
    
}