//Bethany Robinson
//Project 10
//5-5-2025

#include<stdio.h>

void loadMw(char word[]);
void lowerCase(char str[]);
void guessProcess(char guess[], char mystery[], char result[], char pointer[]); 
void print(char board[][6], char pointerB[][6], int count);
int equal(char *string1, char *string2);
int isVguess(char guess[]);

int main(){
	char mystery[6];
	loadMw(mystery);
	
	char board[6][6];
	char pointerB[6][6];
	int guessCount = 0;
	char guess[100];
	
	for(int i = 0; i < 6; i++){
		for(int j = 0;j < 6; j++){
			board[i][j] = '\0';
			pointerB[i][j] = '\0';
		}
	}
	while (guessCount < 6){
		if(guessCount == 5){
			printf("\nFINAL GUESS: ");
		}else{
			printf("GUESS %d! Enter your guess: ", guessCount + 1);
		}
		scanf("%s", guess);
				
		while (isVguess(guess)  != 1){
			printf("Your guess must be 5 letters long.\n");
			printf("Please try again: ");
			scanf("%s", guess);
		}
		lowerCase(guess);
		
		char processed[6];
		char pointer[6];
		
		guessProcess(guess, mystery, processed, pointer);

		for(int i = 0; i < 6; i++){
			board[guessCount][i] = processed[i];
			pointerB[guessCount][i] = pointer[i];
		}
		guessCount++;
		
		printf("=================================\n");
		print(board, pointerB, guessCount);
		
		if(equal(guess, mystery) == 1){
			printf("=================================\n");
			printf("             %s\n", processed);
			printf("     You won in %d guesses!\n", guessCount);
			printf("            Amazing!\n");
			
			return 0;
		}
	}	
	printf("You lost, better luck next time!\n");	
	return 0;
}	
void loadMw(char word[]){
	FILE *file = fopen("word.txt", "r");
	if (file == NULL){
		printf("Error: could not open word.txt\n");
		word[0] = '\0';
		return;
	}
	fscanf(file, "%5s", word);
	fclose(file);
}
int isVguess(char guess[]){
	int i = 0;
	while(guess[i] != '\0'){
		if((guess[i] < 'A' || (guess[i] > 'Z'&& guess[i] < 'a') || guess[i] > 'z')){
		return 0;
		}
		i++;
	}
	return i == 5;
}
void lowerCase(char str[]){
	int i = 0;
	while(str[i] != '\0'){
		if(str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i] + 32;
		}
		i++;
	}
}
int equal(char *string1, char *string2){
	int i =0;
	while(string1[i] != '\0' && string2[i] != '\0'){
		if(string1[i] != string2[i]){
		return 0;
		}
		i++;
	}
	return string1[i] == string2[i];
}
void guessProcess(char guess[], char mystery[], char result[], char pointer[]){
	int used[5];
	for(int i = 0; i < 5; i++){
		used[i] = 0;
	}
	for(int i = 0; i < 5; i++){
		if(guess[i] == mystery[i]){
			result[i] = guess[i] - 32;
			used[i] = 1;
		}else{
			result[i] = guess[i];
		}
		pointer[i] = ' ';
	}
	result[5] = '\0';
	pointer[5] = '\0';
	
	for(int i = 0; i < 5; i++){
		if(guess[i] != mystery[i]){
			for(int j = 0; j < 5; j++){
				if(guess[i] == mystery[j] && used[j] == 0){
					pointer[i] = '^';
					used[j] = 1;
					break;
				}
			}
		}
	}
}
void print(char board[][6], char pointerB[][6], int count){
	for(int i = 0; i < count; i++){
		printf("%s\n", board[i]);
		printf("%s\n", pointerB[i]);
	}
}
