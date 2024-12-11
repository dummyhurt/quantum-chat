#include "cryptography.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    if (argc < 3) {
        print_algorithms(kems);
        die("usage: %s <keyname> <algorithm index>\n", argv[0]);
    }
	
    int choice;
    if (strlen(argv[1]) > 122) die("keyname maxlen = 122\n");
    if ((choice = atoi(argv[2])) >= count_algorithms()) die("invalid index\n");

    char *keyname = argv[1];
    // int choice = atoi(argv[2]);
	
    Keypair *kp = wrap_kp_context(choice, keyname, generate_keypair);

    save_keypair(kp, keyname);   
 
    free_keypair(kp);
    
    return 0;
}
