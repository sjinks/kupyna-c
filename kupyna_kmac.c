#include <string.h>
#include "kupyna256.h"
#include "kupyna512.h"
#include "kupyna_kmac.h"

struct padding_t {
    size_t data_nbytes;
    size_t pad_nbytes;
    uint8_t padding[128 * 2];
};

static void pad256(const uint8_t* data, size_t msg_nbytes, struct padding_t* r)
{
    int i;

    size_t zero_nbytes = ((-(msg_nbytes*8) - 97) % (64 * 8)) / 8;
    size_t nblocks     = msg_nbytes / 64;
    r->pad_nbytes      = msg_nbytes - nblocks * 64;
    r->data_nbytes     = msg_nbytes - r->pad_nbytes;
    const uint8_t* pad_start = data + r->data_nbytes;

    memcpy(r->padding, pad_start, r->pad_nbytes);
    r->padding[r->pad_nbytes] = 0x80;
    ++r->pad_nbytes;

    memset(r->padding + r->pad_nbytes, 0, zero_nbytes);
    r->pad_nbytes += zero_nbytes;
    for (i=0; i<(96/8); ++i, ++r->pad_nbytes) {
        if (i < sizeof(size_t)) {
            r->padding[r->pad_nbytes] = (uint8_t)((msg_nbytes * 8) >> (i * 8));
        }
        else {
            r->padding[r->pad_nbytes] = 0;
        }
    }
}

static void pad512(const uint8_t* data, size_t msg_nbytes, struct padding_t* r)
{
    int i;

    size_t zero_nbytes = ((-(msg_nbytes*8) - 97) % (128 * 8)) / 8;
    size_t nblocks     = msg_nbytes / 128;
    r->pad_nbytes      = msg_nbytes - nblocks * 128;
    r->data_nbytes     = msg_nbytes - r->pad_nbytes;
    const uint8_t* pad_start = data + r->data_nbytes;

    memcpy(r->padding, pad_start, r->pad_nbytes);
    r->padding[r->pad_nbytes] = 0x80;
    ++r->pad_nbytes;

    memset(r->padding + r->pad_nbytes, 0, zero_nbytes);
    r->pad_nbytes += zero_nbytes;
    for (i=0; i<(96/8); ++i, ++r->pad_nbytes) {
        if (i < sizeof(size_t)) {
            r->padding[r->pad_nbytes] = (uint8_t)((msg_nbytes * 8) >> (i * 8));
        }
        else {
            r->padding[r->pad_nbytes] = 0;
        }
    }
}

void kupyna256_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac)
{
    struct kupyna256_ctx_t ctx;
    struct padding_t k;
    struct padding_t m;
    uint8_t ik[256/8];

    kupyna256_init(&ctx);

    pad256(key,  256 / 8, &k);
    pad256(data, len,     &m);

    kupyna256_update(&ctx, k.padding, k.pad_nbytes);

    if (m.data_nbytes > 0) {
        kupyna256_update(&ctx, data, m.data_nbytes);
    }

    kupyna256_update(&ctx, m.padding, m.pad_nbytes);

    for (size_t i=0; i<256/8; ++i) {
        ik[i] = ~key[i];
    }

    kupyna256_update(&ctx, ik, 256/8);
    kupyna256_final(&ctx, mac);
}

void kupyna384_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac)
{
    struct kupyna512_ctx_t ctx;
    struct padding_t k;
    struct padding_t m;
    uint8_t ik[512/8];

    kupyna512_init(&ctx);

    pad512(key,  384 / 8, &k);
    pad512(data, len,     &m);

    kupyna512_update(&ctx, k.padding, k.pad_nbytes);

    if (m.data_nbytes > 0) {
        kupyna512_update(&ctx, data, m.data_nbytes);
    }

    kupyna512_update(&ctx, m.padding, m.pad_nbytes);

    for (size_t i=0; i<384/8; ++i) {
        ik[i] = ~key[i];
    }

    kupyna512_update(&ctx, ik, 384/8);
    kupyna512_final2(&ctx, mac, 384);
}

void kupyna512_kmac(const uint8_t* key, const uint8_t* data, size_t len, uint8_t* mac)
{
    struct kupyna512_ctx_t ctx;
    struct padding_t k;
    struct padding_t m;
    uint8_t ik[512/8];

    kupyna512_init(&ctx);

    pad512(key,  512 / 8, &k);
    pad512(data, len,     &m);

    if (k.data_nbytes > 0) {
        kupyna512_update(&ctx, key, k.data_nbytes);
    }

    kupyna512_update(&ctx, k.padding, k.pad_nbytes);

    if (m.data_nbytes > 0) {
        kupyna512_update(&ctx, data, m.data_nbytes);
    }

    kupyna512_update(&ctx, m.padding, m.pad_nbytes);

    for (size_t i=0; i<512/8; ++i) {
        ik[i] = ~key[i];
    }

    kupyna512_update(&ctx, ik, 512/8);
    kupyna512_final(&ctx, mac);
}
