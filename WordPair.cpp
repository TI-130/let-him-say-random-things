#include "WordPair.h"
#include <iostream>
using namespace std;

WordPair :: WordPair(std::string str, char ch)
{
    patterFound = str;
    followingChar = ch;
}

string WordPair::getPatterFound() const {return patterFound;}
char WordPair::getFollowingChar() const{return followingChar;}
void WordPair::printMe() const {cout << "(\"" <<  getPatterFound() << "\", '" << getFollowingChar() << "')" << endl;}
