#ifndef __MY_LIB_H__
#define __MY_LIB_H__

//General macros
#define ISDIGIT(c) ((unsigned char)c > '/' && (unsigned char)c < ':')
#define ISSPACE(c) ((unsigned char)c == ' ' || (unsigned char)c == '\t' || (unsigned char)c == '\n')

#define LONG_MAX 0x7fffffffffffffff

//Needed open flags
#define O_RDONLY             00
#define O_WRONLY             01
#define O_RDWR               02

//Type definitions
typedef unsigned long size_t;
typedef unsigned long long ssize_t;
typedef unsigned int mode_t;

int geterror();
//converters
long atol(char* str);
void ltoa(long num, char* outbuf);

//string.h stuff
void *memcpy(void *dest, const void *src, unsigned long n);
void *memset(void *s, int c, size_t n);
int puts(const char* s);
size_t strlen(const char* s);
char *strchr(const char* s, int c);

// Custom I/O stuff
long fdgets(int fd, char* buf, size_t size);
void print_num(long num);

//syscall
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
int open(const char *pathname, int flags, mode_t mode);

#endif