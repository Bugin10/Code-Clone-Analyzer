#include "Tokens.h"
#include <iostream>
using namespace std;
Tokens::Tokens()
{
    //token map
    //keywords
    token["class"] = "keyword";
    token["constructor"] = "keyword";
    token["function"] = "keyword";
    token["method"] = "keyword";
    token["field"] = "keyword";
    token["static"] = "keyword";
    token["var"] = "keyword";
    token["int"] = "keyword";
    token["char"] = "keyword";
    token["boolean"] = "keyword";
    token["void"] = "keyword";
    token["true"] = "keyword";
    token["false"] = "keyword";
    token["null"] = "keyword";
    token["this"] = "keyword";
    token["let"] = "keyword";
    token["do"] = "keyword";
    token["if"] = "keyword";
    token["else"] = "keyword";
    token["while"] = "keyword";
    token["return"] = "keyword";
    //symbol
    token["{"] = "symbol";
    token["}"] = "symbol";
    token["("] = "symbol";
    token[")"] = "symbol";
    token["["] = "symbol";
    token["]"] = "symbol";
    token["."] = "symbol";
    token[","] = "symbol";
    token[";"] = "symbol";
    token["+"] = "symbol";
    token["-"] = "symbol";
    token["*"] = "symbol";
    token["/"] = "symbol";
    token["&"] = "symbol";
    token["|"] = "symbol";
    token["<"] = "symbol";
    token[">"] = "symbol";
    token["="] = "symbol";
    token["~"] = "symbol";
    token["'"] = "symbol";
    token["=="] = "symbol";
}

bool Tokens::contains(string intoken)
{
    //use a constant iterator to find the symbol
    map<string, string>::const_iterator it = token.find(intoken);
    return it != token.end();
}

//find and return the token type
string Tokens::find(string tokin)
{
    if (contains(tokin)) {
        return token[tokin];
    }
    //no matching token
    else {
        return "NULL";
    }
}

void Tokens::add(string symbol)
{
    //make sure symbol doesnt exist
    if (!contains(symbol)) {
        //if the symbol is a variable
        //add the address
        token[symbol] = "identifier";
    }
}
