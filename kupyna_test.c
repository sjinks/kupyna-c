#include <stdlib.h>
#include <stdint.h>
#include <CUnit/Basic.h>
#include "kupyna256.h"
#include "kupyna512.h"

static const uint8_t test_8[1] = { 0xFF };
static const uint8_t test[2048 / 8] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF,
    0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF,
    0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0xDE, 0xDF,
    0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
    0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE, 0xFF
};

static uint8_t result[512/8];

static const uint8_t zero[1048576];

static void kupyna256_chunk()
{
    static uint8_t r1[256/8];

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, zero, 1048576);
    kupyna256_final(&ctx, result);

    kupyna256_init(&ctx);
    kupyna256_update(&ctx, zero,               1048576 / 2);
    kupyna256_update(&ctx, zero + 1048576 / 2, 1048576 / 2);
    kupyna256_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 32));

    kupyna256_init(&ctx);
    for (int i=0; i<1048576; ++i) {
        kupyna256_update(&ctx, zero + i, 1);
    }
    kupyna256_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 32));

    kupyna256_init(&ctx);
    for (int i=0; i<1048576; ++i) {
        kupyna256_update(&ctx, zero + i, 1);
    }
    kupyna256_update(&ctx, zero, 0);
    kupyna256_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 32));

    kupyna256_init(&ctx);
    for (int i=0; i<1048576; i+=2) {
        kupyna256_update(&ctx, zero + i, 2);
    }
    kupyna256_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 32));

    kupyna256_init(&ctx);
    for (int i=0; i<1048576; i+=4) {
        kupyna256_update(&ctx, zero + i, 4);
    }
    kupyna256_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 32));
}

