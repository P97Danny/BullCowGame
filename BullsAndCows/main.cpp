/*	Written by Danny Peters with help from the Unreal Course on Udemy.com.
	This is the console executable, that makes use of the BullCow class.
	This acts as the view in a MVC pattern, and is resposible far all
	user interaction. For game logic see the FbullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game
int32 MaxTries = BCGame.GetMaxTries();

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		// TODO add a game summery
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << " ------------------------------------------------------------" << std::endl;
	std::cout << " | Welcome to Bulls and Cows, a fun word game.              |" << std::endl;
	std::cout << " | Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?      |" << std::endl;
	std::cout << " | You've got " << MaxTries << " turns to guess the word.                    |" << std::endl;
	// TODO make a rules function if possible
	//std::cout << " | Press [r] for the rules.                                 |" << std::endl; 
	std::cout << " |                                                          |" << std::endl;
	std::cout << " | Good luck!                                               |" << std::endl;
	std::cout << " ------------------------------------------------------------";
	std::cout << std::endl << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();

	// loop asking for guesses while the game is NOT won
	// AND there are still tries remaining
	while (! BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls : " << BullCowCount.Bulls << ". Cows : " << BullCowCount.Cows;
		std::cout << "\n\n";
	}
	// TODO summarise the game
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::InValid_Status;

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << "  " << std::endl;
		std::cout << "Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word!" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please use all lowercase!" << std::endl;
			break;
		default:
			// assume the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until there are no errors
	return Guess;
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you wanna play again? [Yes] or [No] " << std::endl;
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}

