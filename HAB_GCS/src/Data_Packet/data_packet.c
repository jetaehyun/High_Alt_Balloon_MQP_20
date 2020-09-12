#include "header/data_packet.h"

bool HAB_payload_unpack(uint8_t* payload, struct HAB_payload_t *data) {

    if(!confirm_checksum(payload)) return false;

    data->payload_type = unpack_8(payload);

    if(data->payload_type == SENSOR_PAYLOAD) {

        for(int i = 0; i < 24; i++) {
            data->payload[i] = payload[i + 1];
        }


    } else {

        data->payload = (payload + 1);

    }

    data->checksum = 0;

    return true;
}

uint8_t HAB_payload_pack(uint8_t *payload, struct HAB_payload_t *message) {
    return 0;
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