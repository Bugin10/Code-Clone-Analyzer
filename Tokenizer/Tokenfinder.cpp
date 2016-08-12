//test comment
#include "Tokenfinder.h"
#include "Tokens.h"
#include <iostream>
using namespace std;
Tokenfinder::Tokenfinder()
{
    //start at line 0
    linenumber = 0;
    //get the first line
    getline(cin, line);
    //ignore comments
    if (line.find("//") != string::npos) {
        line = line.substr(0, line.find("//"));
        line += '\r';
        linenumber++;
    }
    index = 0;
    //initialise statuses
    stringstatus = false;
    commentstatus = false;
}

//return the next token
string Tokenfinder::getNextToken()
{
    //temporary token storage
    string temptoken;
    string tokentype;
    //create map
    Tokens tokens;
    //ignore commented input
    //multiline comment on single line
    if ((line.find("/*") != std::string::npos) && (line.find("*/") != std::string::npos)) {
        line = line.erase(line.find("/*"), line.find("*/") - line.find("/*") + 2);
    }
    //multiline comment start
    else if ((line.find("/*") != std::string::npos)) {
        commentstatus = true;
        line = line.erase(line.find("/*"), line.size() - line.find("/*"));
    }
    //multiline comment end
    else if ((line.find("*/") != std::string::npos)) {
        commentstatus = false;
        line = line.erase(0, line.find("*/") + 2);
    }
    //if no end of comment found, remove the entire line
    if (commentstatus == true) {
        line = line.erase(0, line.size());
    }
    
    //loop through line
    while (index < line.size()) {
         //ignore indentations and spaces
        while ((line[index] == ' ') or (line[index] == '\t')) {
            //only skip spaces if not in a string
            if (!stringstatus) {
                index++;
                continue;
            }
            else {
                break;
            }
        }
        //ignore spaces again for recurssion
        while ((line[index] == ' ') or (line[index] == '\t')) {
            if (!stringstatus) {
                index++;
                continue;
            }
            else {
                break;
            }
        }
        
        //add to temptoken string
        temptoken += line[index];
        //if comment found
        if (line[index] == '"') {
            stringstatus = !stringstatus;
        }
        //move to next character if string
        if (stringstatus == true) {
            index++;
            continue;
        }
        //if at end of line
        if (index == line.size() - 1) {
            //get next line
            if (getline(cin, line)) {
                linenumber++;
                //ignore single line comment
                if (line.find("//") != string::npos) {
                    line = line.substr(0, line.find("//"));
                    line += '\r';
                }
            }
            index = 0;
            //return the generated token
            return temptoken;
        }
        //check the token table
        tokentype = tokens.find(temptoken);
        string tmp;
        tmp += line[index + 1];
        //token is found from the token
        if (tokentype != "NULL") {
            index++;
            return temptoken;
        }
        //if character seperated by a space, must have a token
        else if (tokentype == "NULL") {
            if ((line[index + 1] == ' ') or (tokens.find(tmp) != "NULL") or (index == line.size() - 1)) {
                index++;
                return temptoken;
            }
        }
        index++;
    }
    //get next line
    if (getline(cin, line)) {
        linenumber++;
        //ignore single line comments
        if (line.find("//") != string::npos) {
            line = line.substr(0, line.find("//"));
            line += '\r';
        }
        //line is empty
        return "Empty";
    }
    //end of file
    else {
        return "NULL";
    }
    //if no output, return error
    std::cerr << "error in token getter";
    return "error";
}
