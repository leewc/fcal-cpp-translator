/*Scanner will read in text and output a linked list of tokens
based on what was in the text. Each token will contain a string
copy of the original text (terminal), what type of token it is
(tokenType), and a pointer to the next token in the list (next).
*/

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "regex.h"
#include "scanner.h"


//Token constructors
Token::Token(tokenType inTerm, const char* text, int matchedChars, Token* inNext){
	terminal = inTerm;
 	std::string newLex;
 	newLex.assign(text,matchedChars);
	lexeme = newLex;
	next = inNext;
}
Token::Token(tokenType inTerm, std::string inLex, Token* inNext){
	terminal = inTerm;
	lexeme = inLex;
	next = inNext;
}

Token::Token(const char* text, tokenType inTerm, Token* inNext){
	terminal = inTerm;
	std::string newLex;
	newLex.assign(text);
	lexeme = newLex;
	next = inNext;
}


//Scanner constructor that loads all the regexes.
Scanner::Scanner() {

    //allocates memory for all the regexArrays
    regArray = new regex_t [endOfFile];    	
    //Constants: Begin
    //stringConstReg = makeRegex ("^\"([a-z0-9A-Z\\_\\-]+)\"") ;
    // the below regex handles everything between the quotes even internal quotes -->//
    regArray[stringConst] = *makeRegex("^\"([^\"]|(\\\\\"))*\"");
    //stringConstReg = makeRegex("^\".*\"");
    regArray[intConst] = *makeRegex("^[0-9]+");
    regArray[floatConst] = *makeRegex ("^[0-9]+\\.[0-9]*");
    //Constants: End       
    regArray[variableName] = *makeRegex("^([a-zA-Z_])+[0-9a-zA-Z]*"); 
    //Punctuation: Begin
    regArray[leftParen] = *makeRegex ("^\\(");
    regArray[rightParen] = *makeRegex ("^\\)");
    regArray[leftCurly] = *makeRegex ("^\\{");
    regArray[rightCurly] = *makeRegex ("^\\}");
    regArray[leftSquare] = *makeRegex ("^\\[");
    regArray[rightSquare] = *makeRegex ("^\\]");
    regArray[comma] = *makeRegex ("^,");
    regArray[semiColon] = *makeRegex ("^;");
    regArray[colon] = *makeRegex ("^:");
    //FCAL types begin with capital
    regArray[intKwd]= *makeRegex("^Int");
    regArray[boolKwd] = *makeRegex ("^Bool");
    regArray[trueKwd] = *makeRegex ("^True");
    regArray[falseKwd] = *makeRegex ("^False");
    regArray[floatKwd] = *makeRegex("^Float");
    regArray[stringKwd] = *makeRegex("^Str");
    regArray[matrixKwd] = *makeRegex("^Matrix");
    regArray[letKwd] = *makeRegex("^let");
    regArray[inKwd] = *makeRegex("^in");
    regArray[endKwd] = *makeRegex("^end");
    regArray[thenKwd] = *makeRegex("^then");
    regArray[ifKwd] = *makeRegex("^if");
    regArray[elseKwd] = *makeRegex("^else");
    regArray[forKwd] = *makeRegex("^for");
    regArray[whileKwd] = *makeRegex("^while");
    regArray[printKwd] = *makeRegex("^print");
    regArray[assign] = *makeRegex("^=");
    regArray[plusSign] = *makeRegex("^\\+");	
    regArray[star] = *makeRegex("^\\*");
    regArray[dash] = *makeRegex("^-");
    regArray[forwardSlash] = *makeRegex("^/");
    regArray[lessThan] = *makeRegex("^<");
    regArray[lessThanEqual] = *makeRegex("^<=");
    regArray[greaterThan] = *makeRegex("^>");
    //previous regex was ^//>= which is wrong based on the forest bad syn good tokens test (same for <=)
    regArray[greaterThanEqual] = *makeRegex("^>=");
    regArray[equalsEquals] = *makeRegex("^==");
    regArray[notEquals] = *makeRegex("^!=");
    regArray[andOp] = *makeRegex("^&&");
    regArray[orOp] = *makeRegex("^\\|\\|");
    regArray[notOp] = *makeRegex("^!");

    filterArray = new regex_t [3];
    filterArray[0] = *makeRegex ("^[\n\t\r ]+") ;
    filterArray[1] = *makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    filterArray[2] = *makeRegex ("^//[^\n]*\n");
}

