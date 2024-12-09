#include "utils.h"
#include "cryptography.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <oqs/kem.h>

const char *kems[] = {
    OQS_KEM_alg_kyber_768,
    OQS_KEM_alg_ntruprime_sntrup761,
    NULL
};

const int ciphertext_lens[] = {
    OQS_KEM_kyber_1024_length_ciphertext,
    OQS_KEM_ntruprime_sntrup761_length_ciphertext,
};

const int pubkey_lens[] = {
    OQS_KEM_kyber_1024_length_public_key,
    OQS_KEM_ntruprime_sntrup761_length_public_key
};

const int secretkey_lens[] = {
    OQS_KEM_kyber_1024_length_secret_key,
    OQS_KEM_ntruprime_sntrup761_length_secret_key
};

const int sharedsecret_lens[] = {
    OQS_KEM_kyber_1024_length_shared_secret,
    OQS_KEM_ntruprime_sntrup761_length_shared_secret
};

/*
void print_algorithms() {
    for (int i = 0; kems[i]; i++) {
        printf("Algorithm #%d: %s\n", i, kems[i]);
    }
}
*/

int count_algorithms() {
    int i;
    for (i = 0; kems[i]; i++);
    return i;
}

OQS_KEM *create_kem_context(int choice) {
    OQS_KEM *kem = OQS_KEM_new(kems[choice]);
    if (kem == NULL)
        die("create_kem_context OQS_KEM_new()\n");
    return kem;
}

void wrap_io_context(bool is_priv, uint8_t *key, size_t keylen, char*key_filename, fileio_fnt fio) {
    OQS_init();
    fio(is_priv, key, keylen, key_filename);
    OQS_destroy();
}

Keypair *wrap_kp_context(int choice, char *keyname, kp_fnt fkp) {
    OQS_init();
    Keypair *r = fkp(choice, keyname);
    OQS_destroy();
    return r;
}

void read_key(bool is_priv, uint8_t *key, size_t keylen, char *key_filename) {
    char tmpbuf[128];
    snprintf(tmpbuf, 128, "%s%s", key_filename, is_priv ? ".priv" : ".pub");
    read_from_file(tmpbuf, key, keylen);
    log("read_key (%s) - read %d bytes\n", is_priv ? "secret" : "public", (int)keylen);
}

void write_key(bool is_priv, uint8_t *key, size_t keylen, char *key_fname) {
    char tmpbuf[128];
    snprintf(tmpbuf, 128, "%s%s", key_fname, is_priv ? ".priv" : ".pub");
    write_to_file(tmpbuf, key, keylen);
    log("write_key (%s) - wrote %d bytes\n", is_priv ? "secret" : "public", (int)keylen);
}

void free_keypair(Keypair *keypair) {
	free(keypair->pubkey);
	free(keypair->seckey);
	free(keypair);
}

Keypair *generate_keypair(int algo, char *keyname) {
    OQS_KEM *kem = create_kem_context(algo);
    // size_t klen = is_priv ? secretkey_lens[algo] : pubkey_lens[algo];
    uint8_t pubkey[kem->length_public_key];
    uint8_t seckey[kem->length_secret_key];

    if(OQS_KEM_keypair(kem, pubkey, seckey) != OQS_SUCCESS)
        die("generate_keypair OQS_KEM_keypair\n");

    //char fname[128];
    //snprintf(fname, 128, "%s.pub", keyname);
    //write_key(algo, is_priv, pubkey, kem->length_public_key, fname);
    //snprintf(fname, 128, "%s.priv", keyname);
    //write_key(algo, is_priv, seckey, kem->length_secret_key, fname);

    Keypair *result = (Keypair*) malloc(sizeof(Keypair));
    result->pubkey_length = kem->length_public_key;
    result->pubkey = (uint8_t*) malloc(sizeof(uint8_t) * result->pubkey_length);
	snprintf((char*)result->pubkey, result->pubkey_length, "%s", pubkey);

    result->seckey_length = kem->length_secret_key;
    result->seckey = (uint8_t*) malloc(sizeof(uint8_t) * result->seckey_length);
	snprintf((char*)result->seckey, result->seckey_length, "%s", seckey);
    
    free(kem);
    log("generated keypair called '%s'\n", keyname);
	return result;
}
