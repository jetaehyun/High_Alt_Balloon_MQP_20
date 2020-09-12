#include "header/sensor_payload.h"

struct sensor_data_t *create_sensor_payload(int32_t baro_sensor, int32_t NO2_sensor, int32_t temp_sensor, int32_t UV_sensor, int32_t CO2_sensor, int32_t Ozone_sensor) {
    struct sensor_data_t *data = malloc(sizeof(struct sensor_data_t));

    data->baro_sensor = baro_sensor;
    data->NO2_sensor = NO2_sensor;
    data->temp_sensor = temp_sensor;
    data->UV_sensor = UV_sensor;
    data->CO2_sensor = CO2_sensor;
    data->Ozone_sensor = Ozone_sensor;

    return data;
}

struct sensor_data_t sensor_payload_unpack(uint8_t* payload) {
    struct sensor_data_t data;

    data.baro_sensor = unpack_32(payload);
    data.NO2_sensor = unpack_32(payload + 4);
    data.temp_sensor = unpack_32(payload + 8);
    data.UV_sensor = unpack_32(payload + 12);
    data.CO2_sensor = unpack_32(payload + 16);
    data.Ozone_sensor = unpack_32(payload + 20);
 
    return data;
}

uint8_t sensor_payload_pack(uint8_t *payload, struct sensor_data_t *data) {

    pack_32(payload, data->baro_sensor);
    pack_32(payload + 4, data->NO2_sensor);
    pack_32(payload + 8, data->temp_sensor);
    pack_32(payload + 12, data->UV_sensor);
    pack_32(payload + 16, data->CO2_sensor);
    pack_32(payload + 20, data->Ozone_sensor);

    return 24;

}
