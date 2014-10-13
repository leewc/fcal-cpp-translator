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


//Token constructor
Token::Token(tokenType inTerm, std::string inLex, Token* inNext){
	terminal = inTerm;
	lexeme = inLex;
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
    regex_t* regArray[42];

    tokenType* tokenArray[42];
 
    int a = 0; //tracker for array
    
    regex_t* whiteSpace ;
    whiteSpace = makeRegex ("^[\n\t\r ]+") ;

    regex_t* blockCommentReg ;
    blockCommentReg = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    
    regex_t* lineCommentReg ;
    lineCommentReg = makeRegex ("^//[^\n]*\n");
	
    //TODO: we need these REGEXes: variableName, lexicalError, endOfFile (note: also modify constructor).
    //Constants: Begin
    regex_t* stringConstReg ;
    stringConstReg = makeRegex ("^\"([a-z0-9A-Z]+)\"") ;
    regArray[a] = stringConstReg;
    a++;

    regex_t* intConstReg;
    intConstReg = makeRegex("^[0-9]*");
    regArray[a] = intConstReg;
    a++;

    regex_t* floatConstReg ;

    floatConstReg = makeRegex ("^[0-9]+\\.[0-9]*");
    regArray[a] = floatConstReg;
    a++;
    //Constants: End
        
    //Punctuation: Begin
    regex_t* leftParenReg;
    leftParenReg = makeRegex ("^\\(");
    regArray[a] = leftParenReg;
    a++;

    regex_t* rightParenReg;
    rightParenReg = makeRegex ("^\\)");
    regArray[a] = rightParenReg;
    a++;

    regex_t* leftCurlyReg;
    leftCurlyReg = makeRegex ("^\\{");
    regArray[a] = leftCurlyReg;
    a++;

    regex_t* rightCurlyReg;
    rightCurlyReg = makeRegex ("^\\{");
    regArray[a] = rightCurlyReg;
    a++;

    regex_t* leftSquareReg;
    leftSquareReg = makeRegex ("^\\[");
    regArray[a] = leftSquareReg;
    a++;

    regex_t* rightSquareReg;
    rightSquareReg = makeRegex ("^\\]");
    regArray[a] = rightSquareReg;
    a++;

    regex_t* commaReg;
    commaReg = makeRegex ("^,");
    regArray[a] = commaReg;
    a++;

    regex_t* semiColonReg;
    semiColonReg = makeRegex ("^;");
    regArray[a] = semiColonReg;
    a++;

    regex_t* colonReg;
    colonReg = makeRegex ("^:");
    regArray[a] = colonReg;
    a++;

    regex_t* intKwdReg;
    intKwdReg = makeRegex("^int");
    regArray[a] = intKwdReg;	
    a++;

    regex_t* floatKwdReg;
    floatKwdReg = makeRegex("^float");
    regArray[a] = floatKwdReg;
    a++;

    regex_t* stringKwdReg;
    stringKwdReg = makeRegex("^string");
    regArray[a] = stringKwdReg;
    a++;

    regex_t* matrixKwdReg;
    matrixKwdReg = makeRegex("^matrix");
    regArray[a] = matrixKwdReg;
    a++;

    regex_t* letKwdReg;
    letKwdReg = makeRegex("^let");
    regArray[a] = letKwdReg;
    a++;

    regex_t* inKwdReg;
    inKwdReg = makeRegex("^in");
    regArray[a] = inKwdReg;
    a++;

    regex_t* endKwdReg;
    endKwdReg = makeRegex("^end");
    regArray[a] = endKwdReg;
    a++;

    regex_t* thenKwdReg;
    thenKwdReg = makeRegex("^then");
    regArray[a] = thenKwdReg;
    a++;

    regex_t* ifKwdReg;
    ifKwdReg = makeRegex("^if");
    regArray[a] = ifKwdReg;
    a++;

    regex_t* elseKwdReg;
    elseKwdReg = makeRegex("^else");
    regArray[a] = elseKwdReg;
    a++;

    regex_t* forKwdReg;
    forKwdReg = makeRegex("^for");
    regArray[a] = forKwdReg;	
    a++;

    regex_t* whileKwdReg;
    whileKwdReg = makeRegex("^while");
    regArray[a] = whileKwdReg;	
    a++;

    regex_t* printKwdReg;
    printKwdReg = makeRegex("^print");
    regArray[a] = printKwdReg;	
    a++;

    regex_t* assignReg;
    assignReg = makeRegex("^=");
    regArray[a] = assignReg;	
    a++;

    regex_t* plusSignReg;
    plusSignReg = makeRegex("^\\+");
    regArray[a] = plusSignReg;	
    a++;

    regex_t* starReg;
    starReg = makeRegex("^\\*");
    regArray[a] = starReg;	
    a++;

    regex_t* dashReg;
    dashReg = makeRegex("^-");
    regArray[a] = dashReg;	
    a++;

    regex_t* forwardSlashReg;
    forwardSlashReg = makeRegex("^/");
    regArray[a] = forwardSlashReg;	
    a++;

    regex_t* lessThanReg;
    lessThanReg = makeRegex("^\\<");
    regArray[a] = lessThanReg;	
    a++;

    regex_t* lessThanEqualReg;
    lessThanEqualReg = makeRegex("^\\<=");
    regArray[a] = lessThanEqualReg;	
    a++;

    regex_t* greaterThanReg;
    greaterThanReg = makeRegex("^\\>");
    regArray[a] = greaterThanReg;	
    a++;

    regex_t* greaterThanEqualReg;
    greaterThanEqualReg = makeRegex("^\\>=");
    regArray[a] = greaterThanEqualReg;	
    a++;

    regex_t* equalsEqualsReg;
    equalsEqualsReg = makeRegex("^==");
    regArray[a] = equalsEqualsReg;	
    a++;

    regex_t* notEqualsReg;
    notEqualsReg = makeRegex("^!=");
    regArray[a] = notEqualsReg;	
    a++;

    regex_t* andOpReg;
    andOpReg = makeRegex("^&&");
    regArray[a] = andOpReg;	
    a++;

    regex_t* orOpReg;
    orOpReg = makeRegex("^\\|\\|");
    regArray[a] = orOpReg;
    a++;

    regex_t* notOpReg;
    notOpReg = makeRegex("^!");
    regArray[a] = notOpReg;
    a++;
	
	Token* head =NULL;
	//now start looking at the text
    int numMatchedChars = 0;
	
    //skip any initial whitespace
    numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockCommentReg, lineCommentReg, text);
    text = text + numMatchedChars;

    //try matching with regexes
    int maxNumMatchedChars = 0;
    enum tokenEnumType term;
    std::string lex;
	while ( text[0] != '\0' ) {
		maxNumMatchedChars = 0 ;
		term = lexicalError;
		
				numMatchedChars = matchRegex (intKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = intKwd;
			lex.assign(text,numMatchedChars); 
      
      std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (stringConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = stringConst;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (intConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = intConst;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (floatConstReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = floatConst;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (floatKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = floatKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (stringKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = stringKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (matrixKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = matrixKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (letKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = letKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (inKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = inKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (endKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = endKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (ifKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = ifKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (thenKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = thenKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (elseKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = elseKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (forKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = forKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (whileKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = whileKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (printKwdReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = printKwd;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (leftParenReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftParen;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (rightParenReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightParen;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (leftCurlyReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftCurly;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (rightCurlyReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightCurly;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (leftSquareReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = leftSquare;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (rightSquareReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = rightSquare;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (commaReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = comma;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (semiColonReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = semiColon;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (colonReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = colon;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (assignReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = assign;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (plusSignReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = plusSign;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (starReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = star;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (dashReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = dash;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (forwardSlashReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = forwardSlash;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (lessThanReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = lessThan;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (lessThanEqualReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = lessThanEqual;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (greaterThanReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = greaterThan;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (greaterThanEqualReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = greaterThanEqual;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (equalsEqualsReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = equalsEquals;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (notEqualsReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = notEquals;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (andOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = andOp;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (orOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = orOp;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		numMatchedChars = matchRegex (notOpReg, text);
		if (numMatchedChars > maxNumMatchedChars) {
			maxNumMatchedChars = numMatchedChars ;
			term = notOp;
			lex.assign(text,numMatchedChars); std::cout<<"Found match. term is "<<term<<" lex is "<<lex;
		}
		
		
		//Token *current;
		//Token aToken = Token (term, lex, NULL);

		//an example of making an intKwd, snce we have an array of regex, we can have an array of strings that correspond to the array of regexes (e.g. regArray[0] is intKwdreg and strArray[0] is intKwdReg, then put it all in a for loop, hopefully?
   if(term == lexicalError){
   lex.assign(text,1);
			text = text + 1;
		}
		else{
			text = text + maxNumMatchedChars;
		}
   
		if(head == NULL) {
    Token temp (term, lex, NULL);//= (Token*)malloc(sizeof(Token));
      head = &temp;
		}
		else {
		Token *current;// = (Token*)malloc(sizeof(Token));
   current = head;
   while(current->next!=NULL){
   current = current->next;
   }
   Token temp (term, lex, NULL);//= (Token*)malloc(sizeof(Token));
   current->next = &temp;
   }
		
		
		numMatchedChars = consumeWhiteSpaceAndComments(whiteSpace, blockCommentReg, lineCommentReg, text);
		text = text + numMatchedChars;
	}
 if(head == NULL){
 Token temp (endOfFile, "\0", NULL);//= (Token*)malloc(sizeof(Token));
 head = &temp;
 //head->terminal = endOfFile;
 }
 else {
 Token *lastToken;// = (Token*)malloc(sizeof(Token));
 lastToken = head;
 while(lastToken->next!=NULL){
 lastToken = lastToken->next;
 }
 Token temp (endOfFile, "\0", NULL);// = (Token*)malloc(sizeof(Token));
   lastToken->next = &temp;
   }
	return head;
}