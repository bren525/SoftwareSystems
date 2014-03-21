/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *tracks[] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

/* Returns a heap-allocated string that contains the strings 
   from the given array, joined up with no spaces between.
*/
char *strjoin(char *array[], int n)
{
    int i;
    /*int len = 0;
    for(i = 0;i < n; i++){
        len += strlen(array[i]) + 1;
    }
    char *s = malloc(len*sizeof(char));
    */
    char *s = malloc(0);
    //no null space addition needed because last space not needed
    strcpy(s,array[0]);
    strcat(s," ");

    for(i = 1; i < n; i++){
        strcat(s,array[i]);
        strcat(s," ");
    }

    return s;
}


int main (int argc, char *argv[])
{
    char *s = strjoin(tracks, 5);
    printf("%s\n", s);
    return 0;
}
