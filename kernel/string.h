#ifndef STRING_H
#define STRING_H

int strlen(char *s);
int strcmp(char *s1, char *s2);
void strcpy(char *src, char *dest);
void append(char *s, char n);
void backspace(char *s);
void get_arg(char *input, int index, char *output);
void get_tail(char *input, int index, char *output);
void memcpy(char *source, char *dest, int nbytes);
void int_to_ascii(int n, char str[]);

#endif
