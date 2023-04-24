#include "my_lib.h"

extern unsigned long syscall(int syscall_number,...);

int __error;

//Sometimes we need to be able to check if the last function errored out specifically.
//As we can't do that with
int geterror(){
    int tmperror = __error;
    __error = 0;
    return tmperror;
}

//Converters
//ASCII to long
long atol(char* str){
    unsigned long output = 0;
    int i = 0;
    int neg = 0;
    while(ISSPACE(str[i])){
        i++;
    }
    if(str[i] == '-'){
        neg = 1;
        i++;
    }
    for(;ISDIGIT(str[i]);i++){
        output*=10;
        output+=str[i] - '0';
        if(output>LONG_MAX){
            __error=1;
            return -1;//We return -1. It's up to the user to check if we errored out
        }
    }
    if(neg){
        output = ~output+1;
    }
    return (long)output;
}

//Long to ascii
void ltoa(long num, char* outbuf){
    //Longest an unsigned long can be is 21 characters
    unsigned char converted[21];
    unsigned long numhandle = (unsigned long)num;
    int i;
    int neg = 0;

    if(numhandle > LONG_MAX){
        neg = 1;
        numhandle = ~numhandle+1;
    }

    //We start from the back and move up
    for(i = 20; i>-1; i--){
        unsigned char c = numhandle%10;
        converted[i] = c + '0';
        numhandle /= 10;
        if(numhandle == 0){
            break;
        }
    }
    if(neg){
        converted[--i] = '-';
    }
    memcpy(outbuf,&converted[i],21-i);
}

void print_num(long num){
    char result[21] = {0};
    int len;
    ltoa(num,result);
    len = strlen(result);
    write(1,result,len);
}

//string.h stuff
void *memcpy(void *dest, const void *src, unsigned long n){
    unsigned char* d = (unsigned char*)dest;
    unsigned char* s = (unsigned char*)src;

    for(;n>0;n--){
        d[n-1] = s[n-1];
    }
    return dest;
}

void *memset(void *s, int c, size_t n){
    unsigned char* ts = (unsigned char*)s;
    for(size_t i = n; i>0; i--){
        ts[i-1] = (unsigned char)c;
    }
    return s;
}

size_t strlen(const char* s){
    size_t i = 0;
    while(s[i++]!='\x00');
    return i-1;
}

int puts(const char* s){
    size_t len = strlen(s);
    int written = (int)write(1,s,len) +1;
    write(1,"\n",1);
    return written;
}

char *strchr(const char* s, int c){
    char tc = (char)c;
    char* ts = (char*)s;
    for(;*ts!=tc;ts++);
    return ts;

}

//custom helper functions

//fdgets. Like fgets but takes an fd instead of a FILE* 
long fdgets(int fd, char* outbuf, size_t size){
    char *tmpbuf = outbuf;
    long total_read_bytes = 0x0;
    for(size_t i = size; i>0; i--, tmpbuf++){
        int readBytes = read(fd,tmpbuf,1);
        if(readBytes!=1){
            return -1;
            break;
        }
        total_read_bytes++;
        if(i == 1){
            *tmpbuf = '\x00';
            break;
        }
        else if(*tmpbuf == '\n'){
            tmpbuf++;
            *tmpbuf = '\x00';
            break;
        }
    }
    return total_read_bytes;
}

//syscalls
ssize_t read(int fd, void *buf, size_t count){
    return (ssize_t)syscall(0,fd,buf,count);
}

ssize_t write(int fd, const void *buf, size_t count){
    return (ssize_t)syscall(1,fd,buf,count);
}

int open(const char *pathname, int flags, mode_t mode){
    return (int)syscall(2,pathname,flags,mode);
}