static void kupyna256_512()
{
    static const uint8_t expected[256/8] = {
        0x08, 0xF4, 0xEE, 0x6F, 0x1B, 0xE6, 0x90, 0x3B, 0x32, 0x4C, 0x4E, 0x27, 0x99, 0x0C, 0xB2, 0x4E,
        0xF6, 0x9D, 0xD5, 0x8D, 0xBE, 0x84, 0x81, 0x3E, 0xE0, 0xA5, 0x2F, 0x66, 0x31, 0x23, 0x98, 0x75
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 512 / 8);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna256_1024()
{
    static const uint8_t expected[256/8] = {
        0x0A, 0x94, 0x74, 0xE6, 0x45, 0xA7, 0xD2, 0x5E, 0x25, 0x5E, 0x9E, 0x89, 0xFF, 0xF4, 0x2E, 0xC7,
        0xEB, 0x31, 0x34, 0x90, 0x07, 0x05, 0x92, 0x84, 0xF0, 0xB1, 0x82, 0xE4, 0x52, 0xBD, 0xA8, 0x82
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 1024 / 8);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna256_2048()
{
    static const uint8_t expected[256/8] = {
        0xD3, 0x05, 0xA3, 0x2B, 0x96, 0x3D, 0x14, 0x9D, 0xC7, 0x65, 0xF6, 0x85, 0x94, 0x50, 0x5D, 0x40,
        0x77, 0x02, 0x4F, 0x83, 0x6C, 0x1B, 0xF0, 0x38, 0x06, 0xE1, 0x62, 0x4C, 0xE1, 0x76, 0xC0, 0x8F
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 2048 / 8);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna256_8()
{
    static const uint8_t expected[256/8] = {
        0xEA, 0x76, 0x77, 0xCA, 0x45, 0x26, 0x55, 0x56, 0x80, 0x44, 0x1C, 0x11, 0x79, 0x82, 0xEA, 0x14,
        0x05, 0x9E, 0xA6, 0xD0, 0xD7, 0x12, 0x4D, 0x6E, 0xCD, 0xB3, 0xDE, 0xEC, 0x49, 0xE8, 0x90, 0xF4
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test_8, 8 / 8);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna256_760()
{
    static const uint8_t expected[256/8] = {
        0x10, 0x75, 0xC8, 0xB0, 0xCB, 0x91, 0x0F, 0x11, 0x6B, 0xDA, 0x5F, 0xA1, 0xF1, 0x9C, 0x29, 0xCF,
        0x8E, 0xCC, 0x75, 0xCA, 0xFF, 0x72, 0x08, 0xBA, 0x29, 0x94, 0xB6, 0x8F, 0xC5, 0x6E, 0x8D, 0x16
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 760 / 8);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna256_0()
{
    static const uint8_t expected[256/8] = {
        0xCD, 0x51, 0x01, 0xD1, 0xCC, 0xDF, 0x0D, 0x1D, 0x1F, 0x4A, 0xDA, 0x56, 0xE8, 0x88, 0xCD, 0x72,
        0x4C, 0xA1, 0xA0, 0x83, 0x8A, 0x35, 0x21, 0xE7, 0x13, 0x1D, 0x4F, 0xB7, 0x8D, 0x0F, 0x5E, 0xB6
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 0);
    kupyna256_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 32));
}

static void kupyna48_512()
{
    static const uint8_t expected[48/8] = {
        0x2F, 0x66, 0x31, 0x23, 0x98, 0x75
    };

    struct kupyna256_ctx_t ctx;
    kupyna256_init(&ctx);
    kupyna256_update(&ctx, test, 512 / 8);
    kupyna256_final2(&ctx, result, 48);

    CU_ASSERT(!memcmp(result, expected, 6));
}

static void kupyna512_chunk()
{
    static uint8_t r1[512/8];

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, zero, 1048576);
    kupyna512_final(&ctx, result);

    kupyna512_init(&ctx);
    kupyna512_update(&ctx, zero,               1048576 / 2);
    kupyna512_update(&ctx, zero + 1048576 / 2, 1048576 / 2);
    kupyna512_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 64));

    kupyna512_init(&ctx);
    for (int i=0; i<1048576; ++i) {
        kupyna512_update(&ctx, zero + i, 1);
    }
    kupyna512_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 64));

    kupyna512_init(&ctx);
    for (int i=0; i<1048576; ++i) {
        kupyna512_update(&ctx, zero + i, 1);
    }
    kupyna512_update(&ctx, zero, 0);
    kupyna512_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 64));

    kupyna512_init(&ctx);
    for (int i=0; i<1048576; i+=2) {
        kupyna512_update(&ctx, zero + i, 2);
    }
    kupyna512_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 64));

    kupyna512_init(&ctx);
    for (int i=0; i<1048576; i+=4) {
        kupyna512_update(&ctx, zero + i, 4);
    }
    kupyna512_final(&ctx, r1);
    CU_ASSERT(!memcmp(result, r1, 64));
}

