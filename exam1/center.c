/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Returns a heap-allocated string with length n, with
// the given string in the middle, surrounded by fillchar.
//
// For example, if s is allen, n is 10 and fillchar is .
// the result is ..allen... 

char *center(char *s, int n, char fillchar)
{
    char *ret = (char *) malloc (n*sizeof(char)+1);
    
    int len = strlen(s);
    int pad = (n - len)/2;
    
    int i = 0;
    while(i < pad){
        ret[i] = fillchar;
        i++;
    }
    char *dest = ret;
    dest += pad;
    strcpy(dest,s);
    i=pad + len;
    while(i < n){
        ret[i] = fillchar;
        i++;
    }
    ret[n]='\0';
    return ret;

}


int main (int argc, char *argv[])
{
    char *s = center("Software", 30, '.');
    printf("%s\n", s);

    char *s2 = center("Systems", 31, '-');
    printf("%s\n", s2);

    char *s3 = center("Spring 2014", 32, '*');
    printf("%s\n", s3);

    char *s4 = center("Exam 1", 33, '^');
    printf("%s\n", s4);

    return 0;
}
