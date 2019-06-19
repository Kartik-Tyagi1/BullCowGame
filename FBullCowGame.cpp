//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Kartik Tyagi on 10/3/18.
//  Copyright © 2018 Kartik Tyagi. All rights reserved.
//


#pragma once
#include "FBullCowGame.hpp"
#include <map>

//to make for UNREAL
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor



int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return (int32)MyHiddenWord.length(); } //(int32) used for int size change
bool FBullCowGame::IsGameWon() const { return bGameWon; }


int32 FBullCowGame::GetMaxTries() const
{
    TMap <int32, int32> WordLengthToMaxTries {{3,4} , {4,7} , {5,10} , {6,15} , {7,20}};
    return WordLengthToMaxTries[(int32)MyHiddenWord.length()];
}



void FBullCowGame::Reset()
{
    // these shouldnt be int32. You are not defining variables. You are setting values to the variables already defined
    const FString HIDDEN_WORD = "planet"; //must be isogram!!!
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameWon = false;
    return;
}




EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const //debugging function
{
    if (!IsIsogram(Guess)) //if guess is not an isogram
    {
        return EGuessStatus::Not_Isogram; //TODO write function
    }
    else if (!IsLowercase(Guess)) // if guess is not lowercase
    {
        return EGuessStatus::Not_Lowercase; // TODO write function
    }
    else if (Guess.length() != GetHiddenWordLength()) //if guess length is too long or too short
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}


FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) //recieves valid guess, increments turns , and returns count
{
    MyCurrentTry++;
    FBullCowCount BullCowCount; //set return variable
       int32 WordLength = (int32)MyHiddenWord.length(); //assuming same length as guess, (int32) used for int size change
    //loop through letters in hidden word
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++){
        //copmare letters against hidden word
        for (int32 GChar = 0; GChar < WordLength; GChar++){
            //if they match (PLANET)
            if (Guess[GChar] == MyHiddenWord[MHWChar]){
                //if they are in the same place
                if (MHWChar == GChar){
                    BullCowCount.Bulls++; //increment bulls
                }
                else{
                    BullCowCount.Cows++; //increment cows
                }
            }
            

        }
    
    }
    if(BullCowCount.Bulls == WordLength)
    {
        bGameWon = true;
    }
    else
    {
        bGameWon = false;
    }
    
    return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
    //treat 0 and 1 letter words as isograms
    if( Word.length() <= 1 ) { return true; }
    
    TMap <char,bool> LetterSeen; //set up our map
    
    for(auto Letter : Word) // all the letters in the word //auto decides datatype
    {
        Letter = tolower(Letter); // to handle word with mixed upper and lower case
    
            if(LetterSeen[Letter])
            {
                return false; //we do NOT have an isograms
            }
            else     //otherwise
            {
                LetterSeen[Letter] = true; //add the letter to the map as seen
            }
    }
    /*
     checking if the bool attached to each letter is true
     however the empty map defaults each letter to false
     so each letter will then go to the else
     and then be set to a bool of true
     then if a repeat comes it will see that that letter has a value of
     true already
     */
    
    return true; //for /0 character
}

bool FBullCowGame::IsLowercase(FString Word) const
{
    if(Word == " ") {return true;}
    
    for (auto Letter : Word)
    {
        if(!islower(Letter))
        {
            return false;
        }
      
    }
    
    return true;
}

















