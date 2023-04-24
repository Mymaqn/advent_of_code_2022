#include "my_lib.h"

/*
Input is one string representing a number per line
We need something like an implementation itoa for this
*/

void print_num(long num){
    char result[21] = {0};
    int len;
    ltoa(num,result);
    len = strlen(result);
    write(1,result,len);
}
int main(void){
    unsigned long most_calories[3] = {0};
    unsigned long curr_calories = 0;
    unsigned int linenum = 0;
    char buf[256]; //Statically allocated buf. But a line of our input never exceeds this size
    int input_fd = open("./input",O_RDONLY,0x0);
    int fd_ret;

    while(1){
        //reset the buffer
        memset(buf,'\x00',256);

        //Read in a line
        fd_ret = fdgets(input_fd,buf,256);
        if(fd_ret == -1){
            break;
        }

        //Remove the newline
        char* newline = strchr(buf,'\n');
        *newline='\x00';
        int len = strlen(buf);
        
        //if the length is 0 we are done with the current elf
        if(len == 0){
            // Yeaaaah this is not good but that's what I'm going with. Otherwise I'll have to implement some kind of data structure
            if(curr_calories > most_calories[0]){
                most_calories[2] = most_calories[1];
                most_calories[1] = most_calories[0];
                most_calories[0] = curr_calories;
            }
            else if(curr_calories > most_calories[1] && curr_calories < most_calories[0]){
                most_calories[2] = most_calories[1];
                most_calories[1] = curr_calories;
            }
            else if(curr_calories > most_calories[2] && curr_calories < most_calories[1]){
                most_calories[2] = curr_calories;
            }
            curr_calories = 0;
            linenum++;
            continue;
        }

        //Otherwise we convert to a long and add it to current calories
        curr_calories += atol(buf);

        //Error handling in case conversion goes wrong
        int err = geterror();
        if(err){
            char linestr[21] = {0};
            puts("Error occured when reading line: ");
            ltoa(linenum,linestr);
            puts(linestr);
            return -1;
        }
        linenum++;
    }

    //lastly we print the results
    unsigned long total = 0;

    for(int i = 0; i<3; i++){
        total+=most_calories[i];
    }
    print_num(total);
    puts("");

}