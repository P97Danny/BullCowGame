/*	Written by Danny Peters with help from the Unreal Course on Udemy.com.
	This is the console executable, that makes use of the BullCow class.
	This acts as the view in a MVC pattern, and is resposible far all
	user interaction. For game logic see the FbullCowGame class. */
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal engine friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGameSummery();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game, wich we re-use across plays
int32 MaxTries = BCGame.GetMaxTries();

int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummery();
		bPlayAgain = AskToPlayAgain();
	}
	while (bPlayAgain);
	std::cout << "\nD:<" << std::endl;
	return 0;
}

void PrintIntro() // TODO make a rules option
{	// startcreen in ascii art
	std::cout << " ______        _ _                         _     ______                 " << std::endl;
	std::cout << "(____  \\      | | |                       | |   / _____)                " << std::endl;
	std::cout << " ____)  )_   _| | | ___     ____ ____   _ | |  | /      ___  _ _ _  ___ " << std::endl;
	std::cout << "|  __  (| | | | | |/___)   / _  |  _ \\ / || |  | |     / _ \\| | | |/___)" << std::endl;
	std::cout << "| |__)  ) |_| | | |___ |  ( ( | | | | ( (_| |  | \\____| |_| | | | |___ |" << std::endl;
	std::cout << "|______/ \\____|_|_(___/    \\_||_|_| |_|\\____|   \\______)___/ \\____(___/ " << std::endl;
	std::cout << std::endl;
	std::cout << " \n------------------------------------------------------------" << std::endl;
	std::cout << "| Welcome to Bulls and Cows, a fun word game.              |" << std::endl;
	std::cout << "| Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking of?      |" << std::endl;
	std::cout << "| You've got " << MaxTries << " turns to guess the word.                   |" << std::endl;
	std::cout << "|                                                          |" << std::endl;
	std::cout << "| Good luck!                                               |" << std::endl;
	std::cout << "------------------------------------------------------------";
	std::cout << std::endl << std::endl;
	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	// loop asking for guesses while the game is NOT won
	// AND there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game, and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls : " << BullCowCount.Bulls << ". Cows : " << BullCowCount.Cows;
		std::cout << "\n\n";
	}
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() 
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::InValid_Status;

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() <<  std::endl;
		std::cout << "Enter your guess: ";
		getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word!\n" << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase: 
			std::cout << "Please use all lowercase!\n" << std::endl;
			break;
		default:
			// assume the guess is valid
			break;
		}
	} 
	while (Status != EGuessStatus::OK); // keep looping until there are no errors
	return Guess;
}

void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{	// winning screen in ascii art
		std::cout << "__  ______  __  __   _       _______   ____" << std::endl;
		std::cout << "\\ \\/ / __ \\/ / / /  | |     / /  _/ | / / /" << std::endl;
		std::cout << " \\  / / / / / / /   | | /| / // //  |/ / / " << std::endl;
		std::cout << " / / /_/ / /_/ /    | |/ |/ // // /|  /_/  " << std::endl;
		std::cout << "/_/\\____/\\____/     |__/|__/___/_/ |_(_)   " << std::endl;
		std::cout << "\nWELL DONE!\n" << std::endl;
	}
	else
	{	//losing screen in ascii art
		std::cout << "__   _______ _   _   _     _____ _____ _____ _ " << std::endl;
		std::cout << "\\ \\ / /  _  | | | | | |   |  _  /  ___|  ___| |" << std::endl;
		std::cout << " \\ \V /| | | | | | | | |   | | | \\ `--.| |__ | |" << std::endl;
		std::cout << "  \\ / | | | | | | | | |   | | | |`--. \\  __|| |" << std::endl;
		std::cout << "  | | \\ \\_/ / |_| | | |___\\ \\_/ /\\__/ / |___|_|" << std::endl;
		std::cout << "  \\_/  \\___/ \\___/  \\_____/\\___/\\____/\\____/(_)" << std::endl;
		std::cout << "\nToo bad! Better luck next time!\n" << std::endl;
	}
}

bool AskToPlayAgain()
{
	FText Response;
	std::cout << "Do you wanna play again with the same hidden word? [Yes] or [No] " << std::endl;
	getline(std::cin, Response);
	return (Response[0] == 'y' || Response[0] == 'Y');
}
