#include <stdio.h>
#include "findsubstr.h"

// Function to find the string sub inside string str
// Returns first index in str if found, else -1
int find_sub_string(const char *str, const char *sub)
{
    //Slide through the characters in str one-by-one
    // try to match the first character in substr
    for(int i = 0; str[i] != '\0'; i++)
    {
        if(str[i] == sub[0])
        {
            int found = 1;
            //Check for the substr match from the current position in str
            for(int j = 1; sub[j] != '\0' ; j++)
            {
                //If length of remaining string in str < length of substr
                // then no need to slide further through str
                if (str[i+j] == '\0')
                    return -1;

                if (str[i+j] != sub[j])
                {
                    found = 0;
                    break;
                }
            }                
            if (found)
                return i;
        }
    }
    return -1;
}

