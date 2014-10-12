/* Just a small meaningless comment */
#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string.h>
#include "regex.h"
#include <regex.h>

/* This enumerated type is used to keep track of what kind of
   construct was matched. 
 */

enum tokenEnumType { 

	intKwd, floatKwd,  stringKwd, matrixKwd,
	letKwd, inKwd, endKwd, ifKwd, thenKwd, elseKwd,
	forKwd, whileKwd, printKwd,

	// Constants
	intConst, floatConst, stringConst, 

	// Names
	variableName ,

	// Punctuation
	leftParen, rightParen, 
	leftCurly, rightCurly, 
	leftSquare, rightSquare,

	comma, semiColon, colon,

	//Operators
	assign, 
	plusSign, star, dash, forwardSlash,
	lessThan, lessThanEqual, greaterThan, greaterThanEqual,
	equalsEquals, notEquals,
	andOp, orOp, notOp,

	// Special terminal types
	endOfFile ,
	lexicalError
} ;
typedef enum tokenEnumType tokenType ;

// Below you need to write your class definitions for Token and Scanner.

class Token { //Can add more fields later
	public:
	 tokenType terminal;
	 char* lexeme;
	 Token* next;
   Token(tokenType, char*, Token*);
   void setToken(tokenType, char*, Token*);
};

//Token constructor
Token::Token (tokenType _term, char* _lex, Token* _next) {
	setToken(_term,_lex,_next);
};

//Token set members
void Token::setToken(tokenType inTerm, char* inLex, Token* inNext){
     terminal = inTerm;
     lexeme = inLex;
     next = inNext;
};


class Scanner{
	Token *scan (const char *);
};

Token* scanner(const char* text);
#endif /* SCANNER_H */
