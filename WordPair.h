#include <string>
#include <iostream>

#ifndef WORDPAIR_H
#define WORDPAIR_H

class WordPair
{
    public:

        WordPair(std::string, char);
        std::string getPatterFound() const;
        char getFollowingChar() const;
        void printMe() const;
        bool operator <(const WordPair& wp) const
        {
            return getPatterFound() < wp.getPatterFound();
        }

    private:
        std::string patterFound;
        char followingChar;
};
#endif //WORDPAIR_H
