#include "bsp_gost28147.h"
#include <string.h>

static uint32_t subkeys[8];

static const uint8_t sbox[8][16] = {
    {4,10,9,2,13,8,0,14,6,11,1,12,7,15,5,3},
    {14,11,4,12,6,13,15,10,2,3,8,1,0,7,5,9},
    {5,8,1,13,10,3,4,2,14,15,12,7,6,0,9,11},
    {7,13,10,1,0,8,9,15,14,4,6,12,11,2,5,3},
    {6,12,7,1,5,15,13,8,4,10,9,14,0,3,11,2},
    {4,11,10,0,7,2,1,13,3,6,8,5,9,12,15,14},
    {13,11,4,1,3,15,5,9,0,10,14,7,6,8,2,12},
    {1,15,13,0,5,7,10,4,9,2,3,14,6,11,8,12}
};

static const int key_order_encrypt[32] = {0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0};
static const int key_order_decrypt[32] = {7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7,7,6,5,4,3,2,1,0,0,1,2,3,4,5,6,7};

void gost28147_set_key(const uint8_t *key) {
    for(int i = 0; i < 8; i++) {
        subkeys[i] = ((uint32_t)key[i*4 + 3] << 24) | ((uint32_t)key[i*4 + 2] << 16) | ((uint32_t)key[i*4 + 1] << 8) | key[i*4];
    }
}

static uint32_t gost_f(uint32_t x, uint32_t k) {
    uint32_t sum = (x + k) & 0xFFFFFFFF;
    uint32_t out = 0;
    for(int i = 0; i < 8; i++) {
        uint8_t nibble = (sum >> (i * 4)) & 0xF;
        out |= ((uint32_t)sbox[i][nibble]) << (i * 4);
    }
    // Rotate left by 11 bits
    out = (out << 11) | (out >> 21);
    return out;
}

static void gost_process(uint8_t *block, const int *key_order) {
    uint32_t N1 = ((uint32_t)block[3] << 24) | ((uint32_t)block[2] << 16) | ((uint32_t)block[1] << 8) | block[0];
    uint32_t N2 = ((uint32_t)block[7] << 24) | ((uint32_t)block[6] << 16) | ((uint32_t)block[5] << 8) | block[4];
    for(int i = 0; i < 32; i++) {
        uint32_t temp = gost_f(N1, subkeys[key_order[i]]);
        temp ^= N2;
        N2 = N1;
        N1 = temp;
    }
    // Output
    block[0] = N1 & 0xFF;
    block[1] = (N1 >> 8) & 0xFF;
    block[2] = (N1 >> 16) & 0xFF;
    block[3] = (N1 >> 24) & 0xFF;
    block[4] = N2 & 0xFF;
    block[5] = (N2 >> 8) & 0xFF;
    block[6] = (N2 >> 16) & 0xFF;
    block[7] = (N2 >> 24) & 0xFF;
}

void gost28147_encrypt(uint8_t *block) {
    gost_process(block, key_order_encrypt);
}

void gost28147_decrypt(uint8_t *block) {
    gost_process(block, key_order_decrypt);
}

static uint32_t hash_H[4];
static uint8_t hash_buffer[32];
static size_t hash_buffer_len;
static uint64_t hash_total_bits;

void gost_hash_init(void) {
    hash_H[0] = 0;
    hash_H[1] = 0;
    hash_H[2] = 0;
    hash_H[3] = 0;
    hash_buffer_len = 0;
    hash_total_bits = 0;
}

