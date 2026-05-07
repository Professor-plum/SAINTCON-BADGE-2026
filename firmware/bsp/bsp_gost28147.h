#ifndef BSP_GOST28147_H
#define BSP_GOST28147_H

#include <stdint.h>
#include <stddef.h>

#define GOST_BLOCK_SIZE 8
#define GOST_KEY_SIZE 32
#define GOST_HASH_SIZE 32

// Set the key for GOST 28147 cipher
void gost28147_set_key(const uint8_t *key);

// Encrypt a 64-bit block in place
void gost28147_encrypt(uint8_t *block);

// Decrypt a 64-bit block in place
void gost28147_decrypt(uint8_t *block);

// Initialize GOST R 34.11-94 hash
void gost_hash_init(void);

// Update hash with data
void gost_hash_update(const uint8_t *data, size_t len);

// Finalize hash, output 32-byte hash
void gost_hash_final(uint8_t *hash);

// Convenience function to hash a null-terminated string
void gost_hash_string(const char *str, uint8_t *hash);

// Note: GOST 28147 is a block cipher. GOST R 34.11-94 is the hash function that uses it.

#endif // BSP_GOST28147_H