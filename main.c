#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256/basic_hashing.h"

void format_hash(uint32_t hash[8], char *out_str) {
    for (int i = 0; i < 8; i++) {
        sprintf(out_str + (i * 8), "%08x", hash[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(" <input_passwords.txt> <output_table.txt>\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    FILE *outfile = fopen(argv[2], "w");

    if (!infile || !outfile) {
        perror("failed");
        return 1;
    }

    char password[256];
    char hash_hex[65];
    uint32_t output[8];
    Chunk512 *chunks = NULL;


    while (fgets(password, sizeof(password), infile)) {
        password[strcspn(password, "\r\n")] = 0;
        if (strlen(password) == 0) continue;
        size_t count = to_raw_bytes(password, &chunks);

        if (count > 0) {
            hash(chunks, count, output);

            format_hash(output, hash_hex);
            fprintf(outfile, "%s:%s\n", password, hash_hex);

            free(chunks);
            chunks = NULL;
        }
    }

    fclose(infile);
    fclose(outfile);

    return 0;
}