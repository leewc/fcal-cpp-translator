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
    
    //first make all the regexes for each token type
  //    regex_t* regArray[42];

  //tokenType* tokenArray[42];
 
  //int a = 0; //tracker for array
    
    regex_t* whiteSpace ;
    whiteSpace = makeRegex ("^[\n\t\r ]+") ;

    regex_t* blockCommentReg ;
    blockCommentReg = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    
    regex_t* lineCommentReg ;
    lineCommentReg = makeRegex ("^//[^\n]*\n");
	
    //Constants: Begin
    regex_t* stringConstReg ;
    //stringConstReg = makeRegex ("^\"([a-z0-9A-Z\\_\\-]+)\"") ;
    // the below regex handles everything between the quotes even internal quotes -->//
    stringConstReg = makeRegex("^\"([^\"]|(\\\\\"))*\"");
    //stringConstReg = makeRegex("^\".*\"");
    //regArray[a] = stringConstReg;
    //a++;

    regex_t* intConstReg;
    intConstReg = makeRegex("^[0-9]+");
    //regArray[a] = intConstReg;
    //a++;

    regex_t* floatConstReg ;

    floatConstReg = makeRegex ("^[0-9]+\\.[0-9]*");
    //regArray[a] = floatConstReg;
    //a++;
    //Constants: End
        
    regex_t* variableNameReg ;
    variableNameReg = makeRegex("^([a-zA-Z_])+[0-9a-zA-Z]*"); 
    //regArray[a] = variableNameReg;
    //a++;

    //Punctuation: Begin
    regex_t* leftParenReg;
    leftParenReg = makeRegex ("^\\(");
    //regArray[a] = leftParenReg;
    //a++;

    regex_t* rightParenReg;
    rightParenReg = makeRegex ("^\\)");
    //regArray[a] = rightParenReg;
    //a++;

    regex_t* leftCurlyReg;
    leftCurlyReg = makeRegex ("^\\{");
    //regArray[a] = leftCurlyReg;
    //a++;

    regex_t* rightCurlyReg;
    rightCurlyReg = makeRegex ("^\\}");
    //regArray[a] = rightCurlyReg;
    //a++;

    regex_t* leftSquareReg;
    leftSquareReg = makeRegex ("^\\[");
    //regArray[a] = leftSquareReg;
    //a++;

    regex_t* rightSquareReg;
    rightSquareReg = makeRegex ("^\\]");
    //regArray[a] = rightSquareReg;
    //a++;

    regex_t* commaReg;
    commaReg = makeRegex ("^,");
    //regArray[a] = commaReg;
    //a++;

    regex_t* semiColonReg;
    semiColonReg = makeRegex ("^;");
    //regArray[a] = semiColonReg;
    //a++;

    regex_t* colonReg;
    colonReg = makeRegex ("^:");
    //regArray[a] = colonReg;
    //a++;

    regex_t* intKwdReg;
    //FCAL types begin with capital
    intKwdReg = makeRegex("^Int");
    //regArray[a] = intKwdReg;	
    //a++;

    regex_t* boolKwdReg;
    boolKwdReg = makeRegex ("^Bool");

    regex_t* trueKwdReg;
    trueKwdReg = makeRegex ("^True");

    regex_t* falseKwdReg;
    falseKwdReg = makeRegex ("^False");

    regex_t* floatKwdReg;
    floatKwdReg = makeRegex("^Float");
    //regArray[a] = floatKwdReg;
    //a++;

    regex_t* stringKwdReg;
    stringKwdReg = makeRegex("^Str");
    //regArray[a] = stringKwdReg;
    //a++;

    regex_t* matrixKwdReg;
    matrixKwdReg = makeRegex("^Matrix");
    //regArray[a] = matrixKwdReg;
    //a++;

    regex_t* letKwdReg;
    letKwdReg = makeRegex("^let");
    //regArray[a] = letKwdReg;
    //a++;

    regex_t* inKwdReg;
    inKwdReg = makeRegex("^in");
    //regArray[a] = inKwdReg;
    //a++;

    regex_t* endKwdReg;
    endKwdReg = makeRegex("^end");
    //regArray[a] = endKwdReg;
    //a++;

    regex_t* thenKwdReg;
    thenKwdReg = makeRegex("^then");
    //regArray[a] = thenKwdReg;
    //a++;

    regex_t* ifKwdReg;
    ifKwdReg = makeRegex("^if");
    //regArray[a] = ifKwdReg;
    //a++;

    regex_t* elseKwdReg;
    elseKwdReg = makeRegex("^else");
    //regArray[a] = elseKwdReg;
    //a++;

    regex_t* forKwdReg;
    forKwdReg = makeRegex("^for");
    //regArray[a] = forKwdReg;	
    //a++;

    regex_t* whileKwdReg;
    whileKwdReg = makeRegex("^while");
    //regArray[a] = whileKwdReg;	
    //a++;

    regex_t* printKwdReg;
    printKwdReg = makeRegex("^print");
    //regArray[a] = printKwdReg;	
    //a++;

    regex_t* assignReg;
    assignReg = makeRegex("^=");
    //regArray[a] = assignReg;	
    //a++;

    regex_t* plusSignReg;
    plusSignReg = makeRegex("^\\+");
    //regArray[a] = plusSignReg;	
    //a++;

    regex_t* starReg;
    starReg = makeRegex("^\\*");
    //regArray[a] = starReg;	
    //a++;

    regex_t* dashReg;
    dashReg = makeRegex("^-");
    //regArray[a] = dashReg;	
    //a++;

    regex_t* forwardSlashReg;
    forwardSlashReg = makeRegex("^/");
    //regArray[a] = forwardSlashReg;	
    //a++;

    regex_t* lessThanReg;
    lessThanReg = makeRegex("^<");
    //regArray[a] = lessThanReg;	
    //a++;

    regex_t* lessThanEqualReg;
    lessThanEqualReg = makeRegex("^<=");
    //regArray[a] = lessThanEqualReg;	
    //a++;

    regex_t* greaterThanReg;
    greaterThanReg = makeRegex("^>");
    //regArray[a] = greaterThanReg;	
    //a++;

    regex_t* greaterThanEqualReg;
    //previous regex was ^//>= which is wrong based on the forest bad syn good tokens test (same for <=)
    greaterThanEqualReg = makeRegex("^>=");
    //regArray[a] = greaterThanEqualReg;	
    //a++;

    regex_t* equalsEqualsReg;
    equalsEqualsReg = makeRegex("^==");
    //regArray[a] = equalsEqualsReg;	
    //a++;

    regex_t* notEqualsReg;
    notEqualsReg = makeRegex("^!=");
    //regArray[a] = notEqualsReg;	
    //a++;

    regex_t* andOpReg;
    andOpReg = makeRegex("^&&");
    //regArray[a] = andOpReg;	
    //a++;

    regex_t* orOpReg;
    orOpReg = makeRegex("^\\|\\|");
    //regArray[a] = orOpReg;
    //a++;

    regex_t* notOpReg;
    notOpReg = makeRegex("^!");
    //regArray[a] = notOpReg;
    //a++;
	
	Token* head = NULL;
	Token* tail = head;
	//now start looking at the text
    int numMatchedChars = 0;
	
    //skip any initial whitespace
    numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockCommentReg, lineCommentReg, text);
    text = text + numMatchedChars;

    //try matching with regexes
    int maxNumMatchedChars = 0;
    enum tokenEnumType term;
	
	while ( text[0] != '\0' ) {
		maxNumMatchedChars = 0 ;
		term = lexicalError;
		
		

		numMatchedChars = matchRegex (intKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = intKwd;
		  //			std::cout<<"Found match. term is intkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (stringConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = stringConst;
			//std::cout<<"Found match. term is strconst"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (floatConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = floatConst;
			//std::cout<<"Found match. term is floatconst"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (floatKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = floatKwd;
			//std::cout<<"Found match. term is floatkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (stringKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = stringKwd;
			//std::cout<<"Found match. term is stringkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}	
		numMatchedChars = matchRegex (boolKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = boolKwd;
			//std::cout<<"Found match. term is boolkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}	
		numMatchedChars = matchRegex (trueKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = trueKwd;
			//std::cout<<"Found match. term is truekwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}	
		numMatchedChars = matchRegex (falseKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = falseKwd;
			//std::cout<<"Found match. term is falsekwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}	
		numMatchedChars = matchRegex (matrixKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = matrixKwd;
			//std::cout<<"Found match. term is matrixkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (intConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = intConst;
			//std::cout<<"Found match. term is intconst " <<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (letKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = letKwd;
			//std::cout<<"Found match. term is letkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (inKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = inKwd;
			//std::cout<<"Found match. term is INkwd"<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (endKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = endKwd;
			//std::cout<<"Found match. term is endKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (ifKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = ifKwd;
			//std::cout<<"Found match. term is ifKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (thenKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = thenKwd;
			//std::cout<<"Found match. term is thenKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (elseKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = elseKwd;
			//std::cout<<"Found match. term is elseKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (forKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = forKwd;
			//std::cout<<"Found match. term is forKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (whileKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = whileKwd;
			//std::cout<<"Found match. term is whileKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (printKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = printKwd;
			//std::cout<<"Found match. term is printKwd"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}

		numMatchedChars = matchRegex (leftParenReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftParen;
			//std::cout<<"Found match. term is leftparen"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (rightParenReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightParen;
			//std::cout<<"Found match. term is rightParen"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (leftCurlyReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftCurly;
			//std::cout<<"Found match. term is leftCurl"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (rightCurlyReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightCurly;
			//std::cout<<"Found match. term is rightCurl"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (leftSquareReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftSquare;
			//std::cout<<"Found match. term is leftSquare"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (rightSquareReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightSquare;
			//std::cout<<"Found match. term is rightSquare"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (commaReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = comma;
			//std::cout<<"Found match. term is comma"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (semiColonReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = semiColon;
			//std::cout<<"Found match. term is semicolon"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (colonReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = colon;
			//std::cout<<"Found match. term is colon"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (assignReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = assign;
			//std::cout<<"Found match. term is assign"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (plusSignReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = plusSign;
			//std::cout<<"Found match. term is plus"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (starReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = star;
			//std::cout<<"Found match. term is star"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (dashReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = dash;
			//std::cout<<"Found match. term is dash"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (forwardSlashReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = forwardSlash;
			//std::cout<<"Found match. term is forwardslash"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (lessThanReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = lessThan;
			//std::cout<<"Found match. term is lessthan"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (lessThanEqualReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = lessThanEqual;
			//std::cout<<"Found match. term is lessthanEQ"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (greaterThanReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = greaterThan;
			//	std::cout<<"Found match. term is greaterthan"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (greaterThanEqualReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = greaterThanEqual;
			//std::cout<<"Found match. term is greaterthanEQ"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (equalsEqualsReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = equalsEquals;
			//	std::cout<<"Found match. term is EQEQ"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (notEqualsReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = notEquals;
			//std::cout<<"Found match. term is notEQ"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (andOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = andOp;
			//std::cout<<"Found match. term is andOP"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (orOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = orOp;
			//std::cout<<"Found match. term is orOP"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
		numMatchedChars = matchRegex (notOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = notOp;
			//std::cout<<"Found match. term is notOP "<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
		}
   
   numMatchedChars = matchRegex (variableNameReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = variableName;
			//std::cout<<"Found match. term is varName"<<term<<std::endl; printf("Text matched: %.*s\n",numMatchedChars,text);
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
		numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockCommentReg, lineCommentReg, text);
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
