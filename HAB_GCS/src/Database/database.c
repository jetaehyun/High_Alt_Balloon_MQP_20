#include "database.h"

sqlite3 *db;
const char *table = "CREATE TABLE Sensor ("
                    "ID INT PRIMARY KEY NOT NULL, "
                    "pressure_sensor REAL, "
                    "NO2_sensor REAL, "
                    "temp_sensor REAL, "
                    "UV_sensor REAL, "
                    "CO2_sensor REAL, "
                    "Ozone_sensor REAL, "
                    "Altitude Real);";

/**
 * @brief starts database
 * 
 * @return true successful
 * @return false failed to open db
 */
bool startDB() {
    printf("----------------------------------------------------------------------------\n\n");
    
    createDir();

    if(sqlite3_open("DataLog/sensor_data.db", &db) == 1) {
        return false;
    }

    char *err = 0;
    int ok = sqlite3_exec(db, table, callback, 0, &err);

    if(ok != SQLITE_OK) {
        fprintf(stderr, "SQL Error: %s\n\n", err);
        sqlite3_free(err);
    }
    else {
        printf("Sensor table created...\n\n");
    }

    printf("----------------------------------------------------------------------------\n\n");

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
 * @param id 
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
bool insertDatabase(int id, float pressure_sensor, float NO2_sensor, float temp_sensor, float UV_sensor, float CO2_sensor, float Ozone_sensor, float altitude) {    
    char insert[1024] = {'\n'};
    
    sprintf(insert, "INSERT INTO Sensor VALUES(%d, %f, %f, %f, %f, %f, %f, %f);", id, pressure_sensor, NO2_sensor, temp_sensor, UV_sensor, CO2_sensor, Ozone_sensor, altitude);

    char *data;
    int rc = sqlite3_exec(db, insert, callback, (void*)data, NULL);
    char *err = 0;

    if(rc != SQLITE_OK) {
        printf("Sensor data could not be inserted...\n");
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

    char *data;
    int rc = sqlite3_exec(db, select, callback, (void*)data, NULL);

    if(rc != SQLITE_OK) {
        printf("Sensor Table does not exist...\n");
        return false;
    }

    printf("Sensor Table exists...\n");

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

    char *data;
    int rc = sqlite3_exec(db, drop, callback, (void*)data, NULL);

    if(rc != SQLITE_OK) {
        printf("Sensor table failed to drop...\n");
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
        printf("DataLog directory was not made...\n");
        return false;
    }

    printf("DataLog directory created...\n");
    return true;
    
}