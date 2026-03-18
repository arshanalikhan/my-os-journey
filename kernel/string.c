#include "string.h"

int strlen(char *s) { int i = 0; while (s[i] != 0) i++; return i; }

int strcmp(char *s1, char *s2) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void strcpy(char *src, char *dest) {
    int i = 0;
    while (src[i] != 0) { dest[i] = src[i]; i++; }
    dest[i] = '\0';
}

void append(char *s, char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char *s) {
    int len = strlen(s);
    if (len > 0) s[len-1] = '\0';
}

void get_arg(char *input, int index, char *output) {
    int word_count = 0, i = 0, j = 0;
    while (input[i] == ' ') i++;
    while (input[i] != '\0') {
        if (word_count == index) {
            while (input[i] != ' ' && input[i] != '\0') {
                output[j++] = input[i++];
            }
            output[j] = '\0';
            return;
        }
        while (input[i] != ' ' && input[i] != '\0') i++;
        while (input[i] == ' ') i++;
        word_count++;
    }
    output[0] = '\0';
}

void get_tail(char *input, int index, char *output) {
    int i = 0, word_count = 0;
    while (input[i] == ' ') i++;
    while (word_count < index) {
        if (input[i] == '\0') { output[0] = '\0'; return; }
        while (input[i] != ' ' && input[i] != '\0') i++;
        while (input[i] == ' ') i++;
        word_count++;
    }
    strcpy(&input[i], output);
}

void memcpy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) *(dest + i) = *(source + i);
}

// NEW: Convert Integer to String
void int_to_ascii(int n, char str[]) {
    int i = 0, sign;
    if ((sign = n) < 0) n = -n;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
    
    // Reverse it
    int j; char c;
    for (j = 0, i--; j < i; j++, i--) {
        c = str[j]; str[j] = str[i]; str[i] = c;
    }
}
