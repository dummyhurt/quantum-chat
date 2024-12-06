#include "cryptography.h"
#include <stdlib.h>
#include <stdio.h>

const char *kems[] = {
    OQS_KEM_alg_kyber_768,
    OQS_KEM_alg_ntruprime_sntrup761
};

OQS_KEM *create_kem_context(int choice) {
    OQS_KEM *kem = OQS_KEM_new(kems[choice]);
    if (kem == NULL)
        die("create_kem_context OQS_KEM_new()\n");
    return kem;
}