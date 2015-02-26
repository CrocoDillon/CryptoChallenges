#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"

int main() {
    char hex[128];
    printf("Enter a hexidecimal:\n");
    scanf("%127s", hex);
    unsigned char * binary = hex2binary(hex);
    char * base64 = binary2base64(binary, strlen(hex)>>1);
    printf("%s\n", base64);
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

char * binary2base64(unsigned char * binary, int length) {
    int i = 0;
    int padding = length % 3;
    if (padding) {
        padding = 3 - padding;
    }
    int base64length = (length + padding) * 4 / 3;
    char * base64 = malloc(base64length);
    while (i < base64length) {
        base64[i++] = base64index(*binary>>2);
        if (i + 3 < base64length || !padding) {
            base64[i++] = base64index((*binary<<4 | *(++binary)>>4) & 63);
            base64[i++] = base64index((*binary<<2 | *(++binary)>>6) & 63);
            base64[i++] = base64index(*binary & 63);
        } else { // Last octet and padding of...
            if (padding == 1) { // ... 1.
                base64[i++] = base64index((*binary<<4 | *(++binary)>>4) & 63);
                base64[i++] = base64index(*binary<<2 & 63);
            } else { // ... 2.
                base64[i++] = base64index(*binary<<4 & 63);
                base64[i++] = '=';
            }
            base64[i++] = '=';
        }
        binary++;
    }
    return base64;
}

char base64index(unsigned char index) {
    if (index < 26) { // [A-Z] start at 65.
        return index + 65;
    } else if (index < 52) { // [a-z] start at 97.
        return index + 71;
    } else if (index < 62) { // [0-9] start at 48.
        return index - 4;
    } else if (index == 62) { // '+'.
        return '+';
    } else if (index == 63) { // '/'
        return '/';
    } else {
        return '?'; // Shouldn't be possible.
    }
}
