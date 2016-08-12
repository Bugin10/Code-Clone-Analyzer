all: cppTokeniser JackParser

TOKENH=myxml.h Tokenfinder.h Tokens.h
TOKENCPP=cppTokeniser.cpp myxml.cpp Tokenfinder.cpp Tokens.cpp

cppTokeniser: ${TOKENCPP} ${TOKENH}
	g++ -o cppTokeniser ${TOKENCPP}
	
	
PARSERH=myxml.h Tokenfinder.h ParserTokens.h Tokens.h
PARSERCPP=JackParser.cpp Tokenfinder.cpp ParserTokens.cpp Tokens.cpp myxml.cpp

JackParser: ${PARSERCPP} ${PARSERH}
	g++ -o JackParser ${PARSERCPP}
    
clean:
	rm -f cppTokeniser JackParser