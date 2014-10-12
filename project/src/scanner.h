/* Just a small meaningless comment */
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
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
	 std::string lexeme;
	 Token* next;
   Token(tokenType, std::string, Token*);
   void setToken(tokenType, std::string, Token*);
};

//Token constructor
Token::Token (tokenType _term, std::string _lex, Token* _next) {
	setToken(_term,_lex,_next);
};

//Token set members
void Token::setToken(tokenType inTerm, std::string inLex, Token* inNext){
     terminal = inTerm;
     lexeme = inLex;
     next = inNext;
};


class Scanner{
      public:
	Token *scan (const char *);
};
Scanner::scanner()
#endif /* SCANNER_H */
