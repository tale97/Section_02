#include "FBullCowGame.h"
#include <map>
#define TMAP std::map

using int32 = int;

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::isGameWon() const { return bGameIsWon; }

void FBullCowGame::Reset()
{
	constexpr int32  MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "ant";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}

bool FBullCowGame::CheckGuessValidity(FString Guess)
{
	return Guess.length() == MyHiddenWord.length();
}

EGuessStatus FBullCowGame::CheckGuessValidity2(FString Guess) const
{
	if (!IsIsogram(Guess))// if guess isn't isogram, return error
	{
		return EGuessStatus::Not_Isogram;
	} // if isn't all lowercase, return error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_lowercase;
	} // if length is wrong, return error
	else if (Guess.length() != GetWordLength())
	{
		return EGuessStatus::Wrong_Length;
	} // else return ok
	else
	{
		return EGuessStatus::OK;
	}
	
	return EGuessStatus::OK;
}

// receives a valid guess, increments turns, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop thru all letters in guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++) 
	{
		for (int32 j = 0; j < HiddenWordLength; j++) 
		{
			if (Guess[i] == MyHiddenWord[j]) 
			{
				if (i == j) { BullCowCount.Bulls++; }
				else { BullCowCount.Cows++; }
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength) { bGameIsWon = true; }
	else { bGameIsWon = false; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup map
	TMAP<char, bool> LetterSeen;

	// loop thru every letter in guess
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		// if letter not in map, add to map
		if (LetterSeen.find(Letter) == LetterSeen.end()) {
			LetterSeen.insert(std::pair<char, bool>(Letter, true));
		}
		// else, return false
		else {
			return false;
		}
	}

	return true; // for example. where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) { return false; }
	}
	return true;
}


