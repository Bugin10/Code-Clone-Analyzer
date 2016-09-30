#include "Tokens.h"
#include <iostream>
using namespace std;
Tokens::Tokens()
{
    //token map
    //keywords
    token["class"] = "class";
    token["function"] = "function";
    token["method"] = "method";
    token["static"] = "static";
    token["int"] = "int";
    token["char"] = "char";
    token["bool"] = "bool";
    token["void"] = "void";
    token["true"] = "true";
    token["false"] = "false";
    token["null"] = "null";
    token["this"] = "this";
    token["let"] = "let";
    token["do"] = "do";
    token["if"] = "if";
    token["else"] = "else";
    token["while"] = "while";
    token["return"] = "return";
    //symbol
    token["{"] = "symbol";
    token["}"] = "symbol";
    token["("] = "symbol";
    token[")"] = "symbol";
    token["["] = "indl";
    token["]"] = "indr";
    token["."] = "symbol";
    token[","] = "symbol";
    token[";"] = "col";
    token["+"] = "add";
    token["-"] = "sub";
    token["*"] = "multiply";
    token["/"] = "divide";
    token["&"] = "and";
    token["|"] = "or";
    token["<"] = "lt";
    token[">"] = "gt";
    token["="] = "set";
    token["~"] = "symbol";
    token["'"] = "symbol";
    token["=="] = "eq";
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
