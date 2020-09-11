#include "sensor_data.h"

bool HAB_unpack(uint8_t* payload, struct HAB_payload_t *data) {

    if(!confirm_checksum(payload)) return false;

    data.payload_type = unpack_8(payload);

    if(payload_type == SENSOR_PAYLOAD) {
        data.payload = malloc(sizeof(struct sensor_data));

        data.payload->baro_sensor = unpack_32(payload + 1)
        data.payload->NO2_sensor = unpack_32(payload + 5);
        data.payload->temp_sensor = unpack_32(payload + 9);
        data.payload->UV_sensor = unpack_32(payload + 13);
        data.payload->CO2_sensor = unpack_32(payload + 17);
        data.payload->Ozone_sensor = unpack_32(payload + 21);

    } else {

        data.payload = malloc(sizeof(struct release_data_t));

        data.payload->confirmation = unpack_8(payload + 1);
    }

    data.checksum = 0;

    return true;
}

uint8_t HAB_payload_pack(uint8_t *payload, struct HAB_payload_t *message) {

}

uint8_t sensor_payload_pack(uint8_t *payload, struct sensor_data_t *data) {

}

uint8_t release_data_pack(uint8_t *payload, struct release_data_t *data) {

}


uint8_t calculate_checksum(uint8_t *payload, int size) {
    uint8_t checksum = 0;

    for(int i = 0; i < size; i++) {
        checksum += payload[i];
    }

    return ~checksum;

}

bool confirm_checksum(uint8_t* payload) {

    uint8_t checksum = 0;

    for(int i = 0; i < 26; i++) {
        checksum += payload[i];
    }

    if(~checksum == 0) return true;

    return false;

}