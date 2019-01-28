//
// Created by Tim Lien on 2018-12-27.
//

#include "FBullCowGame.h"
#include <map>

#define FMap std::map

FBullCowGame::FBullCowGame()
{
    Reset();
}

int32 FBullCowGame::GetMaxTries() const
{
    return GetHiddenWordLength() * 2;
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
    constexpr int32 INITIAL_TRY = 1;
    MyCurrentTry = INITIAL_TRY;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;

    bGameWon = false;
}

EWordStatus FBullCowGame::ValidateGuess(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EWordStatus::Not_Isogram;
    }
    else if (!IsLowercase(Guess))
    {
        return EWordStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
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

bool FBullCowGame::IsIsogram(FString Word) const
{
    bool isogram = true;

    FMap<char, bool> LetterSeen;
    for (char Letter : Word)
    {
        Letter = static_cast<char>(tolower(Letter));
        if (LetterSeen[Letter])
        {
            isogram = false;
            break;
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }


    return isogram;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    bool IsLowercase = true;

    for (auto Letter : Word)
    {
        if (Letter == ' ' || Letter == '\0' || !islower(Letter))
        {
            IsLowercase = false;
            break;
        }
    }

    return IsLowercase;
}