int Scanner::consumeWhiteSpaceAndComments(regex_t *whiteSpace,
								regex_t *blockComment,
								regex_t *lineComment,
								const char *text) {
	int numMatchedChars = 0 ;
	int totalNumMatchedChars = 0 ;
	int stillConsumingWhiteSpace ;

	do {
		stillConsumingWhiteSpace = 0 ; // exit loop if not reset by a match

		// Try to match white space
		numMatchedChars = matchRegex (whiteSpace, text) ;
		totalNumMatchedChars += numMatchedChars ;
		if (numMatchedChars > 0) {
			text = text + numMatchedChars ;
			stillConsumingWhiteSpace = 1 ;
		}

		// Try to match block comments
		numMatchedChars = matchRegex (blockComment, text) ;
		totalNumMatchedChars += numMatchedChars ;
		if (numMatchedChars > 0) {
			text = text + numMatchedChars ;
			stillConsumingWhiteSpace = 1 ;
		}

		// Try to match single-line comments
		numMatchedChars = matchRegex (lineComment, text) ;
		totalNumMatchedChars += numMatchedChars ;
		if (numMatchedChars > 0) {
			text = text + numMatchedChars ;
			stillConsumingWhiteSpace = 1 ;
		}
	}
	while ( stillConsumingWhiteSpace ) ;

	return totalNumMatchedChars ;
}

Token* Scanner::scan(const char* text){
    	
	Token* head = NULL;
	Token* tail = head;
	//now start looking at the text
    int numMatchedChars = 0;
	
    //skip any initial whitespace
    numMatchedChars = consumeWhiteSpaceAndComments(&filterArray[0], &filterArray[1], &filterArray[2], text);
    text = text + numMatchedChars;

    //try matching with regexes
    int maxNumMatchedChars = 0;
    enum tokenEnumType term;
	
	while ( text[0] != '\0' ) {
		maxNumMatchedChars = 0 ;
		term = lexicalError;
				

	//modify thisssss
		for(int i = 0; i < endOfFile; i++) 
		{
			numMatchedChars = matchRegex (&regArray[i], text);
			if (numMatchedChars > maxNumMatchedChars) {
				maxNumMatchedChars = numMatchedChars ;
				term = static_cast<tokenType>(i);
				//attempted typecast:http://www.dailycoding.com/Posts/enum_coversion_operations_int_to_enum_enum_to_int_string_to_enum_enum_to_string.aspx
			//std::cout<<"Found match. term is semicolon"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
			}
		}

		//printf("done matching\n");
		if(term == lexicalError){
		  //std::cout << "LEXICAL ERROR " << std::endl; printf("Text Matched: %.*s\n",1,text);
			maxNumMatchedChars = 1;
		}
		std::string lex (text, maxNumMatchedChars);
		//set current node
		Token* temp = new Token(term, lex, NULL);
		temp->terminal = term;
		temp->lexeme = lex;
		temp->next = NULL;
		if(head==NULL){
			head = temp;
		}
		else{
		  tail = head;
		  while(tail->next!=NULL){
		    tail = tail->next;
		  }
		  tail->next = temp;
		}
		text = text + maxNumMatchedChars;
		numMatchedChars = consumeWhiteSpaceAndComments(&filterArray[0], &filterArray[1], &filterArray[2], text);
		text = text + numMatchedChars;
	}
	//set end of file node
	std::string lex;
	Token* temp = new Token(endOfFile, lex, NULL);
	temp->terminal = endOfFile;
	temp->lexeme = lex;
	temp->next = NULL;
	if(head==NULL){
		head = temp;
	}
	else{
		tail = head;
    while(tail->next!=NULL){
    tail = tail->next;
    }
			tail->next = temp;
	
	}
	return head;
}
/* This is the site I based the linked list format off:
http://www.codeproject.com/Articles/24684/How-to-create-Linked-list-using-C-C
*/
