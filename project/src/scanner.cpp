/*Scanner will read in text and output a linked list of tokens
based on what was in the text. Each token will contain a string
copy of the original text (terminal), what type of token it is 
(tokenType), and a pointer to the next token in the list (next).
*/

#include <stdio.h>
#include <stdlib.h>

//included the string header or else C++ doesn't support strings
#include <string.h>

#include "scanner.h"
#include "regex.h"
#include "regex.cpp"


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
Token* Scanner::scan(const char* text){
    Token* head;
    
    //first make all the regexes for each token type
    regex_t* regArray[42];

    tokenType* tokenArray[42];
    tokenType t;

    int a = 0; //tracker for array 
    
    //whitespace should not be in the array
    regex_t* whiteSpace ;
    whiteSpace = makeRegex ("^[\n\t\r ]+") ;
    
    //We don't need block or line comment regexes. 
    //And now I remember why I wanted to use a variable instead of 
    //hard coding all the array numbers: in case we needed to change something.
    regex_t* blockCommentReg ;
    blockCommentReg = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/"); 
    regArray[a] = blockCommentReg;
    a++;
    
    regex_t* lineCommentReg ;
    lineCommentReg = makeRegex ("^//[^\n]*\n");
    regArray[a] = lineCommentReg;
    a++;
        
    //Constants: Begin
    regex_t* stringConstReg ;
    stringConstReg = makeRegex ("\"^([a-z0-9A-Z]+)\"") ;
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
    floatKwdReg =  makeRegex("^float");
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

    regex_t*  assignReg;
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

    regex_t* notEqualReg;
    notEqualReg = makeRegex("^!=");
    regArray[a] = notEqualReg;	
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

    //now start looking at the text
    int numMatchedChars = 0;
    //skip any initial whitespace
    numMatchedChars = consumeWhiteSpace(whiteSpace, text);
    text = text + numMatchedChars;

    //try matching with regexes
    int maxNumMatchedChars = 0;
    enum tokenEnumType term;
    std::string lex;
    
    while ( text[0] != '\0' ) {
      maxNumMatchedChars = 0 ;
      term = lexicalError;

      //We have no way of setting term when using the array, so I'm going the long way for now.
      
	  numMatchedChars = matchRegex (intKwdReg, text) ;
	  if (numMatchedChars > maxNumMatchedChars) {
	    maxNumMatchedChars = numMatchedChars ;
	    term = intKwd;
      // initialize a char array that holds the matched characters and copy
      char* data;
      data = strncpy(data, text, maxNumMatchedChars);
      std::string tempLex(data);
	    lex = tempLex;
	  }
     
	  Token *current;
	  Token aToken = Token(term, lex, NULL);
	  if(head == NULL) {
	    head = &aToken;
	    current = head;
	  }
	  else {
	    current->next = &aToken;
	    current = current->next;
	  }
	  text = text + numMatchedChars;
    }

    return head;

}
