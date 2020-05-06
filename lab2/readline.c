#include <stdio.h>
#include "readline.h"
#define MAX_LENGTH 100

// Function to read string from filestream stdin line-by-line (at most MAX_LENGTH-1 chars) 
// content will be stored in str
// Returns number of characters read, or -1 if reads eof or error
int read_line(char *str)
{
    if (ferror(stdin) || feof(stdin))
        return -1;

    if (!str)
        return -1;

    int len = 0;                          
    while (len < MAX_LENGTH-1)                 
    {                                     
        int char_read = fgetc(stdin);      

        if (char_read == EOF)              
            return -1;                    

        // end of line                    
        if (char_read == '\n')             
            break;                        

        str[len++] = char_read;

    }                                     
    str[len] = '\0'; //terminate the string
    return len;                           
}

