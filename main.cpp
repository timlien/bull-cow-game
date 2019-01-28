#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();

void PlayGame();

FText GetGuess();

bool AskToPlayAgain();

void PrintGameSummary();

FBullCowGame Game;

int main()
{
    do
    {
        PrintIntro();
        PlayGame();
    }
    while (AskToPlayAgain());

    return 0;
}

/** introduce game */
void PrintIntro()
{
    std::cout << std::endl << "Welcome to Bulls and Cows, a fun word game" << std::endl;
    std::cout << "Can you guess the " << Game.GetHiddenWordLength() << " letter isogram I'm thinking of" << std::endl
              << std::endl;
}

/** start the guess and check the result */
void PlayGame()
{
    Game.Reset();
    int32 MaxTries = Game.GetMaxTries();

    while (! Game.IsGameWon() && Game.GetCurrentTry() <= MaxTries)
    {
        // while guess is not valid, keep asking player to submit guess
        FText Guess = GetGuess();

        FBullCowCount FBullCowCount = Game.SubmitValidGuess(Guess);
        std::cout << "Bull: " << FBullCowCount.Bulls << " Cows: " << FBullCowCount.Cows << std::endl << std::endl;
    }

    // if game it not won, show you lose message
    PrintGameSummary();
}

void PrintGameSummary()
{
    if (Game.IsGameWon())
    {
        std::cout << "Well done. You win!" << std::endl;
    }
    else
    {
        std::cout << "Better luck next time." << std::endl;
    }

}

/** get player's guess */
FText GetGuess()
{
    int32 CurrentTry = Game.GetCurrentTry();

    FText Guess;
    EWordStatus Status;

    do
    {
        std::cout << "Try " << CurrentTry << " of " << Game.GetMaxTries() << ". " << "Enter your guess: ";
        std::getline(std::cin, Guess);

        Status = Game.ValidateGuess(Guess);
        switch (Status)
        {
            case EWordStatus::Mismatched_Length:
                std::cout << "Please enter a " << Game.GetHiddenWordLength() << " letter word." << std::endl
                          << std::endl;
                break;
            case EWordStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;
                break;
            case EWordStatus::Not_Lowercase:
                std::cout << "Please enter a letter word with lowercase." << std::endl << std::endl;
                break;
            default:
                break;
        }
    }
    while (Status != EWordStatus::Ok);

    return Guess;
}

bool AskToPlayAgain()
{
    FText Response;
    std::cout << "Do you want to play again (y/n)? ";
    getline(std::cin, Response);
    return Response[0] == 'y' || Response[0] == 'Y';
}