static void kupyna512_512()
{
    static const uint8_t expected[512/8] = {
        0x38, 0x13, 0xE2, 0x10, 0x91, 0x18, 0xCD, 0xFB, 0x5A, 0x6D, 0x5E, 0x72, 0xF7, 0x20, 0x8D, 0xCC,
        0xC8, 0x0A, 0x2D, 0xFB, 0x3A, 0xFD, 0xFB, 0x02, 0xF4, 0x69, 0x92, 0xB5, 0xED, 0xBE, 0x53, 0x6B,
        0x35, 0x60, 0xDD, 0x1D, 0x7E, 0x29, 0xC6, 0xF5, 0x39, 0x78, 0xAF, 0x58, 0xB4, 0x44, 0xE3, 0x7B,
        0xA6, 0x85, 0xC0, 0xDD, 0x91, 0x05, 0x33, 0xBA, 0x5D, 0x78, 0xEF, 0xFF, 0xC1, 0x3D, 0xE6, 0x2A
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 512 / 8);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna512_1024()
{
    static const uint8_t expected[512/8] = {
        0x76, 0xED, 0x1A, 0xC2, 0x8B, 0x1D, 0x01, 0x43, 0x01, 0x3F, 0xFA, 0x87, 0x21, 0x3B, 0x40, 0x90,
        0xB3, 0x56, 0x44, 0x12, 0x63, 0xC1, 0x3E, 0x03, 0xFA, 0x06, 0x0A, 0x8C, 0xAD, 0xA3, 0x2B, 0x97,
        0x96, 0x35, 0x65, 0x7F, 0x25, 0x6B, 0x15, 0xD5, 0xFC, 0xA4, 0xA1, 0x74, 0xDE, 0x02, 0x9F, 0x0B,
        0x1B, 0x43, 0x87, 0xC8, 0x78, 0xFC, 0xC1, 0xC0, 0x0E, 0x87, 0x05, 0xD7, 0x83, 0xFD, 0x7F, 0xFE
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 1024 / 8);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna512_2048()
{
    static const uint8_t expected[512/8] = {
        0x0D, 0xD0, 0x3D, 0x73, 0x50, 0xC4, 0x09, 0xCB, 0x3C, 0x29, 0xC2, 0x58, 0x93, 0xA0, 0x72, 0x4F,
        0x6B, 0x13, 0x3F, 0xA8, 0xB9, 0xEB, 0x90, 0xA6, 0x4D, 0x1A, 0x8F, 0xA9, 0x3B, 0x56, 0x55, 0x66,
        0x11, 0xEB, 0x18, 0x7D, 0x71, 0x5A, 0x95, 0x6B, 0x10, 0x7E, 0x3B, 0xFC, 0x76, 0x48, 0x22, 0x98,
        0x13, 0x3A, 0x9C, 0xE8, 0xCB, 0xC0, 0xBD, 0x5E, 0x14, 0x36, 0xA5, 0xB1, 0x97, 0x28, 0x4F, 0x7E
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 2048 / 8);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna512_8()
{
    static const uint8_t expected[512/8] = {
        0x87, 0x1B, 0x18, 0xCF, 0x75, 0x4B, 0x72, 0x74, 0x03, 0x07, 0xA9, 0x7B, 0x44, 0x9A, 0xBE, 0xB3,
        0x2B, 0x64, 0x44, 0x4C, 0xC0, 0xD5, 0xA4, 0xD6, 0x58, 0x30, 0xAE, 0x54, 0x56, 0x83, 0x7A, 0x72,
        0xD8, 0x45, 0x8F, 0x12, 0xC8, 0xF0, 0x6C, 0x98, 0xC6, 0x16, 0xAB, 0xE1, 0x18, 0x97, 0xF8, 0x62,
        0x63, 0xB5, 0xCB, 0x77, 0xC4, 0x20, 0xFB, 0x37, 0x53, 0x74, 0xBE, 0xC5, 0x2B, 0x6D, 0x02, 0x92
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test_8, 8 / 8);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna512_1536()
{
    static const uint8_t expected[512/8] = {
        0xB1, 0x89, 0xBF, 0xE9, 0x87, 0xF6, 0x82, 0xF5, 0xF1, 0x67, 0xF0, 0xD7, 0xFA, 0x56, 0x53, 0x30,
        0xE1, 0x26, 0xB6, 0xE5, 0x92, 0xB1, 0xC5, 0x5D, 0x44, 0x29, 0x90, 0x64, 0xEF, 0x95, 0xB1, 0xA5,
        0x7F, 0x3C, 0x2D, 0x0E, 0xCF, 0x17, 0x86, 0x9D, 0x1D, 0x19, 0x9E, 0xBB, 0xD0, 0x2E, 0x88, 0x57,
        0xFB, 0x8A, 0xDD, 0x67, 0xA8, 0xC3, 0x1F, 0x56, 0xCD, 0x82, 0xC0, 0x16, 0xCF, 0x74, 0x31, 0x21
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 1536 / 8);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna512_0()
{
    static const uint8_t expected[512/8] = {
        0x65, 0x6B, 0x2F, 0x4C, 0xD7, 0x14, 0x62, 0x38, 0x8B, 0x64, 0xA3, 0x70, 0x43, 0xEA, 0x55, 0xDB,
        0xE4, 0x45, 0xD4, 0x52, 0xAE, 0xCD, 0x46, 0xC3, 0x29, 0x83, 0x43, 0x31, 0x4E, 0xF0, 0x40, 0x19,
        0xBC, 0xFA, 0x3F, 0x04, 0x26, 0x5A, 0x98, 0x57, 0xF9, 0x1B, 0xE9, 0x1F, 0xCE, 0x19, 0x70, 0x96,
        0x18, 0x7C, 0xED, 0xA7, 0x8C, 0x9C, 0x1C, 0x02, 0x1C, 0x29, 0x4A, 0x06, 0x89, 0x19, 0x85, 0x38
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 0);
    kupyna512_final(&ctx, result);

    CU_ASSERT(!memcmp(result, expected, 64));
}

static void kupyna304_1024()
{
    static const uint8_t expected[304/8] = {
        0x0A, 0x8C, 0xAD, 0xA3, 0x2B, 0x97, 0x96, 0x35, 0x65, 0x7F, 0x25, 0x6B, 0x15, 0xD5, 0xFC, 0xA4,
        0xA1, 0x74, 0xDE, 0x02, 0x9F, 0x0B, 0x1B, 0x43, 0x87, 0xC8, 0x78, 0xFC, 0xC1, 0xC0, 0x0E, 0x87,
        0x05, 0xD7, 0x83, 0xFD, 0x7F, 0xFE
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 1024 / 8);
    kupyna512_final2(&ctx, result, 304);

    CU_ASSERT(!memcmp(result, expected, 38));
}

static void kupyna384_760()
{
    static const uint8_t expected[384/8] = {
        0xD9, 0x02, 0x16, 0x92, 0xD8, 0x4E, 0x51, 0x75, 0x73, 0x56, 0x54, 0x84, 0x6B, 0xA7, 0x51, 0xE6,
        0xD0, 0xED, 0x0F, 0xAC, 0x36, 0xDF, 0xBC, 0x08, 0x41, 0x28, 0x7D, 0xCB, 0x0B, 0x55, 0x84, 0xC7,
        0x50, 0x16, 0xC3, 0xDE, 0xCC, 0x2A, 0x6E, 0x47, 0xC5, 0x0B, 0x2F, 0x38, 0x11, 0xE3, 0x51, 0xB8
    };

    struct kupyna512_ctx_t ctx;
    kupyna512_init(&ctx);
    kupyna512_update(&ctx, test, 760 / 8);
    kupyna512_final2(&ctx, result, 384);

    CU_ASSERT(!memcmp(result, expected, 48));
}

int main(int argc, char** argv)
{
    CU_initialize_registry();

    CU_pSuite suite_k256 = CU_add_suite("Kupyna-256", NULL, NULL);
    CU_ADD_TEST(suite_k256, kupyna256_chunk);
    CU_ADD_TEST(suite_k256, kupyna256_512);
    CU_ADD_TEST(suite_k256, kupyna256_1024);
    CU_ADD_TEST(suite_k256, kupyna256_2048);
    CU_ADD_TEST(suite_k256, kupyna256_8);
    CU_ADD_TEST(suite_k256, kupyna256_760);
    CU_ADD_TEST(suite_k256, kupyna256_0);

    CU_pSuite suite_k48 = CU_add_suite("Kupyna-48", NULL, NULL);
    CU_ADD_TEST(suite_k48, kupyna48_512);

    CU_pSuite suite_k512 = CU_add_suite("Kupyna-512", NULL, NULL);
    CU_ADD_TEST(suite_k512, kupyna512_chunk);
    CU_ADD_TEST(suite_k512, kupyna512_512);
    CU_ADD_TEST(suite_k512, kupyna512_1024);
    CU_ADD_TEST(suite_k512, kupyna512_2048);
    CU_ADD_TEST(suite_k512, kupyna512_8);
    CU_ADD_TEST(suite_k512, kupyna512_1536);
    CU_ADD_TEST(suite_k512, kupyna512_0);

    CU_pSuite suite_k304 = CU_add_suite("Kupyna-304", NULL, NULL);
    CU_ADD_TEST(suite_k304, kupyna304_1024);

    CU_pSuite suite_k384 = CU_add_suite("Kupyna-384", NULL, NULL);
    CU_ADD_TEST(suite_k384, kupyna384_760);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();
    return CU_get_number_of_tests_failed() ? EXIT_FAILURE : EXIT_SUCCESS;
}
