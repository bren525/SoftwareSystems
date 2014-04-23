#include <stdio.h>
#include <string.h>

int main(){
	char a[] = "hello";
	printf("%lu",strlen(a));
}

char* interleave(char* a, char* b){
	int len = strlen(a)+strlen(b);
	char result[];
	result = malloc(len*sizeof(char) + 1);
	flag = 0;
	int i;
	for(i = 0; i < strlen(a) && i < strlen(b); i++){

		if(b[i]!="\0" && a[i] != "\0"){
			result[i*2]= a[i];
			result[(i*2)+1] = b[i];
		}else{
			if(a[i]=="\0"){
				flag = 0;
			}else{
				flag = 1;
			}
		}
	}
	for(j = i; j< len; j++){
		if(flag){
			result[i*2+j] = b[j];
		}else{
			result[i*2+j] = a[j];
		}
	}



}