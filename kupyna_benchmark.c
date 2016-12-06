#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include "kupyna256.h"
#include "kupyna512.h"

#define BUFFER_MIB   100
#define BUFFER_SIZE  (1048576*BUFFER_MIB)

_Alignas(16) static uint8_t buf[BUFFER_SIZE];

int main(int argc, char** argv)
{
    struct kupyna256_ctx_t k256;
    struct kupyna512_ctx_t k512;
    clock_t t1;
    clock_t t2;
    uint8_t h[512/8];
    double duration;

    t1 = clock();
    kupyna256_init(&k256);
    kupyna256_update(&k256, buf, BUFFER_SIZE);
    kupyna256_final(&k256, h);
    t2 = clock();
    duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("kupyna256: %.3f sec, %.3f MBps\n", duration, BUFFER_MIB/duration);

    t1 = clock();
    kupyna256_init(&k256);
    kupyna256_update_aligned(&k256, buf, BUFFER_SIZE);
    kupyna256_final(&k256, h);
    t2 = clock();
    duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("kupyna256a: %.3f sec, %.3f MBps\n", duration, BUFFER_MIB/duration);

    t1 = clock();
    kupyna512_init(&k512);
    kupyna512_update(&k512, buf, BUFFER_SIZE);
    kupyna512_final(&k512, h);
    t2 = clock();
    duration = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("kupyna512: %.3f sec, %.3f MBps\n", duration, BUFFER_MIB/duration);

    return 0;
}
