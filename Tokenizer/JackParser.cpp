#include <iostream>
#include <stdlib.h>
#include "myxml.h"
#include "Tokenfinder.h"
#include "ParserTokens.h"
#include "Tokens.h"
using namespace std;

//storing the token and its type
string token = "?";
string tokentemp = "?";
//object creation
Tokenfinder tokeniser;
ParserTokens tokens;
Tokens tokenisertokens;
myxml xmlBuilder;

// XML node creation for the current token
void nodeBuilder()
{
    //store the current token
    string temptoken = tokentemp;
    // Check the token map
    string tokentype = tokenisertokens.find(temptoken);
    if (tokentype != "NULL") {
        xmlBuilder.addnode(tokentype);
        xmlBuilder.addcontent(temptoken);
        xmlBuilder.closenode(tokentype);
    }
    //Build the token type node
    else if (temptoken != "Empty") {
    // String constant
        if (temptoken[0] == '"') {
            temptoken = temptoken.substr(1, temptoken.size() - 2);
            xmlBuilder.addnode("stringConstant");
            xmlBuilder.addcontent(temptoken);
            xmlBuilder.closenode("stringConstant");
        }
    //Integer Constant
        else if (isdigit(temptoken[0])) {
            xmlBuilder.addnode("integerConstant");
            xmlBuilder.addcontent(temptoken);
            xmlBuilder.closenode("integerConstant");
        }
    //Identifier
        else {
            xmlBuilder.addnode("identifier");
            xmlBuilder.addcontent(temptoken);
            xmlBuilder.closenode("identifier");
        }
    }
}

//Get the token type using the token map
void getType()
{
    //Do nothing if the token is in the map
    if (tokens.find(tokentemp) != "NULL") {
        token = tokentemp;
    }
    //Convert the token to an identifier, string or integer       
    if ((tokentemp != "Empty") && (tokens.find(tokentemp) == "NULL")) {

        if (tokentemp[0] == '"') {
            tokentemp = tokentemp.substr(1, tokentemp.size() - 2);

            token = "stringConstant";
        }
        else if (isdigit(tokentemp[0])) {
            token = "integerConstant";
        }
        else {
            token = "identifier";
        }
    }
}

//Get the next token using the token finder class.
void nextToken()
{
    //Store the next token
    tokentemp = tokeniser.getNextToken();
    //Ignore any wrong tokens
    while ((tokentemp[0] == '\r') or (tokentemp[0] == ' ') or (tokentemp == "Empty")) {
        tokentemp = tokeniser.getNextToken();
    }
    //Get the token type
    getType();
}

// If the token is expected, get the next token, otherwise throw error
void mustbe(string expected)
{
    //compare token and expected token
    if (expected != token) {
        cerr << "Syntax error on line: " << tokeniser.linenumber << ", expected: " << expected << ", found " << token << "!" << endl;
        exit(-1);
    }
    //build xml nodes
    nodeBuilder();
    //get next token
    (void)nextToken();
}

// if we have the expected token return true
bool have(string expected)
{   
    //functions like mustbe, but doesnt move to next token
    if (expected != token)
        return false;
    return true;
}

// forward declare the parser functions
void parseProgram();
void parseDeclarations();
void parseStatement();
void parseWhileStatement();
void parseIfStatement();
void parseLetStatement();
void parseStatementSequence();
void parseExpression();
void parseCondition();
void parseTerm();
void getType();
void parseClass();
void parseFunction();
void parseParameters();
void parseSubroutineCall();
void parseSubroutineParameters();
void parseDo();
void parseReturn();
void nodeBuilder();
void parseExpressionList();
void parseConstructor();

// parsing the program
void parseProgram()
{
    //build class node and parse class
    xmlBuilder.addnode("class");
    mustbe("class");
    parseClass();
    xmlBuilder.closenode("class");
}

