//
// Created by Tim Lien on 2018-12-27.
//

#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
    return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
    return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const
{
    return bGameWon;
}

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 5;
    MyMaxTries = MAX_TRIES;

    constexpr int32 INITIAL_TRY = 1;
    MyCurrentTry = INITIAL_TRY;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;

    bGameWon = false;
}

EWordStatus FBullCowGame::ValidateGuess(FString Guess) const
{
    if (false)
    {

    }
    else if (false)
    {

    }
    else if (Guess.length() != GetHiddenWordLength() )
    {
        return EWordStatus::Mismatched_Length;
    }
    else
    {
        return EWordStatus::Ok;
    }
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount = {};

    int32 WordLength = GetHiddenWordLength();
    // loop through string
    for (int32 i = 0; i < WordLength; i++)
    {
        for (int32 j = 0; j < WordLength; j++)
        {
            if (Guess[i] == MyHiddenWord[j])
            {
                if (i == j)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }

    if (BullCowCount.Bulls == GetHiddenWordLength())
    {
        bGameWon = true;
    }

    return BullCowCount;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
    return (int32) MyHiddenWord.length();
}

