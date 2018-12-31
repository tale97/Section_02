#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// initialize two int32 to 0
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool isGameWon() const;
	int32 GetWordLength() const;

	void Reset(); // TODO make a more rich return value
	bool CheckGuessValidity(FString);

	EGuessStatus CheckGuessValidity2(FString) const;
	// counts bulls and cows, and increases try #
	FBullCowCount SubmitValidGuess(FString);


// Ignore this and focus on the interface above 
private:
	// constructor will initialize at runtime
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};