#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <algorithm>
#include "Tokens.h"
#include "myxml.h"
#include "Tokenfinder.h"

using namespace std;
//tokenise and print the input
int main()
{
    //token storage
    string temptoken;
    string tokentype;
    //object creation
    myxml xmlbuilder;
    Tokens tokens;
    Tokenfinder tokengetter;

    //open the tokens node
    xmlbuilder.addnode("tokens");
    //get tokens until eof
    for (temptoken = tokengetter.getNextToken(); temptoken != "NULL"; temptoken = tokengetter.getNextToken()) {
        //skip token if newline or empty
        if ((temptoken[0] == '\r') or (temptoken[0] == ' ')) {
            continue;
        }
        else {
        }
        //return error if error in getting next token
        if (temptoken == "error") {
            return -1;
        }
        //find the token type
        tokentype = tokens.find(temptoken);
        //build the token node if in map
        if (tokentype != "NULL") {
            xmlbuilder.addnode(tokentype);
            xmlbuilder.addcontent(temptoken);
            xmlbuilder.closenode(tokentype);
        }
        //specify token type as integer, string or identifier
        else if (temptoken != "Empty") {
            //if string
            if ((temptoken[0] == '"') or (temptoken[0] == '\'')) {
                //remove quotes
                temptoken = temptoken.substr(1, temptoken.size() - 2);
                xmlbuilder.addnode("stringConstant");
                xmlbuilder.addcontent(temptoken);
                xmlbuilder.closenode("stringConstant");
            }
            //if integer
            else if (isdigit(temptoken[0])) {
                xmlbuilder.addnode("integerConstant");
                xmlbuilder.addcontent(temptoken);
                xmlbuilder.closenode("integerConstant");
            }
            //mustbe an identifier
            else {
                xmlbuilder.addnode("identifier");
                xmlbuilder.addcontent(temptoken);
                xmlbuilder.closenode("identifier");
            }
        }
    }
    //close the tokens node
    xmlbuilder.closenode("tokens");
    return 0;
}
