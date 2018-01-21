// This program creates an artificial intelligence that is designed
// to copy the styles of famous authors and write a sentence in that
// style based upon the provided data sample.

#include <iostream>
#include <fstream>
#include <set>
#include "WordPair.h"

using namespace std;

char isGood(char);
void intro();
string grabLast(string, int);
multiset<WordPair> createList(int, string);
WordPair chooseRandomFromMultiSet(multiset<WordPair>);
string makeSentence(multiset<WordPair>, int);

int main()
{
    int searchLevel;
    string bookName, fileName;
    srand ((unsigned int) time(NULL));   // seed for random

    intro();

    cout << "Please Type in level of search : ";
    cin >> searchLevel;
    cin.ignore();
    cout << "Please Type in the file name you would like your OPUS based on : ";
    getline(cin, bookName);

    fileName = bookName;
    string fileType = ".txt";
    if (fileName.find(fileType) == std::string::npos) // if file name is entered without the data type
        fileName += fileType;

    multiset<WordPair> mySet = createList(searchLevel, fileName);

    // press enter to quit, anything else to continue
    string again = "enterLoop";

    do {
        if (again.empty())
            break;

        cout << "******************************************************" << endl <<
             "After careful thought, I surmise that the next" << endl <<
             "sentence to your opus should be: " << endl <<
             "******************************************************" << endl;

        cout << ">>" << makeSentence(mySet, searchLevel) << endl;

        cout << "******************************************************" << endl
             <<"Do you want another? Press enter to quit, anything else to repeat." << endl;
    } while (getline(cin, again));

    return 0;
}

// Prints introduction
void intro()
{
    cout << "Welcome to the grand writing artificial intelligence" << endl
         << "How may we help you today?" << endl
         << endl;
}

// Creates the big multiset of WordPair.
// Read though the file and create a multiset of all possible word strings and the
// corresponding following letter, using the provided depth from the main program.
multiset <WordPair> createList(int searchLevel, string fileName)
{
    multiset<WordPair> mySet;
    char ch;

    ifstream fin (fileName);
    string pattern = "";

    while (fin >> noskipws >> ch)
    {
        char c = isGood(ch);
        if (c != '~')
        {
            // avoid two space in a row
            if (!(c == ' ' && pattern.back() == ' '))
            {
                WordPair pair(pattern, c);
                mySet.insert(pair);
            }
            pattern += c;
            if (c == '.') pattern = "";
            if (pattern.length() > searchLevel) pattern = pattern.substr(1);  // keep the size of pattern
        }
    }
    return mySet;
}

// Returns good characters.
// Ignore characters from the file that you can't see/print. This finds all
// the useful characters and turns everything else into some character that can be ignored in the main method.
char isGood(char x);

// Return a randomly picked element from the set.
WordPair chooseRandomFromMultiSet(multiset<WordPair> fromMe)
{
    multiset<WordPair>::iterator iter = fromMe.begin();
    advance(iter, rand() % fromMe.size());  // randomly pick a element within size of the set
    return *iter;
 }

// Returns last couple of character of the string to compare them to the list of possibilities.
string grabLast(string x, int searchLevel)
{
    if (x.length() < searchLevel) return x; // if no enough characters in string, return all of them
    return x.substr(x.length() - searchLevel, (unsigned long) searchLevel);
}

// Return the finished sentence.
// Take the finished set of pairs, the necessary distance, and use the two to complete the sentence by
// taking data from the mfrvc..ultiset and smooshing it together.
string makeSentence(multiset<WordPair> fromMe, int searchLevel)
{
    string sentence = "";
    multiset<WordPair>smallerSet;
    multiset<WordPair>::iterator iter;

    while (sentence.back() != '.')  // when the end is not hit by a period
    {
        string lastString = grabLast(sentence, searchLevel);
        smallerSet.clear(); // clear smallerSet for next use

        for (iter = fromMe.begin(); iter != fromMe.end(); iter++)
        {
            if (lastString == iter->getPatterFound()) // find matching pairs in the complete set.
                smallerSet.insert(*iter); // insert them to small set.
        }

        WordPair chosenRandom = chooseRandomFromMultiSet(smallerSet);
        sentence += chosenRandom.getFollowingChar();
    }
    return sentence;
}

char isGood(char x) {
    if (x > 255 || x < 0) return '~';
    if (isprint(x)) return x;
    if (iscntrl(x)) return ' ';
    return '~';
}
