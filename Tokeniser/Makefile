all: cppTokeniser

TOKENH=myxml.h Tokenfinder.h Tokens.h
TOKENCPP=cppTokeniser.cpp myxml.cpp Tokenfinder.cpp Tokens.cpp

cppTokeniser: ${TOKENCPP} ${TOKENH}
	g++ -o cppTokeniser ${TOKENCPP}
	
    
clean:
	rm -f cppTokeniser JackParser