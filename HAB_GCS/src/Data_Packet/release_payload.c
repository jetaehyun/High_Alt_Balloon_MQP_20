#include "header/release_payload.h"

struct release_data_t release_payload_unpack(uint8_t *payload) {
    struct release_data_t data;

    data.confirmation = unpack_8(payload);

    return data;
}

uint8_t release_payload_pack(uint8_t *payload, struct release_data_t *data) {

    pack_8(payload, data->confirmation);

    return 1;

}

struct release_data_t *create_release_payload(uint8_t confirmation) {
    struct release_data_t *data = malloc(sizeof(struct release_data_t));

    data->confirmation = confirmation;

    return data;
}