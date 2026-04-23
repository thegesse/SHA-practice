#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basic_hashing.h"

size_t to_raw_bytes(const char *text, Chunk512 **out_chunks) {
    size_t len = strlen(text);

    size_t num_chunks = (len + 1 + 8 + 63) / 64;

    *out_chunks = (Chunk512 *)calloc(num_chunks, sizeof(Chunk512));
    if (!*out_chunks) return 0;

    uint8_t *raw_ptr = (uint8_t *)(*out_chunks);

    if (len > 0) {
        memcpy(raw_ptr, text, len);
    }

    raw_ptr[len] = 0x80;

    uint64_t bit_len = (uint64_t)len * 8;
    size_t total_bytes = num_chunks * 64;

    for (int i = 0; i < 8; i++) {
        raw_ptr[total_bytes - 1 - i] = (uint8_t)(bit_len >> (i * 8));
    }

    return num_chunks;
}

//helper for bit rotation
static uint32_t rotr(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (32 - n));
}

void to_bit_chunk(const Chunk512 *chunk, uint32_t words[16]) {
    for (int i = 0; i < 16; i++) {
        words[i] = ((uint32_t)chunk->data[i * 4] << 24) |
                   ((uint32_t)chunk->data[i * 4 + 1] << 16) |
                   ((uint32_t)chunk->data[i * 4 + 2] << 8) |
                   ((uint32_t)chunk->data[i * 4 + 3]);
    }
}

void hash(const Chunk512 *chunks, size_t chunk_count, uint32_t output[8]) {
    // 1. init output
    output[0] = 0x6a09e667; output[1] = 0xbb67ae85;
    output[2] = 0x3c6ef372; output[3] = 0xa54ff53a;
    output[4] = 0x510e527f; output[5] = 0x9b05688c;
    output[6] = 0x1f83d9ab; output[7] = 0x5be0cd19;

    for (size_t c = 0; c < chunk_count; c++) {
        uint32_t w[64];
        uint32_t a, b, c_reg, d, e, f, g, h; // avoid loop counter conflict

        // Fill all
        to_bit_chunk(&chunks[c], w);

        // Extend to 64
        for (int i = 16; i < 64; i++) {
            uint32_t s0 = rotr(w[i-15], 7) ^ rotr(w[i-15], 18) ^ (w[i-15] >> 3);
            uint32_t s1 = rotr(w[i-2], 17) ^ rotr(w[i-2], 19) ^ (w[i-2] >> 10);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }

        a = output[0]; b = output[1]; c_reg = output[2]; d = output[3];
        e = output[4]; f = output[5]; g = output[6]; h = output[7];

        // compression
        for (int i = 0; i < 64; i++) {
            uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
            uint32_t ch = (e & f) ^ ((~e) & g);
            uint32_t temp1 = h + S1 + ch + K[i] + w[i];

            uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
            uint32_t maj = (a & b) ^ (a & c_reg) ^ (b & c_reg);
            uint32_t temp2 = S0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c_reg;
            c_reg = b;
            b = a;
            a = temp1 + temp2;
        }
        //results
        output[0] += a; output[1] += b; output[2] += c_reg; output[3] += d;
        output[4] += e; output[5] += f; output[6] += g; output[7] += h;
    }
}