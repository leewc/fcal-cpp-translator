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
   Token(char*, char*, Token*);
   void setToken(char*, char*, Token*);
};

//Token constructor
Token::Token (char* _term, char* _lex, Token* _next) {
	setToken(_term,_lex,_next);
};

//Token set members
void Token::setToken(char* inTerm, char* inLex, Token* inNext){
  //terminal = inTerm;
     lexeme = inLex;
     next = inNext;
     
     switch(inTerm)
       {
       case "intKwdReg":
	 terminal = intKwd;
	 break;
       case "floatKwdReg":
	 terminal = floatKwd;
	 break;
       case "stringKwdReg":
	 terminal = stringKwd;
	 break;
       case "matrixKwdReg":
	   terminal = matrixKwd;
       case "letKwd":
	   terminal = letKwd;
       case "inKwdReg":
	   terminal = inKwd;
       case "ifKwdReg":
	   terminal = ifKwd;
       case "thenKwdReg":
	   terminal = thenKwd;
       case "elseKwdReg":
	   terminal = elseKwd;
       case "forKwdReg":
	   terminal = forKwd;
       case "whileKwdReg":
	   terminal = whileKwd;
       case "printKwdReg":
	   terminal = printKwd;
       case "intConstReg":
	   terminal = intConst;
       case "floatConstReg":
	   terminal = floatConst;
       case "stringConstReg":
	   terminal = stringConst;
       case "variableNameReg":
	   terminal = variableName;
       case "leftParenReg":
	   terminal = leftParen;
       case "rightParenReg":
	   terminal = rightParen;
       case "leftCurlyReg":
	   terminal = leftCurly;
       case "rightCurlyReg":
	   terminal = rightCurly;
       case "leftSquareReg":
	   terminal = leftSquare;
       case "rightSquareReg":
	   terminal = rightSquare;
       case "commaReg":
	   terminal = comma;
       case "semicolonReg":
	   terminal = semiColon;
       case "colonReg":
	   terminal = colon;
       case "assignReg":
	   terminal = assign;
       case "plusSignReg":
	   terminal = plusSign;
       case "starReg":
	   terminal = star;
       case "dashReg":
	 terminal = dash;
       case "forwardSlashReg":
	 terminal = forwardSlash;
       case "lessThanReg":
	   terminal = lessThan;
       case "lessThanEqualReg":
	   terminal = lessThanEqual;
       case "greaterThanReg":
	   terminal = greaterThan;
       case "greaterThanEqualReg":
	   terminal = greaterThanEqual;
       case "equalsEqualsReg":
	   terminal = equalsEquals;
       case "notEqualsReg":
	   terminal = notEquals;
       case "andOpReg":
	   terminal = andOp;
       case "orOpReg":
	 terminal = orOp;
       case "notOpReg":
	 terminal = notOp;
       default:
	 
	 break;
       }
};


class Scanner{
	Token *scan (const char *);
};

Token* scanner(const char* text);
#endif /* SCANNER_H */
