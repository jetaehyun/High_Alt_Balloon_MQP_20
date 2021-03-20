#include "release_payload.h"

/**
 * @brief Create a release payload object
 * 
 * @param confirmation 
 * @return struct release_data_t* 
 */
struct release_data_t *create_release_payload(uint8_t confirmation) {
    struct release_data_t *data = malloc(sizeof(struct release_data_t));

    data->confirmation = confirmation;

    return data;
}

/**
 * @brief function to unpack payload into release struct
 * 
 * @param payload byte array to unpack
 * @return struct release_data_t 
 */
struct release_data_t release_payload_unpack(uint8_t *payload) {
    struct release_data_t data;

    data.confirmation = unpack_8(payload);

    return data;
}

/**
 * @brief function to pack data into payload
 * 
 * @param payload byte array to pack data into
 * @param data data to be packed
 * @return uint8_t returns number of bytes written
 */
uint8_t release_payload_pack(uint8_t *payload, struct release_data_t *data) {

    pack_8(payload, data->confirmation);

    return 1;

}
