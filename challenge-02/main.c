#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main() {
    char hexA[128];
    char hexB[128];
    printf("Enter a hexadecimal:\n");
    scanf("%127s", hexA);
    printf("Enter another hexadecimal:\n");
    scanf("%127s", hexB);
    int bytes = strlen(hexA)>>1;
    unsigned char * binaryA = hex2binary(hexA);
    unsigned char * binaryB = hex2binary(hexB);
    printf("XOR Result:\n");
    unsigned char * xor = malloc(bytes);
    int i;
    for (i = 0; i < bytes; i++) {
        xor[i] = binaryA[i] ^ binaryB[i];
        printf("%02X", xor[i]);
    }
    printf("\n");

    return 0;
}

unsigned char * hex2binary(char * hex) {
    int i;
    int bytes = strlen(hex)>>1;
    unsigned char * buffer = malloc(bytes);
    for (i = 0; i < bytes; i++) {
        sscanf(hex + 2 * i, "%2hhx", buffer + i);
    }
    return buffer;
}
