#include <stdlib.h>
#include <stdio.h>
static int a[10]={0,1,2,3,4,5,6,7,8,9};
void printa (int* a);
int main(){
	a[11] = 5;
	printa(a);

	int b[10] = {0,1,2,3,4,5,6,7,8,9};
	b[11] = 5;
	printa(b);

	int *c = malloc(10*sizeof(int));
	c[11] = 5;
	printa(c);
}

void printa(int * a){
	int i;
	for(i=0;i<15;i++){
		printf("%i\n",a[i]);
	}
}