//parsing declarations
void parseDeclarations()
{
    //parse field declarations
    while (have("field")) {
        xmlBuilder.addnode("classVarDec");
        nodeBuilder();
        nextToken();
        //if the next token is an identifier, we have either ; or another identifer
        if (have("identifier")) {
            nodeBuilder();
            nextToken();
            if (have(";")) {
            }
            else {
                //second identifer
                if (have("identifier")) {
                    nodeBuilder();
                    nextToken();
                    //multiple variable names on one line
                    if (have(",")) {
                        mustbe("identifier");
                        while (have(",")) {
                            nodeBuilder();
                            nextToken();
                            mustbe("identifier");
                        }
                        //end of multiple variables
                        mustbe(";");
                    }
                    //only a single variable
                    else {
                        mustbe(";");
                    }
                }
            }
        }
        //next token must be a keyword, ie int or bool
        else {
            token = tokens.find(token);
            mustbe("keyword");
            mustbe("identifier");
            if (have(";")) {
                nodeBuilder();
                nextToken();
            }
            //multiple variable declarations
            else {
                if (have(",")) {
                    nodeBuilder();
                    nextToken();
                    mustbe("identifier");
                    //more than two
                    while (have(",")) {
                        nodeBuilder();
                        nextToken();
                        mustbe("identifier");
                    }
                    //end multiple variables
                    mustbe(";");
                }
                //only one variable declared
                else {
                    mustbe(";");
                }
            }
        }
        //end variable declarations
        xmlBuilder.closenode("classVarDec");
    }
    //parse non field variable declarations
    while (have("var")) {
        xmlBuilder.addnode("varDec");
        nodeBuilder();
        nextToken();
        //if the next token is an identifier
        if (have("identifier")) {
            nodeBuilder();
            nextToken();
            //if end of variables
            if (have(";")) {
            }
            else {
                //second identifer
                if (have("identifier")) {
                    nodeBuilder();
                    nextToken();
                    //multiple variables
                    if (have(",")) {
                        mustbe("identifier");
                        while (have(",")) {
                            nodeBuilder();
                            nextToken();
                            mustbe("identifier");
                        }
                        //end of multiple variables
                        mustbe(";");
                    }
                    //only a single variable
                    else {
                        mustbe(";");
                    }
                }
            }
        }
        //next token must be a keyword
        else {
            token = tokens.find(token);
            mustbe("keyword");
            mustbe("identifier");
            if (have(";")) {
                nodeBuilder();
                nextToken();
            }
            //multiple variables
            else {
                if (have(",")) {
                    nodeBuilder();
                    nextToken();
                    mustbe("identifier");
                    //more than two variables
                    while (have(",")) {
                        nodeBuilder();
                        nextToken();
                        mustbe("identifier");
                    }
                    mustbe(";");
                }
                else {
                    mustbe(";");
                }
            }
        }
        //end variable declarations
        xmlBuilder.closenode("varDec");
    }
}

//statement parsing
void parseStatement()
{
    //do statements
    if (have("do")) {
        //build nodes and parse
        xmlBuilder.addnode("doStatement");
        nodeBuilder();
        nextToken();
        parseDo();
        //close nodes
        xmlBuilder.closenode("doStatement");
    }
    //return statements
    else if (have("return")) {
        //build nodes and parse
        xmlBuilder.addnode("returnStatement");
        nodeBuilder();
        nextToken();
        parseReturn();
        //close nodes
        xmlBuilder.closenode("returnStatement");
    }
    //while statements
    else if (have("while")) {
        //build nodes and parse
        xmlBuilder.addnode("whileStatement");
        nodeBuilder();
        nextToken();
        parseWhileStatement();
        //close nodes
        xmlBuilder.closenode("whileStatement");
    }
    //if statements
    else if (have("if")) {
        //build nodes and parse
        xmlBuilder.addnode("ifStatement");
        nodeBuilder();
        nextToken();
        parseIfStatement();
        //close nodes
        xmlBuilder.closenode("ifStatement");
    }
    //let statements
    else if (have("let")) {
        //build nodes and parse
        xmlBuilder.addnode("letStatement");
        nodeBuilder();
        nextToken();
        parseLetStatement();
        //close nodes
        xmlBuilder.closenode("letStatement");
    }
    //mustbe a statement sequence
    else {
        mustbe("{");
        parseStatementSequence();
        mustbe("}");
    }
}

