#include <stdio.h>
#include "findsubstr.h"
#include "readline.h"

int main(int argc, char *argv[])
{
    char* filename = argv[1];
    char* substr = argv[2];
    size_t max_len = 100;
    char* line = (char*) malloc(max_len);
    stdin = fopen(filename, "r");
    
    while(read_line(line) != -1)
    {
        if (find_sub_string(line, substr) != -1)
            printf("%s\n", line);
    }

    free(line);
    fclose(stdin);
    return 0;
}
