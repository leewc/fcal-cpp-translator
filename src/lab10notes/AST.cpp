#include "AST.h"

using namespace std ;

// Root
// ------------------------------------------------------------
string Root::unparse () {
    return varName->unparse() + " () {\n" + stmts->unparse() + "\n}\n" ;
}

Root::~Root() {}

// Stmts
// ------------------------------------------------------------
string StmtsSeq::unparse ( ) {
    return stmt->unparse() + stmts->unparse() ;
}

string EmptyStmts::unparse ( ) {
    return "";
}

string BinOpExpr::unparse ( ) {
    //return "bin op";
	return "(" + left->unparse() + " " + *op + " " + right->unparse() + ")" ;
}

string VarName::unparse ( ) { return lexeme ; } ;

string AnyConst::unparse ( ) { return constString ; } ;