//parsing while statement
void parseWhileStatement()
{
    //pasrse conditions
    mustbe("(");
    parseCondition();
    mustbe(")");
    mustbe("{");
    //statementsequence
    parseStatementSequence();
    mustbe("}");
}

//parsing if statements 
void parseIfStatement()
{
    //parse conditions
    mustbe("(");
    parseCondition();
    mustbe(")");
    mustbe("{");
    //statement sequence
    parseStatementSequence();
    //if theres an else statement parse sequence
    if (have("else")) {
        parseStatementSequence();
    }
    //end if statement
    mustbe("}");
}

//parsing let
void parseLetStatement()
{
    //look for identifier
    mustbe("identifier");
    //array accesing
    if (have("[")) {
        nodeBuilder();
        nextToken();
        //parse expression
        parseExpression();
        mustbe("]");
        mustbe("=");
    }
    //look for =
    else {
        mustbe("=");
    }
    //end let 
    parseExpression();
    mustbe(";");
}

//parsing statementsequence
void parseStatementSequence()
{   
    //build node
    xmlBuilder.addnode("statements");
    //keep parsing until end
    while (token != "}") {
        parseStatement();
    }
    //close node
    xmlBuilder.closenode("statements");
}

//parsing expression
void parseExpression()
{
    //build node
    xmlBuilder.addnode("expression");
    //do nothing if no terms
    if (have(")")) {
    }
    else {
        parseTerm();
    }
    string whilestring = token;
    //parseterm if an operation is found
    while (have("relop")) {
        nodeBuilder();
        nextToken();
        parseTerm();
    }
    //build node
    token = tokentemp;
    xmlBuilder.closenode("expression");
}

//parsing conditions
void parseCondition()
{
    parseExpression();
}

//parsing terms
void parseTerm()
{
    //build node
    xmlBuilder.addnode("term");
    //identifiers
    if (have("identifier")) {
        nodeBuilder();
        nextToken();
        //array accesing
        if (have("[")) {
            nodeBuilder();
            nextToken();
            xmlBuilder.addnode("expression");
            xmlBuilder.addnode("term");
            //build node
            if (have("identifier")) {
                nodeBuilder();
                nextToken();
            }
            //mustbe an index
            else {
                mustbe("integerConstant");
            }
            //close nodes
            xmlBuilder.closenode("term");
            xmlBuilder.closenode("expression");
            mustbe("]");
        }
        //function calls 
        if ((have(".")) or (have("("))) {
            nodeBuilder();
            nextToken();
            mustbe("identifier");
            //parse the function call
            parseSubroutineCall();
            xmlBuilder.closenode("term");
        }
        //check for operartion
        else {
            xmlBuilder.closenode("term");
            tokentemp = token;
            token = tokens.find(token);
            if (have("op")) {

                nodeBuilder();
                nextToken();
                parseTerm();
            }
        }
    }
    //string handling
    else if (have("stringConstant")) {
        xmlBuilder.addnode("stringConstant");
        xmlBuilder.addcontent(tokentemp);
        xmlBuilder.closenode("stringConstant");
        nextToken();
        xmlBuilder.closenode("term");
    }
    //keyword handling
    else if (have("keyword")) {

        nodeBuilder();

        nextToken();
        xmlBuilder.closenode("term");
    }
    //integer handling
    else {
        mustbe("integerConstant");
        xmlBuilder.closenode("term");
    }
}

//parsing do
void parseDo()
{  
    //need identifier
    mustbe("identifier");
    //accesing function call
    if (have(".")) {
        nodeBuilder();
        nextToken();
        //need a method identifier
        mustbe("identifier");
        parseSubroutineCall();
    }
    //call subroutine
    else if (have("(")) {
        parseSubroutineCall();
    }
    //end do
    mustbe(";");
}

