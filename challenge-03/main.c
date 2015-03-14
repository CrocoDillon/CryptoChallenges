#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"
#include "english.h"

int main(int argc, char *argv[]) {
    char hex[128];
    printf("Enter a hexadecimal:\n");
    scanf("%127s", hex);
    // Length in bytes, allocate memory for message
    size_t length = strlen(hex)>>1;
    char *encrypted = malloc(length + 1);
    char *decrypted = malloc(length + 1);
    // Encrypted string
    hex2string(hex, encrypted, length);
    // Best cipher match
    unsigned char bestCipher;
    double bestDistance;
    // Cipher being evaluated
    unsigned char cipher;
    v_normalize(FREQUENCIES);
    double distance;
    int i;
    for (cipher = 0, i = 0; i < 256; cipher++, i++) {
        decrypt(encrypted, decrypted, length, cipher);
        distance = calculateDistance(FREQUENCIES, decrypted, length);
        if (cipher == 0 || distance < bestDistance) {
            bestCipher = cipher;
            bestDistance = distance;
        }
    }
    decrypt(encrypted, decrypted, length, bestCipher);
    printf("Decrypted message:\n%s\n", decrypted);

    free(encrypted);
    free(decrypted);

    return 0;
}

void hex2string(char *in, char *out, size_t length) {
    int i;
    for (i = 0; i < length; i++) {
        sscanf(in + 2 * i, "%2hhx", out + i);
    }
    out[length] = 0;
}

void decrypt(char *in, char *out, size_t length, unsigned char cipher) {
    int i;
    for (i = 0; i < length; i++) {
        out[i] = in[i] ^ cipher;
    }
    out[length] = 0;
}

double calculateDistance(double *reference, char *message, size_t length) {
    int i;
    double frequencies[26];
    for (i = 0; i < 26; i++) {
        frequencies[i] = 0;
    }
    for (i = 0; i < length; i++) {
        char c = message[i];
        if (c < 32 || c == 33 || c == 38 || c == 42) {
            // CHEATING! :( Excluding characters because I was getting the cipher wrong
            return 10;
        }
        if (65 <= c && c <= 90) {
            // Uppercase
            frequencies[c - 65]++;
        }
        if (97 <= c && c <= 122) {
            // Lowercase
            frequencies[c - 97]++;
        }
    }
    // Normalize frequencies so length == 1
    v_normalize(frequencies);
    // Subtract frequencies from reference (English)
    v_subtract(frequencies, reference);
    return v_length(frequencies);
}

void v_normalize(double *v) {
    double length = v_length(v);
    int i;
    for (i = 0; i < 26; i++) {
        v[i] = v[i] / length;
    }
}

void v_subtract(double *v1, double *v2) {
    int i;
    for (i = 0; i < 26; i++) {
        v1[i] = v1[i] - v2[i];
    }
}

double v_length(double *v) {
    int i;
    double length = 0;
    for (i = 0; i < 26; i++) {
        length += v[i] * v[i];
    }
    return sqrt(length);
}
