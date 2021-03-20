#include "sensor_payload.h"

/**
 * @brief Create a sensor payload object
 * 
 * @param baro_sensor 
 * @param NO2_sensor 
 * @param temp_sensor 
 * @param UV_sensor 
 * @param CO2_sensor 
 * @param Ozone_sensor 
 * @return struct sensor_data_t* 
 */
struct sensor_data_t *create_sensor_payload(int32_t pressure_sensor, int32_t NO2_sensor, int32_t temp_sensor, int32_t UV_sensor, int32_t CO2_sensor, int32_t Ozone_sensor, int32_t altitude) {
    struct sensor_data_t *data = malloc(sizeof(struct sensor_data_t));

    data->pressure_sensor = pressure_sensor;
    data->NO2_sensor = NO2_sensor;
    data->temp_sensor = temp_sensor;
    data->UV_sensor = UV_sensor;
    data->CO2_sensor = CO2_sensor;
    data->Ozone_sensor = Ozone_sensor;
    data->altitude = altitude;

    return data;
}

/**
 * @brief function to unpack sensor data
 *  
 * @param payload data to unpack
 * @return struct sensor_data_t returns the data in sensor struct
 */
struct sensor_data_t sensor_payload_unpack(uint8_t* payload) {
    struct sensor_data_t data;

    data.pressure_sensor = unpack_32(payload);
    data.NO2_sensor = unpack_32(payload + 4);
    data.temp_sensor = unpack_32(payload + 8);
    data.UV_sensor = unpack_32(payload + 12);
    data.CO2_sensor = unpack_32(payload + 16);
    data.Ozone_sensor = unpack_32(payload + 20);
    data.altitude = unpack_32(payload + 24);
 
    return data;
}

/**
 * @brief function to pack data into bytes
 * 
 * @param payload array of bytes to store data into
 * @param data data to be stored
 * @return uint8_t number of written bytes
 */
uint8_t sensor_payload_pack(uint8_t *payload, struct sensor_data_t *data) {

    pack_32(payload, data->pressure_sensor);
    pack_32(payload + 4, data->NO2_sensor);
    pack_32(payload + 8, data->temp_sensor);
    pack_32(payload + 12, data->UV_sensor);
    pack_32(payload + 16, data->CO2_sensor);
    pack_32(payload + 20, data->Ozone_sensor);
    pack_32(payload + 24, data->altitude);

    return 24;

}
