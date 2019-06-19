//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Kartik Tyagi on 10/3/18.
//  Copyright © 2018 Kartik Tyagi. All rights reserved.
//
#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

//to make syntax for UNREAL
using int32 = int;
using FString = std::string;

// all values initiallised to 0
struct FBullCowCount // a struct is like a class but all its members are public
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus { //what this is doing is giving us a better return value than 1 or 0 that we would get with bool
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    
};


class FBullCowGame
{
public:
    FBullCowGame();//constructor
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    
    EGuessStatus CheckGuessValidity(FString) const;
    void Reset(); 
    FBullCowCount SubmitValidGuess(FString);
    
    
    
    
    
private: //can have functions an variables
    //see constructor for initialization 
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameWon;
    bool IsLowercase(FString) const;
    bool IsIsogram(FString) const;
};


#endif /* FBullCowGame_hpp */
