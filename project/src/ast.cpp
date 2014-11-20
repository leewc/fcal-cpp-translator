/*! \file ast.cpp
    \brief The abstract syntax tree .cpp file
    \author Sophia Stembridge
    \author Wen Chuan Lee
    
*/
#include "ast.h"

using namespace std ;

//Root
//----------------------------------------------

/*! \fn string Root::unparse()
    \brief Unparse for root node: varName '(' ')' '{' Stmts '}'
*/
string Root::unparse () {
    return varName->unparse() + " () {\n" + stmts->unparse() + "\n}\n" ;
}

Root::~Root() {}

//Decl
//----------------------------------------------

/*! \fn string SimpleDecl::unparse()
    \brief Unparse for SimpleDecl node: integerKwd|floatKwd|stringKwd varName ';'
*/
string SimpleDecl::unparse(){
       return kwd + " " + var->unparse() + " ;";
}

/*! \fn string MatrixDecl::unparse()
    \brief Unparse for MatrixDecl node : 'Matrix' varName '=' Expr ';'
*/
string MatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " = " + expr1->unparse() + " ;";
}

/*! \fn string LongMatrixDecl::unparse()
    \brief Unparse for LongMatrixDecl node : 'Matrix' varName '[' Expr ',' Expr ']' varName ',' varName  '=' Expr ';'
*/
string LongMatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + "] " + var2->unparse() + " , " + var3->unparse() + " = " + expr3->unparse() + " ;";
}

//Expr
//----------------------------------------------

/*! \fn string BinOpExpr::unparse()
    \brief Unparse for BinOpExpr node : Expr 'op' Expr
    ops are: * / + - > >= < <= == != && ||
*/
string BinOpExpr::unparse ( ) {
    //return "bin op";
	return "(" + left->unparse() + " " + *op + " " + right->unparse() + ")" ;
}

/*! \fn string VarName::unparse()
    \brief Unparse for VarName node : varName
*/
string VarName::unparse ( ) { return lexeme ; } ;

/*! \fn string AnyConst::unparse()
    \brief Unparse for AnyConst node : integerConst | floatConst |  stringConst
*/
string AnyConst::unparse ( ) { return constString ; } ;

/*! \fn string MatrixRefExpr::unparse()
    \brief Unparse for MatrixRefExpr node : varName '[' Expr ',' Expr ']'
*/
string MatrixRefExpr::unparse(){
       return var->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + " ]";
}

/*! \fn string NestOrFuncExpr::unparse()
    \brief Unparse for NestOrFuncExpr node : varName '(' Expr ')'
*/
string NestOrFuncExpr::unparse() {
       return var->unparse() + " (" + expr->unparse() + ")";
}

/*! \fn string ParenExpr::unparse()
    \brief Unparse for ParenExpr node : '(' Expr ')'
*/
string ParenExpr::unparse() {
       return "(" + expr->unparse() + ")";
}

/*! \fn string LetExpr::unparse()
    \brief Unparse for LetExpr node : 'let' Stmts 'in' Expr 'end'
*/
string LetExpr::unparse() {
       return "let " + stmts->unparse() + " in " + expr->unparse() + " end";
}

/*! \fn string IfElseExpr::unparse()
    \brief Unparse for IfElseExpr node : 'if' Expr 'then' Expr 'else' Expr
*/
string IfElseExpr::unparse() {
       return "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse();
}

/*! \fn string NotExpr::unparse()
    \brief Unparse for NotExpr node : '!' Expr
*/
string NotExpr::unparse() {
       return "!" + expr->unparse();
}

// Stmts
// -----------------------------------------------------------

/*! \fn string EmptyStmts::unparse()
    \brief Unparse for EmptyStmts node : <<empty>>
*/
string EmptyStmts::unparse() {
  return "";
}

/*! \fn string StmtsSeq::unparse()
    \brief Unparse for StmtsSeq node : Stmt Stmts
*/
string StmtsSeq::unparse() {
  return stmt->unparse() + stmts->unparse();
}

// Stmt
// -----------------------------------------------------------

/*! \fn string DeclStmt::unparse()
    \brief Unparse for DeclStmt node : Decl
*/
string DeclStmt::unparse() {
  return decl->unparse() ;
}

/*! \fn string IfStmt::unparse()
    \brief Unparse for IfStmt node : 'if' '(' Expr ')' Stmt
*/
string IfStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse();
}

/*! \fn string IfElseStmt::unparse()
    \brief Unparse for IfElseStmt node : 'if' '(' Expr ')' Stmt 'else' Stmt
*/
string IfElseStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse() + "\n" + "else " + elseStmt->unparse();
}

/*! \fn string BlockStmt::unparse()
    \brief Unparse for BlockStmt node : '{' Stmts '}'
*/
string BlockStmt::unparse() {
  return "{ \n" + statements->unparse()+ "\n}";
}

/*! \fn string PrintStmt::unparse()
    \brief Unparse for PrintStmt node : 'print' '(' Expr ')' ';'
*/
string PrintStmt::unparse() {
  return "print (" + printExpr->unparse() + " );" ;
}

/*! \fn string AssignStmt::unparse()
    \brief Unparse for AssignStmt node : varName '=' Expr ';'
*/
string AssignStmt::unparse() {
  return var->unparse() + " = " + rightExpr-> unparse();
}

/*! \fn string LongAssignStmt::unparse()
    \brief Unparse for LongAssignStmt node : varName '[' Expr ',' Expr ']' '=' Expr ';'	
*/
string LongAssignStmt::unparse() {
  return var->unparse() + "["+ leftExpr1->unparse() + "," + leftExpr2->unparse() +"] = " + rightExpr->unparse();
}

/*! \fn string WhileStmt::unparse()
    \brief Unparse for WhileStmt node : 'while' '(' Expr ')' Stmt
*/
string WhileStmt::unparse() { 
  return "while (" + whileExpr->unparse() + " )" + whileStmt->unparse();
}

/*! \fn string ForStmt::unparse()
    \brief Unparse for ForStmt node : 'for' '(' varName '=' Expr ':' Expr ')' Stmt
*/
string ForStmt::unparse() {
  return "for (" + var->unparse() +" = " + expr1->unparse() + ":" + expr2->unparse() + ")" + statements->unparse();
}
 
