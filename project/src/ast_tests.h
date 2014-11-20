#include <cxxtest/TestSuite.h>

#include "readInput.h"
#include "scanner.h"
#include "extToken.h"
#include "parser.h"
#include "parseResult.h"

#include <sstream>

using namespace std ;

class ParserTestSuite : public CxxTest::TestSuite 
{
public:
    Scanner *s ;
    Parser *p ;
    void test_setup_code ( ) {
        s = new Scanner() ;
        p = new Parser() ;
    }

    void xtest_parse_bad_syntax ( ) {
        const char *text 
          = readInputFromFile ( "../samples/bad_syntax_good_tokens.dsl" )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        TS_ASSERT ( ! pr.ok ) ;
    }
    void xtest_parse_sample_1 ( ) {
        const char *filename = "../samples/sample_1.dsl" ;
        const char *text = readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors ; 
        TSM_ASSERT ( msg , pr.ok );
    }
    void xtest_parse_sample_2 ( ) {
        const char *filename = "../samples/sample_2.dsl" ;
        const char *text = readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors ; 
        TSM_ASSERT ( msg , pr.ok );
    }
    void xtest_parse_sample_4 ( ) {
        const char *filename = "../samples/sample_4.dsl" ;
        const char *text = readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors ; 
        TSM_ASSERT ( msg , pr.ok );
    }
    void xtest_parse_sample_5 ( ) {
        const char *filename = "../samples/sample_5.dsl" ;
        const char *text = readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors ; 
        TSM_ASSERT ( msg , pr.ok );
    }

	void xtest_parse_forestLossV2 ( ) {
        const char *filename = "../samples/forest_loss_v2.dsl" ;
        const char *text = readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg (filename) ;
        msg += "\n" + pr.errors ; 
        TSM_ASSERT ( msg , pr.ok );
    }
    
    void xtest_parse_top_down ( ) {
        const char *text = "main(){}";
        TS_ASSERT ( text ) ;
        ParseResult pr = p->parse ( text ) ;
        string msg ("main") ;
        msg += "\n" + pr.errors ;
        TSM_ASSERT ( msg , pr.ok );
        printf("%s\n",pr.ast->unparse().c_str());
    }
    
    void test_parse_Expr () {
        const char *text = "1+2";
        TS_ASSERT ( text ) ;
        ParseResult pr ;
        ExtToken *tokens ;
        ExtToken *currToken ;
        
        Token *stokens ;
        Scanner *s ;
        try {
            s = new Scanner() ;
            stokens = s->scan (text) ;
            tokens = extendTokenList ( p, stokens ) ;
            
            currToken = tokens ;
           
            p->currToken = currToken;
            p->tokens = tokens;
            p->s = s;
            p->stokens = stokens;
            
            pr = p->parseExpr(0) ;
        }
        catch (string errMsg) {
            pr.ok = false ;
            pr.errors = errMsg ;
            pr.ast = NULL ;
        }
        TSM_ASSERT (pr.errors, pr.ok );
        printf("%s\n",pr.ast->unparse().c_str());
    }

} ;
