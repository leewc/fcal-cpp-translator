#include "ast.h"

using namespace std ;

// Root
// ------------------------------------------------------------
string Root::unparse () {
    return varName->unparse() + " () {\n" + stmts->unparse() + "\n}\n" ;
}

Root::~Root() {}


// Decls
// ------------------------------------------------------------

string SimpleDecl::unparse(){
       return kwd + " " + var->unparse() + " ;";
}

string MatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " = " + expr1->unparse() + " ;";
}

string LongMatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + "] " + var2->unparse() + " , " + var3->unparse() + " = " + expr3->unparse() + " ;";
}

// Exprs
// ------------------------------------------------------------
string BinOpExpr::unparse ( ) {
    //return "bin op";
	return "(" + left->unparse() + " " + *op + " " + right->unparse() + ")" ;
}

string VarName::unparse ( ) { return lexeme ; } ;

string AnyConst::unparse ( ) { return constString ; } ;

string MatrixRefExpr::unparse(){
       return var->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + " ]";
}

string NestOrFuncExpr::unparse() {
       return var->unparse() + " (" + expr->unparse() + ")";
}

string LetExpr::unparse() {
       return "let " + stmts->unparse() + " in " + expr->unparse() + " end";
}

string IfElseExpr::unparse() {
       return "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse();
}

string NotExpr::unparse() {
       return "!" + expr->unparse();
}

// Stmts
// -----------------------------------------------------------
string EmptyStmts::unparse() {
  return "";
}

string StmtsSeq::unparse() {
  return stmt->unparse() + stmts->unparse();
}

// Stmt
// -----------------------------------------------------------

string DeclStmt::unparse() {
  return decl->unparse() ;
}

string IfStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse();
}

string IfElseStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse() + "\n" + "else " + elseStmt->unparse();
}

string BlockStmt::unparse() {
  return "{ \n" + statements->unparse()+ "\n}";
}

string PrintStmt::unparse() {
  return "print (" + printExpr->unparse() + " );" ;
}

string AssignStmt::unparse() {
  return var->unparse() + " = " + rightExpr-> unparse();
}

string LongAssignStmt::unparse() {
  return var->unparse() + "["+ leftExpr1->unparse() + "," + leftExpr2->unparse() +"] = " + rightExpr->unparse();
}

string WhileStmt::unparse() { 
  return "while (" + whileExpr->unparse() + " )" + whileStmt->unparse();
}

string ForStmt::unparse() {
  return "for (" + var->unparse() +" = " + expr1->unparse() + ":" + expr2->unparse() + ")" + statements->unparse();
}
 
