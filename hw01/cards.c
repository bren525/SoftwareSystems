#include <stdio.h>
#include <stdlib.h>
int get_val(char *card_name);
int updated_count(int count, int val);
/* Main funtion
	Contains the main loop which continuously 
	prompts user for each card name

	count: running card count
	card_name: buffer where user input is stored
*/
int main()
{
	char card_name[3];
	int count = 0;
	int val;
	while (card_name[0]!='X') {
		puts("Enter the card_name: ");
		scanf("%2s", card_name);
		if(card_name[0]=='X'){break;}
		val = get_val(card_name);
		if(val!=0){
			count = updated_count(count,val);
			printf("Current count: %i\n", count);
		}
		
	}
	return 0;
}
/* Determines and returns the value of a given card
	val: value of numeric cards,
		 returned if within correct range 
*/
int get_val(char *card_name){
	int val;
	switch(card_name[0]) {
		case 'K':
		case 'Q':
		case 'J':
			return 10;
		case 'A':
			return 11;
		default:
			val = atoi(card_name);
			if((val < 2)||(val>10)){
				puts("I don't understand that value!");
				return 0;
			}else{
				return val;
			}
			
	}
}
/* Updates the count based on the value of the new card
	count: the current card count
	val: the new cards value
	contains the rules for updating the count
*/
int updated_count(int count, int val){
	if ((val > 1) && (val < 7)) {
		return count + 1;
	} else if (val == 10) {
		return count - 1;
	}
	return count;
}


/*
int main()
{
	char card_name[3];
	int count = 0;
	while (card_name[0]!='x') {
	puts("Enter the card_name: ");
	scanf("%2s", card_name);
	int val = 0;
	switch(card_name[0]) {
	case 'K':
	case 'Q':
	case 'J':
	val = 10;
	break;
	case 'A':
	val = 11;
	break;
	case 'X':
		continue;
	default:
	val = atoi(card_name);
	if((val < 2)||(val>10)){
		puts("I don't understand that value!");
		continue;
	}
}
if ((val > 1) && (val < 7)) {
	count++;
} else if (val == 10) {
	count--;
}
printf("Current count: %i\n", count);
}
	return 0;
}
*/