#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// to make the syntax Unreal engine friendly
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset();} //default constructor

//List of getters
int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLenghtToMaxTries{ {3,10}, {4,10}, {5,15}, {6,15}, {7,20}, {8,20} };
	return WordLenghtToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() // TODO make user enter an isogram
{
	const FString HIDDEN_WORD = "rocket"; // enter only a ISOGRAM with 3 - 8 letters, see GetMaxTries() for amount of tries
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess ins't all lowecase 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessStatus::OK;
	}
}

// recieves a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match than
			if(Guess[GChar] == MyHiddenWord[MHWChar]) 
			{
				// if they're in the same place
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // incriment bulls
				}
				// if they're not in the same place
				else
				{
					BullCowCount.Cows++; // incriment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all the letters of the word
	{
		Letter = tolower(Letter); // Handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{ 
			return false; //we do NOT have an isogram
		} 
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}		
	}
	return true; // for example in cases where /0 is enterd
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