//parsing class
void parseClass()
{   
    //require class name
    mustbe("identifier");
    //open class 
    mustbe("{");
    //parsing variable declarations
    parseDeclarations();
    //parsing function declarations 
    while ((have("function")) or (have("constructor")) or (have("method"))) {
        //functions and methods are treated the same
        if ((have("function")) or (have("method"))) {
            xmlBuilder.addnode("subroutineDec");
            nodeBuilder();
            nextToken();
            //call the function parser
            parseFunction();
            xmlBuilder.closenode("subroutineDec");
        }
        //constructors have different functionality
        else {
            xmlBuilder.addnode("subroutineDec");
            nodeBuilder();
            nextToken();
            //call the constructor parser
            parseConstructor();
            xmlBuilder.closenode("subroutineDec");
        }
    }
    //parse declarations again
    parseDeclarations();
    //close the class
    mustbe("}");
}

//parsing functions
void parseFunction()
{
    //find the token type
    token = tokens.find(token);
    //mustbe a return type
    mustbe("keyword");
    mustbe("identifier");
    //parse parameter list
    mustbe("(");
    xmlBuilder.addnode("parameterList");
    parseParameters();
    xmlBuilder.closenode("parameterList");
    mustbe(")");
    //begin subroutine body
    xmlBuilder.addnode("subroutineBody");
    mustbe("{");
    //statements and declarations
    parseDeclarations();
    parseStatementSequence();
    mustbe("}");
    //close subroutineBody
    xmlBuilder.closenode("subroutineBody");
}

//parsing constructors
void parseConstructor()
{
    //require identifiers
    mustbe("identifier");
    mustbe("identifier");
    //parse parameterList
    mustbe("(");
    xmlBuilder.addnode("parameterList");
    parseParameters();
    xmlBuilder.closenode("parameterList");
    mustbe(")");
    //subroutineBody
    xmlBuilder.addnode("subroutineBody");
    mustbe("{");
    //declarations and statementsequence
    parseDeclarations();
    parseStatementSequence();
    mustbe("}");
    //close subroutine
    xmlBuilder.closenode("subroutineBody");
}

//parsing parameters
void parseParameters()
{   
    //check for paramters
    token = tokens.find(token);
    if (have("keyword")) {
        nodeBuilder();
        nextToken();
        mustbe("identifier");
    }
    //multiple parameter handling
    while (have(",")) {
        nodeBuilder();
        nextToken();
        token = tokens.find(token);
        mustbe("keyword");
        mustbe("identifier");
    }
    //reset token
    token = tokentemp;
}

//parsing subroutine parameters
void parseSubroutineParameters()
{
    parseExpressionList();
}

//parsing subroutine call
void parseSubroutineCall()
{
    mustbe("(");
    //do nothing if no parameters
    if (have(")")) {
        xmlBuilder.addnode("expressionList");
        xmlBuilder.closenode("expressionList");
        nodeBuilder();
        nextToken();
    }
    //parse parameters if parameters
    else {
        parseSubroutineParameters();
        mustbe(")");
    }
}

//parsing return
void parseReturn()
{
    //no value return
    if (have(";")) {
        nodeBuilder();
        nextToken();
    }
    //returning different values
    if (have("identifier")) {
        xmlBuilder.addnode("expression");
        xmlBuilder.addnode("term");
        nodeBuilder();
        xmlBuilder.closenode("term");
        xmlBuilder.closenode("expression");
        //end return
        nextToken();
        mustbe(";");
    }
    //integer return
    else if (have("integerConstant")) {
        nodeBuilder();
        nextToken();
        mustbe(";");
    }
    //keyword
    else if (have("keyword")) {
        //expression return
        parseExpression();
        nodeBuilder();
        nextToken();
        mustbe(";");
    }
}

//parsing expressionList
void parseExpressionList()
{
    //build expressionlist node
    xmlBuilder.addnode("expressionList");
    //parse the next expression
    parseExpression();
    //multiple expression parsing
    while (have(",")) {
        nodeBuilder();
        nextToken();
        parseExpression();
    }
    //close expressionList node
    xmlBuilder.closenode("expressionList");
}

// call parseProgram from here
int main()
{
    // call nextToken to initialise token
    nextToken();
    getType();
    // parse a Program
    parseProgram();
}
