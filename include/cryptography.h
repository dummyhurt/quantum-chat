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

/* //////// externs \\\\\\\\ */

extern const char *kems[];
extern const int ciphertext_lens[];
extern const int pubkey_lens[];
extern const int secretkey_lens[];
extern const int sharedsecret_lens[];

/* //////// structures \\\\\\\\ */

/*
 * Structure that contains a keypair
 * 
 */
typedef struct keypair {
    OQS_KEM *kem;
    uint8_t *pubkey;
	size_t pubkey_length;
	uint8_t *seckey;
	size_t seckey_length;
} Keypair;

/* //////// funcs \\\\\\\\ */

/*
 * Return number of active algoritms
 */
int count_algorithms();

/*
 * Creates KEM context for chosen alg
 * 
 * IN:
 *  chosen algorithm
 */
OQS_KEM *create_kem_context(int choice);

typedef void (*fileio_fnt)(bool, uint8_t*, size_t, char*);
typedef Keypair* (*kp_fnt)(int, char*);

// to wrap the below io funcs
void wrap_io_context(bool is_priv, uint8_t *key, size_t keylen, char*key_filename, fileio_fnt fio);

// to wrap keypair fn
Keypair *wrap_kp_context(int choice, char *keyname, kp_fnt fkp);

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
void read_key(bool is_priv, uint8_t *key, size_t keylen, char *key_filename);

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
void write_key(bool is_priv, uint8_t *key, size_t keylen, char *key_filename);

/*
 * Writes keys to FILEs
 *
 * IN:
 *  keypair object
 *  key name
 */
void save_keypair(Keypair *kp, char *keyname);

/*
 * Free a dynamically allocated keypair
 *
 * IN:
 * 	Keypair to be freed
 */
void free_keypair(Keypair *keypair);

/*
 * Generate a key pair
 *
 * IN:
 *  algorithm choice
 *  name of keypair
 */
Keypair *generate_keypair(int algo, char *keyname);

#endif
