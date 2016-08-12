all: JackTokeniser JackParser

TOKENH=myxml.h Tokenfinder.h Tokens.h
TOKENCPP=JackTokeniser.cpp myxml.cpp Tokenfinder.cpp Tokens.cpp

JackTokeniser: ${TOKENCPP} ${TOKENH}
	g++ -o JackTokeniser ${TOKENCPP}
	
	
PARSERH=myxml.h Tokenfinder.h ParserTokens.h Tokens.h
PARSERCPP=JackParser.cpp Tokenfinder.cpp ParserTokens.cpp Tokens.cpp myxml.cpp

JackParser: ${PARSERCPP} ${PARSERH}
	g++ -o JackParser ${PARSERCPP}
    
clean:
	rm -f JackTokeniser JackParser