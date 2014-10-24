#include <cxxtest/TestSuite.h>

#include "readInput.h"
#include "scanner.h"
#include <stdio.h>
using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
 public:
  /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
  */
  Scanner *s ;
  void test_setup_code ( ) {
    s = new Scanner() ;
  }


  // Tests for components and functions used by "scan"
  // --------------------------------------------------

  /* You may need to write several tests to adequately test the
       functions that are called from "scan".  Once you are confident
       that the components used by "scan" work properly, then you can
       run tests on the "scan" method itself.
  */

  // Here you should place tests for these other functions.


  /* Below is one of the tests for these components in the project
       solution created by your instructor..  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

        void xtest_TokenMaker_leftCurly ( ) {
            tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) ;
        }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
  */


  /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
  */





  // Tests for "scan"
  // --------------------------------------------------

  /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
  */

  // Test that a list of tokens has no lexicalError tokens.
  bool noLexicalErrors (Token *tks) {
    Token *currentToken = tks ;
    int i = 0;
    while (currentToken != NULL) {
      i++;
      if (currentToken->terminal == lexicalError) {
	printf("problem: %s\n",currentToken->lexeme.c_str());
	cout << "at " << i;
	return false ;
      }
      else {
	currentToken = currentToken->next ;
      }
    }
    return true ;
  }

  /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
  */
  void scanFileNoLexicalErrors ( const char* filename ) {
    char *text =  readInputFromFile ( filename )  ;
    TS_ASSERT ( text ) ;
    Token *tks = s->scan ( text ) ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT (noLexicalErrors(tks));
  }


  /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
  */
  bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
    Token *currentToken = tks ;
    int termIndex = 0 ;
    while (currentToken != NULL && termIndex < numTerms ) {
      if (currentToken->terminal != ts[termIndex]) {
	printf("%i: %i should be %i\n",termIndex,currentToken->terminal , ts[termIndex]);
	fflush(stdout);
	return false ;
      }
      else {
	++ termIndex ;
	currentToken = currentToken->next ;
      }
    }
    return true ;
  }


  /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

  */

  // The "endOfFile" token is always the last one in the list of tokens.
  void test_scan_empty ( ) {
    Token *tks = s->scan ("  ") ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
    TS_ASSERT (tks->next == NULL) ;
  }

  void test_scan_empty_comment ( ) {
    Token *tks = s->scan (" /* a comment */ ") ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
    TS_ASSERT (tks->next == NULL) ;
  }

  // When a lexical error occurs, the scanner creates a token with a 
  // single-character lexeme and lexicalError as the terminal.
  void test_scan_lexicalErrors ( ) {
    Token *tks = s->scan ("$&1  ") ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
    TS_ASSERT_EQUALS (tks->lexeme, "$");
    tks = tks->next ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
    TS_ASSERT_EQUALS (tks->lexeme, "&");
    tks = tks->next ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, intConst) ;
    TS_ASSERT_EQUALS (tks->lexeme, "1");
    tks = tks->next ;
    TS_ASSERT (tks != NULL) ;
    TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
    TS_ASSERT (tks->next == NULL) ;
  }


  // A test for scanning numbers and a variable.
  void test_scan_nums_vars ( ) {
    Token *tks = s->scan (" 123 x 12.34 ") ;
    TS_ASSERT (tks != NULL) ;
    tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
    TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
  }



  /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexeme
       are correct.
  */
    
  void test_scan_bad_syntax_good_tokens ( ) {
    const char *filename = "../samples/bad_syntax_good_tokens.dsl" ;
    char *text =  readInputFromFile ( filename )  ;
    TS_ASSERT ( text ) ;
    Token *tks = s->scan ( text ) ;
    TS_ASSERT (tks != NULL) ;
    tokenType ts[] = { 
      intConst, intConst, intConst, intConst, 

      stringConst, stringConst, stringConst,

      floatConst, floatConst, floatConst,

      matrixKwd,



      semiColon, comma, colon,
      leftCurly, leftParen, rightCurly, rightParen,

      plusSign, star, dash, forwardSlash, 

      equalsEquals, lessThanEqual, 
      greaterThanEqual, notEquals, 
      assign,

      variableName, variableName, variableName, variableName, 
      variableName, variableName, variableName,


      intKwd, floatKwd,  stringKwd,  whileKwd,

            endOfFile
    } ;
    int count = 39; 
    TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
  }

  
  void test_scan_sample_forestLoss_v2 ( ) {
    scanFileNoLexicalErrors ("../samples/forest_loss_v2.dsl") ;
  }
  
  void compare_terminals(const char* inString, tokenType tT){
    Token *tks = s->scan(inString);
    TS_ASSERT (tks != NULL) ;
    tokenType ts[] = { tT, endOfFile } ;
    TS_ASSERT ( sameTerminals ( tks, 2, ts ) ) ;
  }
  
  void test_terminal_intKwd () { compare_terminals(" Int", intKwd);}
   
  void test_terminal_floatKwd () { compare_terminals(" Float", floatKwd);}

  void test_terminal_stringKwd () { compare_terminals(" Str", stringKwd);}

  void test_terminal_boolKwd () { compare_terminals("  Bool", boolKwd);}

  void test_terminal_trueKwd () { compare_terminals("  True", trueKwd);}

  void test_terminal_falseKwd () { compare_terminals("  False", falseKwd);}

  void test_terminal_matrixKwd () { compare_terminals("  Matrix", matrixKwd);}

  void test_terminal_letKwd () { compare_terminals("  let", letKwd);}

  void test_terminal_inKwd () { compare_terminals("  in", inKwd);}

  void test_terminal_endKwd () { compare_terminals("  end", endKwd);}
  
  void test_terminal_ifKwd () { compare_terminals("  if", ifKwd);}

  void test_terminal_thenKwd () { compare_terminals("  then", thenKwd);}

  void test_terminal_elseKwd () { compare_terminals("  else", elseKwd);}

  void test_terminal_forKwd () { compare_terminals("  for", forKwd);}

  void test_terminal_whileKwd () { compare_terminals("  while", whileKwd);}

  void test_terminal_printKwd () { compare_terminals("  print", printKwd);}

  void test_terminal_intConst () { compare_terminals("  123", intConst);}

  void test_terminal_floatConst () { compare_terminals("  123.456", floatConst);}

  void test_terminal_stringConst () { compare_terminals("  \"string\"", stringConst);}

  void test_terminal_variableName () { compare_terminals("  variable_Name10", variableName);}

  void test_terminal_leftParen () { compare_terminals("  (", leftParen);}

  void test_terminal_rightParen () { compare_terminals("  )", rightParen);}

  void test_terminal_leftCurly () { compare_terminals("  {", leftCurly);}

  void test_terminal_rightCurly () { compare_terminals("  }", rightCurly);}

  void test_terminal_leftSquare () { compare_terminals("  [", leftSquare);}

  void test_terminal_rightSquare () { compare_terminals("  ]", rightSquare);}

  void test_terminal_comma () { compare_terminals("  ,", comma);}

  void test_terminal_semiColon () { compare_terminals("  ;", semiColon);}

  void test_terminal_colon () { compare_terminals("  :", colon);}

  void test_terminal_assign () { compare_terminals("  =", assign);}

  void test_terminal_plusSign () { compare_terminals("  +", plusSign);}

  void test_terminal_star () { compare_terminals("  *", star);}

  void test_terminal_dash () { compare_terminals("  -", dash);}

  void test_terminal_forwadrSlash () { compare_terminals("  /", forwardSlash);}

  void test_terminal_lessThan () { compare_terminals("  <", lessThan);}

  void test_terminal_lessThanEqual () { compare_terminals("  <=", lessThanEqual);}

  void test_terminal_greaterThan () { compare_terminals("  >", greaterThan);}

  void test_terminal_greaterThanEqual () { compare_terminals("  >=", greaterThanEqual);}

  void test_terminal_equalsEquals () { compare_terminals("  ==", equalsEquals);}

  void test_terminal_notEquals () { compare_terminals("  !=", notEquals);}

  void test_terminal_andOp () { compare_terminals("  &&", andOp);}

  void test_terminal_orOp () { compare_terminals("  ||", orOp);}

  void test_terminal_notOp () { compare_terminals("  !", notOp);}

  void test_terminal_endOfFile () { compare_terminals("  ", endOfFile);}

} ;
