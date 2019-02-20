#ifndef WORDLIST
#define WORDLIST
#endif // WORDLIST
#include <fstream>


std::string wordlist[1500];


std::string wordlist_funct(int wordIndex)
{
    std::ifstream wordlistFile("wordlist.txt");
    int i;
    for(i=0;i<1500;i++)
    {
        wordlistFile>>wordlist[i];
    }

    return wordlist[wordIndex];
}
