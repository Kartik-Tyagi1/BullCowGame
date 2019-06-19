//
//  main.cpp
//  BullCowGame
//
//  Created by Kartik Tyagi on 6/2/18.
//  Copyright © 2018 Kartik Tyagi. All rights reserved.
//

//this is console executeable. Game logic is in class
 
 
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// to make syntax for UNREAL
using FText = std::string;
using int32 = int;

//function prototypes outside of class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game which we use to each game


int main() {
    
    
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);
    
    return 0;
}


void PlayGame() //plays a single game
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    //loop for number guess while NOT game won
    //and while there are tries still remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FText Guess = GetValidGuess();
        
        // submit valid guess to game and recieve count
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }
    
    PrintGameSummary();
    
}


void PrintIntro()
{
    std::cout << "\n\nWelcome to Bulls and Cows\n\n";
    std::cout << "  //             \\    " << std::endl;
    std::cout << "  ((__-^^-,-^^-__))   " << std::endl;
    std::cout << "   `-_---' `---_-'    " << std::endl;
    std::cout << "    <__|o` 'o|__>     " << std::endl;
    std::cout << "      \\  `  //       " << std::endl;
    std::cout << "        ): :(         " << std::endl;
    std::cout << "        :o_o:         " << std::endl;
    
    std::cout << std::endl;
    
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter word that I am thinking of?\n";
    std::cout << std::endl;
    return;
}

//loop until user gives valid guess
FText GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
     FText Guess = "";
    do{
        // Get a guess
        int32 CurrentTry = BCGame.GetCurrentTry(); 
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter a Guess: ";
        std::getline(std::cin,Guess);
        
        Status = BCGame.CheckGuessValidity(Guess); //Debug Function to check for error
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word \n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter a word that has all lowercase letters \n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters \n\n";
            break;
        default:
            break;
        }
        
    } while (Status != EGuessStatus::OK); //keep looping unitl we get no errors
    return Guess; //to stop the error
}

bool AskToPlayAgain()
{
    std::cout << " Do you want to play again with same word? (y/n)";
    FText Response = "";
    std::getline(std::cin,Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon() == true)
    {
        std::cout << "Good Job! You Have Won The Game!\n";
    }
    else
    {
        std::cout << "Better Luck Next Time\n";
    }
    
    std::cout << std::endl;
}


