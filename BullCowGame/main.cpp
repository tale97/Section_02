/* This is console executable that makes use of BullCow class
This acts as the view in MVC pattern, and is responsible for 
all user interaction. For game logic see FBullCowGame class*/

// pre-processor directive
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// prototypes of functions
void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
// void GameSummary();

FBullCowGame BCGame; //instantiate new game

// entry point for our application
int main() 
{	
	bool WantToPlayAgain;
	do 
	{
		PrintIntro();
		PlayGame();
		WantToPlayAgain = AskToPlayAgain();
	} while (WantToPlayAgain);

	return 0;
}

// introduce the game
void PrintIntro()
{
	// strong form of constant, whose value must be known at compile time
	const int32 WORD_LENGTH = BCGame.GetWordLength();
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram I'm thinking off?" << std::endl << std::endl;
	return;
}

void PlayGame()
{	
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game is NOT won
	// and there are still tries remaining
	while(!BCGame.isGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		
		// Submit valid guess to the game, receives counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

		// Print # of bulls and cows
		std::cout << "Your guess: " << Guess << std::endl << std::endl;
	}

	// TODO summarize game
	if (BCGame.isGameWon()) { std::cout << "YOU WON!\n"; }
	else { std::cout << "U SUCK!\n"; }

	return;
}

// loop until get a valid guess from the player
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		// get a guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". Enter your guess: ";
		getline(std::cin, Guess);

		// check validity
		Status = BCGame.CheckGuessValidity2(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetWordLength() << "-letter word!\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (word without repeating letters)!\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << "Please enter all lowercase letter word!\n";
			break;
		default:
			// assume guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Wanna play again? (y/n) ";
	FText answer = "";
	getline(std::cin, answer);
	std::cout << std::endl;
	return (answer[0] == 'y' || answer[0] == 'Y');
}



