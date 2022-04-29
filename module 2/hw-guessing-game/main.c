// Add your program here!\
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//include all the libraries we need to use in this game

int one_round();
void guessing_game();

void guessing_game() {
	int count = 0;
	int arr[5];
	int sum = 0;
	
	while(count < 5) {
		int guesscount = one_round();
		arr[count] = guesscount;
		count++;
	}	
	
	printf("=================================================\n");
	printf("|Here are the results of your guessing abilities|\n");
	printf("=================================================\n");
	
	for(int i = 0; i < count; i++) {	
		printf("Game %d took you %d guesses\n", i, arr[i]);
		sum += arr[i];
	}
	
	printf("On average it took you %d guesses until you guessed the correct number.\n", sum/5); 
}

int one_round() {
	int count = 0;
	int target = rand() % 20 + 1; //generate a random number between 1-20
	int guess = 0;
	
	printf("==========================\n");
	printf("CPU Says: Pick a number 1-20\n");
	printf("==========================\n");	
	
	while(count < 5) {
		printf("Make a guess:");
		scanf("%d", &guess);
		if(guess == target) {
			printf("You Got It!!\n");
			count++;
			break;
		} else if (guess > 20 || guess < 1) {
			printf("You guess should be between 1-20!\n");
			count++;
 		} else if (guess > target) {
			printf("Guess lower!\n");
			count++;	
		} else if (guess < target) {
			printf("Guess higher!\n");
			count++;
		}	
        }
	if (count == 5) {
		printf("You only have 5 chances to guess!\n");
	}
	return count;
}

int main() {
	guessing_game();
	return 0;
}	

