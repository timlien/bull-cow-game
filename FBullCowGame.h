//
// Created by Tim Lien on 2018-12-27.
//

#include <string>

#ifndef SECTION_02_FBULLCOWGAME_H
#define SECTION_02_FBULLCOWGAME_H

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWordStatus
{
    Ok,
    Mismatched_Length,
    Not_Lowercase,
    Not_Isogram,
};

class FBullCowGame
{
public:
    FBullCowGame();

    int32 GetMaxTries() const;

    int32 GetCurrentTry() const;

    int32 GetHiddenWordLength() const;

    bool IsGameWon() const;

    EWordStatus ValidateGuess(FString) const;

    void Reset();

    FBullCowCount SubmitValidGuess(FString);

private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;

    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};

#endif //SECTION_02_FBULLCOWGAME_H