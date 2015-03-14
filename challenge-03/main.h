#ifndef MAIN_H
#define MAIN_H

void hex2string(char *in, char *out, size_t length);
void decrypt(char *in, char *out, size_t length, unsigned char cipher);
double calculateDistance(double *reference, char *message, size_t length);
void v_normalize(double *v);
void v_subtract(double *v1, double *v2);
double v_length(double *v);

#endif
