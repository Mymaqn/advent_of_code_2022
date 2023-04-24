#include "my_lib.h"


//Used for sanity checking input to get_tokens
#define IS_O(c)     (c >'@' && c < 'D')
#define IS_P(c)     (c > 'W' && c < '[')

//Used for getting the absolute value
#define ABS(v)      (v > 0 || v<0 ? v * ((v>0) - (v<0)) : 0)


//Checks for whether something is a win loss or a draw
#define ISDRAW(p,o) (o == p ? 3 : 0)
#define ISWIN(p,o)  (ABS(p-o)%3 == 1 ? 6 : 0)

int is_win(char o, char p){
    return ((o-p)%3) == 1;
}

int get_tokens(char* line, char* o, char* p){
    //Yeah we might go OOB but doesn't matter as we check whether input is valid
    if(!IS_O(line[0])){
        return -1;
    }
    if(!IS_P(line[2])){
        return -1;
    }
    *o = line[0] - 0x40;
    *p = line[2]- 0x57; //Normalize our input
    return 1;
}

int main(void){
    int input_fd;
    input_fd = open("./input",O_RDONLY,0x0);
    unsigned long score = 0; //We can never go negative, so this all good    
    while(1){
        int fd_ret = 0;
        char linebuf[256] = {0};
        char o;
        char p;

        fd_ret = fdgets(input_fd,linebuf,256);
        if(fd_ret == -1){
            break; //We're done in that case
        }
        
        int tok_success = get_tokens(linebuf,&o,&p);

        if(tok_success == -1){
            break; //Probably last line in that case
        }

        score+=p;
        score+=ISDRAW(p,o);
        score+=ISWIN(p,o);
    }

    print_num(score);
    puts("");
}