#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>


void Hang_visuals(int n);
void SpellBee(int *SpellCheck, int *HangCheck);
void Hangman(int *SpellCheck, int *HangCheck);
int Treasure(int *SpellCheck, int *HangCheck);


int checkwin(char ChosenWord[], char display[])
{
	return strcmp(ChosenWord, display) == 0;
}


//------------------------------------------------------------------------------
void main()
{
	int HangCheck = 0;
	int SpellCheck = 0;


	printf("\n=======================================================================");
	printf("\nYou are traveling through a dense forest...");
	printf("\nSuddenly, you discover a massive treasure chest sealed with two locks!");
	printf("\nBefore you, two gigantic doors rise from the ground.");
	printf("\nEach door holds a game within. Win the games, and earn the keys to your treasure!");
	printf("\n=======================================================================");



Start :
	char LaunchGame;
	printf("\nDo you want to play the SpellBee or Hangman  (S/H) ");
	scanf("\n %c", &LaunchGame);
	if(LaunchGame=='s' || LaunchGame=='S')
	{
		SpellBee(&SpellCheck,&HangCheck);
	}
	else if(LaunchGame=='h' || LaunchGame=='H')
	{
		Hangman(&SpellCheck,&HangCheck);
	}
	else
	{
		printf("wrong input");
		goto Start;
	}

}


//------------------------------------------------------------------------------

void Hangman(int *SpellCheck, int *HangCheck)
{

    if (*SpellCheck==1)
    goto Hangman_Game;
	*HangCheck = 1;


Hangman_Game ://Introduction
	printf("\n---------------------------------------------------------------");
	printf("\nWelcome to the Hangman Game");
	printf("\n");
	printf("\nDifficulty : Easy");
	printf("\n");
	printf("\nWord selection: The computer randomly chooses a word");
	printf("\nand a row of dashes appears on screen, indicating the number of letters.");
	printf("\n");
	printf("\nGuessing: You input a single letter such as a single alphabetic character.");
	printf("\n");
	printf("\nCorrect guess: If the letter is in the word, the computer reveals all");
	printf("\ninstances of that letter in the word display.");
	printf("\n");
	printf("\nIncorrect guess: If the letter is not in the word, it is typically marked"); 
	printf("\nas wrong, and you lose one of your limited attempts. A visual representation");
	printf("\nof the hangman drawing is often completed with each incorrect guess.");
	printf("\n");
	printf("\nOnly The First Letter Will Be Accepted");
	printf("\n---------------------------------------------------------------");


	//--------------------------------------------------------------------------

	//Random Word Code

	char words [20] [7] = {

		"SHADOW",
		"ROCKET",
		"PLANET",
		"MIRROR",
		"JUNGLE",
		"TRAVEL",
		"BRIGHT",
		"FOREST",
		"WIZARD",
		"TEMPLE",
		"SPRAY",
		"DANGER",
		"CASTLE",
		"SILVER",
		"MYSTERY",
		"GARDEN",
		"SPIRIT",
		"LETTER",
		"BUTTER",
		"COFFEE"

	};

	srand(time(0));
	//makes the seed for random number
	//seed decides what random number to take
	//if i take a set seed the number will come out in a set pattern
	//eg if i take seed as 502 i get the numbers 5,6,7,8,2,3,4.....every time i use this seed
	// srand(time(0)) sets the "seed" for the random number generator using the current time.
	// This makes the random numbers (and the chosen word) different each time the game runs.
	// Without it, the program would pick the same "random" word every time you play.


	int randomWord = rand() % 20; //picks a random number form 1 to 20
	char ChosenWord[50];  //the word to guess
	strcpy(ChosenWord, words[randomWord]); // picks the word from the table


	//-----------------------------------------------------------------------------

	// legnth of word
	int WordLength;
	WordLength=strlen(ChosenWord);
	printf("\nThe Number Of Letters Is : %d",WordLength);


	//printing underlines
	int i;
	char display[WordLength+1];

	for(i=0; i<WordLength; i++)
	{
		display[i]= '_';
	}
	display[WordLength] = '\0';
	//-----------------------------------------------------------------------------

	//code for guessing
	char guess;

	int found = 0;  //counter to check if guess is corect
	int lives = 7;  //no of lives
	int k = 0;  //useful variable
	//-----------------------------------------------------------------------------


wrongguess : //to return from a wrong guess


	//-----------------------------------------------------------------------------


	while(lives>0)   //main game loop
	{
		Hang_visuals(lives);
		printf("\nYour Remaining Lives Are %d", lives);
		printf("\nWord: ");
		
		
		for(k=0; k<WordLength; k++) //
		{
			printf("%c", display[k]);  //print the underlines and correct guess
		}

		printf("\nEnter Your Guess : ");

		scanf(" %c%*[^\n]", &guess);

		guess = toupper(guess); //convert the entered guess to uppercase
		found = 0;  // resetting counter

		for(int j =0; j<WordLength; j++)
		{
			if (ChosenWord[j]== guess && display[j] == '_') //if the character mathces and the underline is there
			{
				display[j]= guess; //convert underline to guess

				found = 1; //setting the counter to show correct guess
			}
		}


		if (found == 0) //meaning wrong guess
		{
			lives--;
			printf("\nWrong Guess : The Rope Tightens");
			goto wrongguess;
		}


		else
		{
			printf("\nGOOD GUESS!!!"); //for correct guess
		}


		if (checkwin(ChosenWord, display)) //to check if the word is corect , function above main
		{
			printf("\nCongrats You WON, The Word Was \"%s\".\n",ChosenWord);
			goto Checking;
		}

	}// End Of Loop

	//--------------------------------------------------------------------------

Again:
	int choice; //after losing the game to return or play again
	if(lives==0)
	{
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n   /|\\\  |");
		printf("\n   / \\\  |");
		printf("\n        |");
		printf("\n=========");
		printf("\nOops your are out of lives the word was %s \nIf You Want To Try Again Enter 1 And To Quit Enter 2 : ",ChosenWord);
		scanf("\n %d",&choice);
		if(choice==1)
		{
			goto Hangman_Game;
		}

		else if(choice==2)
		{
		    printf("Once You Enter You Cant Go Back \n You Have To Play Again!!!!");
			main();
		}
		else
			printf("\nWrong Input");
		goto Again;
	}

	else
	{
		printf("\nCongrats You Win");
	}


Checking :  //label
	if(*SpellCheck!=1) //checking if player had played the other game
	{
		printf("\nHangman Has Been Completed and Now You Must Go The Other Door");
		SpellBee(SpellCheck, HangCheck);
	}

	else if(*SpellCheck == 1)
	{
		printf("Congrats You Now Posses Both The Keys Now Head Out And Take Your Reward");
		Treasure( SpellCheck, HangCheck);

	}
	//to make choice if they lose to return back or retry


GameEnd:
	printf("\nGAME IS FINISHED");

}

