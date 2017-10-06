/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskTopPlayAgain();


FBullCowGame BCGame; //instantiate a new game

//the entry point of the application
int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		PrintGameSummary();
		bPlayAgain = AskTopPlayAgain();
	}
	while (bPlayAgain);
	return 0; //exit the application
}

// introduce the game
void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I`m thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MyMaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MyMaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		// print number of bulls and cows
		std::cout << "\nBulls= " << BullCowCount.Bulls;
		std::cout << "\tCows= " << BullCowCount.Cows << std::endl;
		std::cout << "You entered your guess: "<< Guess <<std::endl;
	}
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations! You won the game!\n";
	}
	else
	{
		std::cout << "Bad Luck! You lost the game!\n";
	}
	std::cout << "Number of tries: " << BCGame.GetCurrentTry() << " out of " << BCGame.GetMaxTries()<<std::endl;
}

//loop contunually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "\nTry: " << CurrentTry << " of " << BCGame.GetMaxTries() <<" Please enter your guess:\n";
		
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters!\n\n";
			break;
		case EGuessStatus::Wrong_length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters!\n\n";
			break;
		default: 
			// assume the Guess is valid
			break;			
		}
	} while (Status != EGuessStatus::OK);	//keep looping until we get no errors
	return Guess;
}

bool AskTopPlayAgain()
{
	std::cout << "Do you wany to play again with the same hidden word (y/n)?\n";
	FText Response = "";
	getline(std::cin, Response);

	return (Response[0] == 'y') || ((Response[0] == 'Y'));
} 