#include <stdio.h>
#include <stdint.h>

uint16_t assemble(uint8_t most, uint8_t least){
	uint16_t res = most;
	res<<= 8;
	res += least;
	return res;
}

int main(){
	printf("%i\n",assemble(1,2) );
}