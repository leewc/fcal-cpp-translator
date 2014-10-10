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


//now start looking at the text

//skip any initial whitespace

//try matching with regexes



}
