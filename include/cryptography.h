#ifndef CRY_H
#define CRY_H

#include "utils.h"
#include <oqs/kem.h>

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

/*
 * Reads key from FILE
 *
 * IN:
 *  algorithm choice
 *  buffer that will hold pubkey
 *  filename of pubkey
 */
void read_key(int choice, char *pubkey, char *pubkey_filename);

#endif