static void gost_compress(uint32_t *H, const uint32_t *M) {
    // Save current subkeys
    uint32_t saved_subkeys[8];
    memcpy(saved_subkeys, subkeys, sizeof(subkeys));

    // Set key to H
    uint8_t key_bytes[32];
    for(int i = 0; i < 4; i++) {
        key_bytes[i*4 + 3] = (H[i] >> 24) & 0xFF;
        key_bytes[i*4 + 2] = (H[i] >> 16) & 0xFF;
        key_bytes[i*4 + 1] = (H[i] >> 8) & 0xFF;
        key_bytes[i*4 + 0] = H[i] & 0xFF;
    }
    gost28147_set_key(key_bytes);

    // P function
    uint32_t S[4];
    S[0] = M[0];
    S[1] = M[1];
    S[2] = M[2];
    S[3] = M[3];
    for(int i = 0; i < 4; i++) {
        uint8_t block[8];
        block[0] = (S[0] >> 24) & 0xFF;
        block[1] = (S[0] >> 16) & 0xFF;
        block[2] = (S[0] >> 8) & 0xFF;
        block[3] = S[0] & 0xFF;
        block[4] = (S[1] >> 24) & 0xFF;
        block[5] = (S[1] >> 16) & 0xFF;
        block[6] = (S[1] >> 8) & 0xFF;
        block[7] = S[1] & 0xFF;
        gost28147_encrypt(block);
        S[0] = (block[0] << 24) | (block[1] << 16) | (block[2] << 8) | block[3];
        S[1] = (block[4] << 24) | (block[5] << 16) | (block[6] << 8) | block[7];
        // Shift S
        uint32_t temp = S[3];
        S[3] = S[2];
        S[2] = S[1];
        S[1] = S[0];
        S[0] = temp;
    }
    // H = H XOR S
    H[0] ^= S[0];
    H[1] ^= S[1];
    H[2] ^= S[2];
    H[3] ^= S[3];

    // Restore subkeys
    memcpy(subkeys, saved_subkeys, sizeof(subkeys));
}

void gost_hash_update(const uint8_t *data, size_t len) {
    hash_total_bits += (uint64_t)len * 8;
    size_t i = 0;
    while (i < len) {
        size_t to_copy = 32 - hash_buffer_len;
        if (to_copy > len - i) to_copy = len - i;
        memcpy(hash_buffer + hash_buffer_len, data + i, to_copy);
        hash_buffer_len += to_copy;
        i += to_copy;
        if (hash_buffer_len == 32) {
            uint32_t M[4];
            for(int j = 0; j < 4; j++) {
                M[j] = (hash_buffer[j*4 + 3] << 24) | (hash_buffer[j*4 + 2] << 16) | (hash_buffer[j*4 + 1] << 8) | hash_buffer[j*4];
            }
            gost_compress(hash_H, M);
            hash_buffer_len = 0;
        }
    }
}

void gost_hash_final(uint8_t *hash) {
    // Pad and process remaining buffer
    if (hash_buffer_len > 0) {
        memset(hash_buffer + hash_buffer_len, 0, 32 - hash_buffer_len);
        uint32_t M[4];
        for(int j = 0; j < 4; j++) {
            M[j] = (hash_buffer[j*4 + 3] << 24) | (hash_buffer[j*4 + 2] << 16) | (hash_buffer[j*4 + 1] << 8) | hash_buffer[j*4];
        }
        gost_compress(hash_H, M);
    }

    // Process length block
    uint8_t length_block[32] = {0};
    uint64_t bits = hash_total_bits;
    length_block[24] = (bits >> 56) & 0xFF;
    length_block[25] = (bits >> 48) & 0xFF;
    length_block[26] = (bits >> 40) & 0xFF;
    length_block[27] = (bits >> 32) & 0xFF;
    length_block[28] = (bits >> 24) & 0xFF;
    length_block[29] = (bits >> 16) & 0xFF;
    length_block[30] = (bits >> 8) & 0xFF;
    length_block[31] = bits & 0xFF;

    uint32_t M[4];
    for(int j = 0; j < 4; j++) {
        M[j] = (length_block[j*4 + 3] << 24) | (length_block[j*4 + 2] << 16) | (length_block[j*4 + 1] << 8) | length_block[j*4];
    }
    gost_compress(hash_H, M);

    // Output hash in big-endian
    for(int j = 0; j < 4; j++) {
        hash[j*4 + 0] = (hash_H[j] >> 24) & 0xFF;
        hash[j*4 + 1] = (hash_H[j] >> 16) & 0xFF;
        hash[j*4 + 2] = (hash_H[j] >> 8) & 0xFF;
        hash[j*4 + 3] = hash_H[j] & 0xFF;
    }
}

void gost_hash_string(const char *str, uint8_t *hash) {
    gost_hash_init();
    gost_hash_update((const uint8_t *)str, strlen(str));
    gost_hash_final(hash);
}