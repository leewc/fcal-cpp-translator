/*Scanner will read in text and output a linked list of tokens
based on what was in the text. Each token will contain a string
copy of the original text (terminal), what type of token it is 
(tokenType), and a pointer to the next token in the list (next).
*/

#include <stdio.h>
#include <stlib.h>

#include "scanner.h"
#include "regex.h"

/*scanner will take in text in the form of char*s and return a
pointer to the top of the list.
*/
Token* scanner(const char* text){
	Token* head;
//first make all the regexes for each token type

	regex_t* intKwd;
	intKwd = makeRegex("^int");
	
	regex_t* floatKwd;
	floatKwd =  makeRegex("^float");
	
	regex_t* stringKwd;
	stringKwd = makeRegex("^string");
	
	regex_t* matrixKwd;
	matrixKwd = makeRegex("^matrix");
	
	regex_t* letKwd;
	letKwd = makeRegex("^let");
	
	regex_t* inKwd;
	inKwd = makeRegex("^in");
	
	regex_t* endKwd;
	endKwd = makeRegex("^end");
	
	regex_t* thenKwd;
	thenKwd = makeRegex("^then");
	
	regex_t* ifKwd;
	ifKwd = makeRegex("^if");
	
	regex_t* elseKwd;
	elseKwd = makeRegex("^else");
	
	regex_t* forKwd;
	forKwd = makeRegex("^for");
	
	regex_t* whileKwd;
	whileKwd = makeRegex("^while");
	
	regex_t* printKwd;
	printKwd = makeRegex("^print");
	
	regex_t*  assign;
	assign = makeRegex("^=");
	
	regex_t* plusSign;
	plusSign = makeRegex("^\\+");
	
	regex_t* star;
	star = makeRegex("^\\*");
	
	regex_t* dash;
	dash = makeRegex("^-");
	
	regex_t* forwardSlash;
	forwardSlash = makeRegex("^/");
	
	regex_t* lessThan;
	lessThan = makeRegex("^\\<");
	
	regex_t* lessThanEqual;
	lessThanEqual = makeRegex("^\\<=");
	
	regex_t* greaterThan;
	greaterThan = makeRegex("^\>");
	
	regex_t* greaterThanEqual;
	greaterThanEqual = makeRegex("^\>=");
	
	regex_t* equalsEquals;
	equalsEquals = makeRegex("^==");
	
	regex_t* notEqual;
	notEqual = makeRegex("^!=");
	
	regex_t* andOp;
	andOp = makeRegex("^&&");
	
	regex_t* orOp;
	orOp = makeRegex("^\\|\\|");
	
	regex_t* notOp;
	notOp = makeRegex("^!");

//now start looking at the text

//skip any initial whitespace

//try matching with regexes



}
