/* The game logic (no view code or direct user interaction
The game is a simple guess game based on mastermind
This file should not be touched!*/
#pragma once
#include <string>

// to make the syntax Unreal engine friendly
using FString = std::string;
using int32 = int;

// all values intialised to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	InValid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase

};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor


	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	// counts bulls and cows, and increasing turn #, assuming valid guess

	// ^^ Please try and ignore this and focus on the interface above ^^
private:
	// see constructor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;

};