#ifndef CRY_H
#define CRY_H

#include "utils.h"
#include <oqs/kem.h>
#include <stdbool.h>

#ifndef OQS_KEM_alg_kyber_768
    die("KYBER768 is not defined - oqs/kem.h is missing?\n");
#endif

#ifndef OQS_KEM_alg_ntruprime_sntrup761
    die("SNTRUP761 is not defined - oqs/kem.h is missing?\n");
#endif

/*
 * Creates KEM context for chosen alg
 * 
 * IN:
 *  chosen algorithm
 */
OQS_KEM *create_kem_context(int choice);

typedef void (*fileio_fnt)(int, bool, uint8_t*, size_t, char*);
typedef void (*kp_fnt)(int, bool, uint8_t*);

// to wrap the below io funcs
void wrap_io_context(int choice, bool is_priv, uint8_t *key, size_t keylen, char*key_filename, fileio_fnt fio);

// to wrap keypair fn
void wrap_kp_context(int choice, bool is_priv, uint8_t *key, kp_fnt fkp);

/*
 * Reads key from FILE
 *
 * IN:
 *  algorithm choice
 *  bool is priv
 *  buffer that will hold key
 *  sizeof key
 *  filename of key
 */
void read_key(int choice, bool is_priv, uint8_t *key, size_t keylen, char *key_filename);

/*
 * Writes key to FILE
 * 
 * IN:
 *  algorithm choice
 *  bool is priv
 *  buffer that will hold key
 *  sizeof key
 *  filename of key
 */
void write_key(int choice, bool is_priv, uint8_t *key, size_t keylen, char *key_fname);

/*
 * Generate a key pair
 *
 * IN:
 *  algorithm choice
 *  name of keypair
 */
void generate_keypair(int algo, bool is_priv, char *keyname);

#endif