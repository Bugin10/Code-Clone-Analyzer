#ifndef _TOKENFINDER_H
#define _TOKENFINDER_H
#include <string>
#include <map>
#include "Tokens.h"
using namespace std;

class Tokenfinder
{
    public: 
        Tokenfinder();
        //return the next token        
        string getNextToken();
        //store line, index and statuses
        string line;
        unsigned int index;
        bool stringstatus;
        bool commentstatus;
        int linenumber;

};
#endif