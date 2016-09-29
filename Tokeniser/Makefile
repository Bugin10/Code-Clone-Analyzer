all: cppTokeniser TokenComparer

TOKENH=myxml.h Tokenfinder.h Tokens.h
TOKENCPP=cppTokeniser.cpp myxml.cpp Tokenfinder.cpp Tokens.cpp

cppTokeniser: ${TOKENCPP} ${TOKENH}
	g++ -o cppTokeniser ${TOKENCPP}
	
TokenComparer: TokenComparer.cpp
	g++ -o TokenComparer TokenComparer.cpp
    
clean:
	rm -f cppTokeniser TokenComparer