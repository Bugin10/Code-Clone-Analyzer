#ifndef _PARSERTOKENS_H
#define _PARSERTOKENS_H
#include <string>
#include <map>
using namespace std;

class ParserTokens
{
    public: 
        ParserTokens();
        
        //find and return the token type
        string find(string);
        //check if token is in map
        bool contains(string);
        void add(string);
        //required maps for the conversion
        map<string, string> token;

};
#endif