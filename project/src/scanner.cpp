/*Scanner will read in text and output a linked list of tokens
based on what was in the text. Each token will contain a string
copy of the original text (terminal), what type of token it is 
(tokenType), and a pointer to the next token in the list (next).
*/

#include <stdio.h>
//Lee: the previous version had stlib.h! typo made me not compile xD
#include <stdlib.h>

//included the string header or else C++ doesn't support strings
#include <string>

#include "scanner.h"
#include "regex.h"


//placed on top or else scan cannot find it
//copied from WordCount, adapted to not consume comments
int consumeWhiteSpace(regex_t *whiteSpace, 
                                  const char *text) {
  int numMatchedChars = 0 ;
  int totalNumMatchedChars = 0 ;
  int stillConsumingWhiteSpace ;

  do {
    stillConsumingWhiteSpace = 0 ;  // exit loop if not reset by a match
    // Try to match white space
    numMatchedChars = matchRegex (whiteSpace, text) ;
    totalNumMatchedChars += numMatchedChars ;
    if (numMatchedChars > 0) {
      text = text + numMatchedChars ;
      stillConsumingWhiteSpace = 1 ;
    }
  }
  while ( stillConsumingWhiteSpace ) ;    

  return totalNumMatchedChars ;
}



/*scanner will take in text in the form of char*s and return a
pointer to the top of the list.
*/
Token* scanner(const char* text){
    Token* head;
    
    //first make all the regexes for each token type
    regex_t* regArray[42];
    tokenType* tokenArray[42];
    tokenType t;

    regex_t* whiteSpace ;
    whiteSpace = makeRegex ("^[\n\t\r ]+") ;
    regArray[0] = whiteSpace;
    tokenArray[0] = t;

    regex_t* blockComment ;
    blockComment = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");
    regArray[1] = blockComment;
    tokenArray[1] = t.blockComment;

    regex_t* lineComment ;
    lineComment = makeRegex ("^//[^\n]*\n");
    regArray[2] = lineComment;
    tokenArray[2] = t.lineComment;

    //Constants: Begin
    regex_t* stringConst ;
    stringConst = makeRegex ("\"^([a-z0-9A-Z]+)\"") ;
    regArray[3] = stringConst;
    tokenArray[3] = t.stringConst;

    regex_t* intConst; 
    intConst = makeRegex("^[0-9]*");
    regArray[4] = intConst;
    tokenArray[4] = t.intConst;

    regex_t* floatConst ;
    // modified to include the count of floating point numbers
    // somehow using / instead of [] complains, ^ is needed to show front
    floatConst = makeRegex ("^[0-9]*[.]*[0-9]+");
    regArray[5] = floatConst;
    tokenArray[5] = t.floatConst;

    //Constants: End
    /*    
    //Punctuation: Begin
    regex_t* leftParen;
    leftParen = makeRegex ("^\\(");
    regArray[6] = leftParen;

    regex_t* rightParen;
    rightParen = makeRegex ("^\\)");
    regArray[7] = rightParen;

    regex_t* leftCurly;
    leftCurly = makeRegex ("^\\{");
    regArray[8] = leftCurly;

    regex_t* rightCurly;
    rightCurly = makeRegex ("^\\{");
    regArray[9] = rightCurly;

    regex_t* leftSquare;
    leftSquare = makeRegex ("^\\[");
    regArray[10] = leftSquare;

    regex_t* rightSquare;
    rightSquare = makeRegex ("^\\]");
    regArray[11] = rightSquare;

    regex_t* comma;
    rightCurly = makeRegex ("^,");
    regArray[12] = comma;

    regex_t* semiColon;
    semiColon = makeRegex ("^;");
    regArray[13] = semiColon;

    regex_t* colon;
    semiColon = makeRegex ("^:");
    regArray[14] = colon;

    regex_t* intKwd;
    intKwd = makeRegex("^int");
    regArray[15] = intKwd;	

    regex_t* floatKwd;
    floatKwd =  makeRegex("^float");
    regArray[16] = floatKwd; 

    regex_t* stringKwd;
    stringKwd = makeRegex("^string");
    regArray[17] = stringKwd;
	
    regex_t* matrixKwd;
    matrixKwd = makeRegex("^matrix");
    regArray[18] = matrixKwd;	

    regex_t* letKwd;
    letKwd = makeRegex("^let");
    regArray[19] = letKwd;	

    regex_t* inKwd;
    inKwd = makeRegex("^in");
    regArray[20] = inKwd;	

    regex_t* endKwd;
    endKwd = makeRegex("^end");
    regArray[21] = endKwd;	

    regex_t* thenKwd;
    thenKwd = makeRegex("^then");
    regArray[22] = thenKwd;
	
    regex_t* ifKwd;
    ifKwd = makeRegex("^if");
    regArray[23] = ifKwd;
	
    regex_t* elseKwd;
    elseKwd = makeRegex("^else");
    regArray[24] = elseKwd;
	
    regex_t* forKwd;
    forKwd = makeRegex("^for");
    regArray[25] = forKwd;	

    regex_t* whileKwd;
    whileKwd = makeRegex("^while");
    regArray[26] = whileKwd;	

    regex_t* printKwd;
    printKwd = makeRegex("^print");
    regArray[27] = printKwd;	

    regex_t*  assign;
    assign = makeRegex("^=");
    regArray[28] = assign;	

    regex_t* plusSign;
    plusSign = makeRegex("^\\+");
    regArray[29] = plusSign;	

    regex_t* star;
    star = makeRegex("^\\*");
    regArray[30] = star;	

    regex_t* dash;
    dash = makeRegex("^-");
    regArray[31] = dash;	

    regex_t* forwardSlash;
    forwardSlash = makeRegex("^/");
    regArray[32] = forwardSlash;	

    regex_t* lessThan;
    lessThan = makeRegex("^\\<");
    regArray[33] = lessThan;	

    regex_t* lessThanEqual;
    lessThanEqual = makeRegex("^\\<=");
    regArray[34] = lessThanEqual;	

    regex_t* greaterThan;
    greaterThan = makeRegex("^\>");
    regArray[35] = greaterThan;	

    regex_t* greaterThanEqual;
    greaterThanEqual = makeRegex("^\>=");
    regArray[36] = greaterThanEqual;	

    regex_t* equalsEquals;
    equalsEquals = makeRegex("^==");
    regArray[37] = equalsEquals;	

    regex_t* notEqual;
    notEqual = makeRegex("^!=");
    regArray[38] = notEqual;	

    regex_t* andOp;
    andOp = makeRegex("^&&");
    regArray[39] = andOp;	

    regex_t* orOp;
    orOp = makeRegex("^\\|\\|");
    regArray[40] = orOp;
	
    regex_t* notOp;
    notOp = makeRegex("^!");
    regArray[41] = notOp;
    */
    //now start looking at the text
    int numMatchedChars = 0;
    //skip any initial whitespace
    numMatchedChars = consumeWhiteSpace(whiteSpace, text);
    text = text + numMatchedChars;

    //try matching with regexes
    int maxNumMatchedChars = 0;
    
    while ( text[0] != '\0' ) {
      maxNumMatchedChars = 0 ;

      //Lee: added in a for loop for the array
      for(int i=0; i < 42; i++)
	{
	  numMatchedChars = matchRegex (regArray[i], text) ;
	  if (numMatchedChars > maxNumMatchedChars) {
	    maxNumMatchedChars = numMatchedChars ;
	    //matchType = wordMatch ;
	    // initialize a char array that holds the matched characters and copy
	    char lexeme[maxNumMatchedChars+1];
	    strcpy(lexeme,text,maxNumMatchedChars);

	    Token *current;
	    Token aToken = Token(tokenArray[i],lexeme);
	    if(head == NULL) {
	      head = aToken;
	      current = head;
	    }
	    else {
	      current.next = aToken;
	      current = current.next;
	    }
	    text = text + numMatchedChars;
	  }
	}
      text = text +1;
    }

}
