#include "data_packet.h"

struct HAB_payload_t *HAB_payload_create(uint8_t payload_type, uint8_t *payload) {
    struct HAB_payload_t *data = malloc(sizeof(struct HAB_payload_t));

    data->payload_type = payload_type;

    for(int i = 0; i < 28; i++) {
        data->payload[i] = payload[i];
    }

    data->checksum = 0; // checksum won't be calculated until the data is packed...

    return data;
}


bool HAB_payload_unpack(uint8_t* payload, struct HAB_payload_t *data) {

    if(!confirm_checksum(payload, 30)) return false;

    data->payload_type = unpack_8(payload);

    for(int i = 0; i < 28; i++) {
        data->payload[i] = payload[1 + i];
    }

    data->checksum = payload[29];

    return true;
}

uint8_t HAB_payload_pack(uint8_t *payload, struct HAB_payload_t *data) {
    pack_8(payload, data->payload_type);
    for(int i = 0; i < 28; i++) {
        pack_8(payload + i + 1, data->payload[i]);
    }

    uint8_t checksum = calculate_checksum(payload, 28);

    pack_8(payload + 29, checksum);

    return 26;
}


uint8_t calculate_checksum(uint8_t *payload, int size) {
    uint8_t checksum = 0;

    for(int i = 0; i < size; i++) {
        checksum += payload[i];
    }

    return ~checksum;

}

bool confirm_checksum(uint8_t* payload, int size) {

    uint8_t checksum = 0;

    for(int i = 0; i < size; i++) {
        checksum += payload[i];
    }

    if(checksum == 0xFF) return true;

    return false;

}