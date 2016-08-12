#ifndef _TOKENS_H
#define _TOKENS_H
#include <string>
#include <map>
using namespace std;

class Tokens
{
    public: 
        Tokens();
        //methods
        string find(string);
        bool contains(string);
        void add(string);
        //required maps for the conversion
        map<string, string> token;

};
#endif