void Hang_visuals(int n)
{

	switch(n) {
	case 7:
		printf("\n    +---+");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 6:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 5:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n        |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 4:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n    |   |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 3:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n   /|   |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 2:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n   /|\\\  |");
		printf("\n        |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 1:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n   /|\\\  |");
		printf("\n   /    |");
		printf("\n        |");
		printf("\n=========");
		break;

	case 0:
		printf("\n    +---+");
		printf("\n    |   |");
		printf("\n    0   |");
		printf("\n   /|\\\  |");
		printf("\n   / \\\  |");
		printf("\n        |");
		printf("\n=========");
		break;


	default:
		printf("ERROR!!!!!");

	}

}
//HangMan Game End
//SpellBee Game Launch


void SpellBee(int *SpellCheck,int *HangCheck)
{
    
    printf("\n=============================================================\n");
    printf("           THE QUEEN BEE'S WORD TRIAL \n");
    printf("=============================================================\n");
    printf("You have wandered into the forbidden Hive Of QUEEN BEE,\n");
    
    printf("\nShe and her army of razor-winged battle bees surround you…\n");
    printf("Her golden voice echoes:\n");
    
    printf("\nSurvive by earning points.\n");
    printf("\n=============================================================\n");
    printf("\nRULES OF THE WORD TRIAL:\n");
    printf("1. Every word will be converted to UPPER CASE\n");
    printf("2. Must include the sacred letter: A\n");
    printf("3. Must be at least 4 letters long\n");
    printf("4. Allowed letters: A, D, G, M, N, O, R\n");
    printf("5. No plurals or abbreviations\n");
    printf("6. Points = word length\n");
    printf("7. Earn **35 or more** points in **7 tries** to survive!\n");
    printf("\n=============================================================\n");
    printf("Every accepted word weakens the Bee Army.\n");
    printf("Every mistake makes them buzz closer…\n");
    printf("May luck be on your side.\n");
    printf("\nTHE TRIAL BEGINS...\n");
    Retry:
    char validLetters[] = "ADGMNOR";

    // Approved dictionary of valid words
    const char *validWords[] = {
        "GRANDAM","GORMAND","RANDOM","DRAGON","ADORN","AMONG","ARGON",
        "GONAD","GROAN","MANGO","NOMAD","ORGAN","RADON","GRAND",
        "AGRO","DAMN","DANG","DORM","DRAG","MOAN","NORM","ROAD",
        "ROAM","RANG","DARN"
    };
    int validWordCount = sizeof(validWords) / sizeof(validWords[0]);

    char usedWords[7][20];
    int points = 0;
    int tries = 7;

    for (int i = 0; i < tries; i++) {
        char word[20];
        int valid = 1;

        printf("\n\nWord Attempt %d — The bees buzz impatiently: ", i + 1);
        scanf("%s", word);

        // Convert to uppercase
        for (int j = 0; j < strlen(word); j++) {
            word[j] = toupper(word[j]);
        }

        // Check for repetition
        for (int k = 0; k < i; k++) {
            if (strcmp(word, usedWords[k]) == 0) {
                printf("The Queen shrieks: \"You dare repeat a word?!\"\n");
                printf("Her bees swarm and sting you mercilessly.\n");
                printf("GAME OVER.\nOnce You Enter You Cant Go Back \n You Have To Play Again!!!!");
                goto Retry;
            }
        }

        // Store word
        strcpy(usedWords[i], word);

        // Check length
        if (strlen(word) < 4) {
            printf("\"Too short!\" the bees hiss.\n");
            valid = 0;
        }

        // Check 'A'
        if (strchr(word, 'A') == NULL) {
            printf("\"Where is the sacred A?!\" the Queen growls.\n");
            valid = 0;
        }

        // Check allowed letters
        for (int j = 0; j < strlen(word); j++) {
            if (strchr(validLetters, word[j]) == NULL) {
                printf("A guard bee points its stinger at '%c' — forbidden!\n", word[j]);
                valid = 0;
                break;
            }
        }

        // Check dictionary
        int isInList = 0;
        for (int j = 0; j < validWordCount; j++) {
            if (strcmp(word, validWords[j]) == 0) {
                isInList = 1;
                break;
            }
        }
        if (!isInList) {
            printf("\"%s\" is not one of our sacred hive-words!\" the Queen declares.\n", word);
            valid = 0;
        }

        // If valid
        if (valid) {
            int gained = strlen(word);
            points += gained;

            printf("The Queen nods. \"%s\" is worthy. (+%d points)\n", word, gained);
            printf("Current points: %d\n", points);
	    printf("The Bee Army swarms closer... Current points: %d\n", points);
        }
    }

    // Final result
    printf("\n=============================================================\n");
    printf("Final Score: %d\n", points);

    if (points >= 35) {
        printf("With a mighty roar, the Queen Bee yields.\n");
        printf("\"You have surpassed my challenge... You may leave the Hive.\"\n");
        printf("YOU WIN!\n");
    } else {
        printf("The bees screech in triumph.\n");
        printf("The Queen Bee whispers: \"You have failed, mortal...\"\n");
        printf("Her Bee Troops descend upon you.\n");
        printf("YOU LOSE — STUNG BY THE SWARM!\n");
        printf("Once You Enter You Cant Go Back \n You Have To Play Again!!!!");
			
        goto Retry;
    }

    printf("=============================================================\n");
    
	*SpellCheck = 1;
	if(*HangCheck==1)
	{
		Treasure(SpellCheck, HangCheck);
	}
	else if(*HangCheck!= 1)
	{
		printf("\nNow That The Queen Is Defeated Take This Key And Now You Must Enter The Next Door");
		Hangman(SpellCheck, HangCheck);
	}

}

int Treasure(int *SpellCheck,int  *HangCheck)
{
	if(*SpellCheck==1 && *HangCheck==1)
	{
		printf("\nYou Got The Treasure!!!!");
	}
	
}