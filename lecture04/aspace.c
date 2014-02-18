/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int local = 5;
    void *p = malloc(128);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of local is %p\n", &local);
    printf ("Address of p is %p\n", p);

    int new_local = 6;
    printf ("Address of new_local is %p\n", &new_local);

    void *q = malloc(5);
    printf ("Address of q is %p\n", q);
    void *r = malloc(5);
    printf ("Address of r is %p\n", r);
    
    return 0;
}
