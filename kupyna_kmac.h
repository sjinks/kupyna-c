#ifndef KUPYNA_KMAC_H
#define KUPYNA_KMAC_H

#include <stdint.h>

void kupyna256_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);
void kupyna384_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);
void kupyna512_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac);

#endif /* KUPYNA_KMAC_H */
