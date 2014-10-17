/* A small meaningless comment */
#ifndef SCANNER_H
#define SCANNER_H

#include <regex.h>
#include <string>

/* This enumerated type is used to keep track of what kind of
construct was matched.
*/

enum tokenEnumType {

        intKwd, floatKwd, boolKwd, 
        trueKwd, falseKwd, stringKwd, matrixKwd,
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
// Token class
class Token { //Can add more fields later
	public:
	tokenType terminal;
	std::string lexeme;
	Token* next;
  	Token(tokenType, const char*, int, Token*);
	Token(tokenType, std::string, Token*);
	Token();
 	Token (const char*,tokenType, Token*) ;
};

/*/Token constructor
Token::Token(tokenType inTerm, std::string inLex, Token* inNext){
	terminal = inTerm;
	lexeme = inLex;
	next = inNext;
}*/

//Scanner class
class Scanner {
	public:
	int consumeWhiteSpaceAndComments(regex_t*, regex_t*, regex_t*, const char*);
	Token* scan(const char*);
};

int consumeWhiteSpaceAndComments(regex_t *whiteSpace,regex_t *blockComment, regex_t *lineComment,const char *text);

Token* scan(const char* text);

#endif /* SCANNER_H */
