#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "wordlist.h"
#include <fstream>

//This function displays the hangman depending on how many errors you've made
void hangman(int hangmanLevel)
{
    if (hangmanLevel==0)
        std::cout<<" ___________\n |/        |\n |\n |\n |\n |\n |\n |\n |\n_|_ \n";
    else if (hangmanLevel==1)
        std::cout<<" ___________\n |/        |\n |         O\n |\n |\n |\n |\n |\n |\n_|_ \n";
    else if (hangmanLevel==2)
        std::cout<<" ___________\n |/        |\n |         O\n |        /|\n |\n |\n |\n |\n |\n_|_ \n";
    else if (hangmanLevel==3)
        std::cout<<" ___________\n |/        |\n |         O\n |        /|\\ \n |\n |\n |\n |\n |\n_|_ \n";
    else if (hangmanLevel==4)
        std::cout<<" ___________\n |/        |\n |         O\n |        /|\\ \n |         |\n |        /\n |\n |\n |\n_|_ \n";
    else if (hangmanLevel==5)
        {
        std::cout<<" ___________\n |/        |\n |         O\n |        /|\\ \n |         |\n |        / \\ \n |\n |\n_|_ \n";
        }
    else
        std::cout<<"You should never see this";
}

//This function checks if our input character, although part of the word, has been entered already
bool alreadyUsed(std::string inputChar, std::string blankWord)
{
    bool wasUsed=0;
    unsigned int i;
    for (i=0; i<blankWord.length(); i++)
    {
        if (blankWord.at(i)==inputChar.at(0)&&inputChar.at(0)!='_'&&inputChar.at(0)!=' ')
        {
            wasUsed+=1;
        }
        else wasUsed=wasUsed;
    }
    return wasUsed;
}

//This function ensues that only 1 character is kept, even though the user might input a longer string
std::string ignoreExtraCharacters(std::string currentGuess)
{
    int length =currentGuess.length();
    int truncate = length-1;
    if (length>1)
    {
        currentGuess.erase(1, truncate);
    }
    return currentGuess;
}

int main()
{
    char startbutton;
    std::cout<<":::::::::: NEW GAME ::::::::::\nPress any key to begin.\n";
    std::cin>>startbutton;

//  Generate a random word index; the word corresponding to that index will be looked up in the word list
    int wordIndex;
    std::srand(static_cast<unsigned int>(std::time(0)));
    wordIndex=std::rand();
    wordIndex=wordIndex%71+(7*(wordIndex%100));

//  We declare a currentWord variable and link it to the word list function in the wordlist.h header
    std::string currentWord;
    currentWord=wordlist_funct(wordIndex);

//  The blankWord is displayed like this: "_ _ _ _ _ ", depending on how many letters the word has
    unsigned int i;
    std::string blankWord(2*currentWord.length(), '*');
    for (i=0; i<2*currentWord.length(); i+=2)
    {
        blankWord.at(i)='_';
        blankWord.at(i+1)=' ';
    }
    std::cout<<"\n"<<blankWord;

//  This code snippet formats our randomly chosen word like the blankWord, adding spaces between letters
    std::string hiddenWord(2*currentWord.length(), '?');
    for (i=0; i<2*currentWord.length(); i+=2)
    {
        hiddenWord.at(i)=currentWord.at(i/2);
        hiddenWord.at(i+1)=' ';

    }
    std::cout<<"\n";

//  We begin playing; so far, we have neither won nor lost the game, and we haven't made any mistakes
    bool win=0;
    bool lose=0;
    int mistakeIncrement=0;
    std::string currentGuess(1, '?');

//  This loop will have us keep guessing letters until either we discover the whole word or we make too many mistakes
    while (win==0&&lose==0)
    {
//      The user inputs a random letter; the ignoreExtraCharacters function is called to ensure it's just one letter
        std::cin>>currentGuess;
        currentGuess = ignoreExtraCharacters(currentGuess);

//      Now we get to the meat of things
        bool correctGuess=0;    //we don't know yet if our guess is right, by default it is not

        bool alreadyUsedVar=alreadyUsed(currentGuess, blankWord); //check if we've already entered a correct variable

//      This loop checks if our guess is correct, and displays the word with the letters we've uncovered so far, in their right place
        for (i=0; i<2*currentWord.length(); i+=2)
        {
            if(currentGuess.at(0)==hiddenWord.at(i)&&alreadyUsedVar==0)
            {
                correctGuess=1;
                blankWord.at(i)=currentGuess.at(0);
                std::cout<<blankWord.at(i)<<blankWord.at(i+1);
            }
            else
            {
                std::cout<<blankWord.at(i)<<blankWord.at(i+1);
            }
        }
        std::cout<<"\n\n";

//      This if statement increments the mistakeIncrement and displays the hangman if our guess was incorrect
        if (correctGuess==0)
        {
            mistakeIncrement+=1;
            hangman(mistakeIncrement);
        }

//      Win condition (congrats!)
        if (blankWord==hiddenWord&&mistakeIncrement<5)
        {
            std::cout<<"\nYOU WON THE GAME!";
            win=1;
        }
//      Lose condition
        else if (mistakeIncrement==5)
        {
            lose=1;
            std::cout<<"\n"<<hiddenWord<<"\n"; //so that you're not left hanging... completely :P
            std::cout<<"\nYOU LOST THE GAME!";
        }
//      Keep playing
        else
        {
            win=0;
            lose=0;
        }

        std::cout<<"\n";
    }

    return 0;
}

//known bugs for the first round of testing:
//- you can enter a bunch of characters at once and have them all count - RESOLVED
//- the mistake increment doesn't go up if you enter a character you have already entered - RESOLVED
//- the game doesn't recognise the equivalence between uppercase and lowercase letters

//feature idea: choose difficulty
