/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() { //returns an array of size SIZE entirely filled with 17s
    int i;
    //int array[SIZE];
    int *array = malloc(SIZE*size(int));
    
    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = 17;
    }
    return array;
}

void bar() { //replaces foo array because the same memory is used
    int i;
    int array[SIZE];

    printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
	array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
	printf("%d\n", array[i]); //prints out whatever is at the address maybe neither foo nor bar
    }

    return 0;
}
