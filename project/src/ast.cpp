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
string Root::cppCode(){
	return (string)
	"#include <iostream>\n" +
	"#include \"Matrix.h\"\n" +
	"#include <math.h>\n" +
	"using namespace std; \n" +
	"int main () { \n" +
	stmts->cppCode() +
	"\n}\n";
}

Root::~Root() {}

//Decl
//----------------------------------------------

/*! \fn string SimpleDecl::unparse()
    \brief Unparse for SimpleDecl node: integerKwd|floatKwd|stringKwd varName ';'
*/
string SimpleDecl::unparse(){
       return kwd + " " + var->unparse() + "; \n";
}

string SimpleDecl::cppCode(){
	if(kwd == "Int") return (string) "int " + var->cppCode() + "; \n";
	if(kwd == "Float") return (string) "float " + var->cppCode() + "; \n";
	if(kwd == "Str") return (string) "string " + var->cppCode() + "; \n";
}

/*! \fn string MatrixDecl::unparse()
    \brief Unparse for MatrixDecl node : 'Matrix' varName '=' Expr ';'
*/
string MatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " = " + expr1->unparse() + ";  \n";
}

string MatrixDecl::cppCode(){
	return (string) "Matrix " + var1->cppCode() +"( " + expr1->cppCode() + " ) ; \n" ;
}

/*! \fn string LongMatrixDecl::unparse()
    \brief Unparse for LongMatrixDecl node : 'Matrix' varName '[' Expr ',' Expr ']' varName ',' varName  '=' Expr ';'
*/
string LongMatrixDecl::unparse(){
       return "Matrix " + var1->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + "] " + var2->unparse() + " , " + var3->unparse() + " = " + expr3->unparse() + "; \n";
}

string LongMatrixDecl::cppCode(){
	string v1 = var1->cppCode();
	string e1 = expr1->cppCode();
	string v2 = var2->cppCode();
	string e2 = expr2->cppCode();
	string v3 = var3->cppCode();
	
	return (string) "Matrix " + v1 + "( "+ e1 +","+ e2 +") ; \n" 
						+ "for (int " + v2 + " = 0;" + v2 + " < " + e1 + "; " + v2 +" ++ ) { \n"
							+ "		for (int " + v3 + " = 0;" + v3 + " < " + e2 + "; " + v3 +" ++ ) { \n" 
								+ " 	*("+ v1 +".access(" + v2 + "," + v3 + ")) = (" + expr3->cppCode() + " ); \n"
									+ "		} \n}";
}

//Expr
//----------------------------------------------

/*! \fn string BinOpExpr::unparse()
    \brief Unparse for BinOpExpr node : Expr 'op' Expr
    ops are: * / + - > >= < <= == != && ||
*/
string BinOpExpr::unparse ( ) {
    //return "bin op";
	return  left->unparse() + " " + *op + " " + right->unparse() ;
}

string BinOpExpr::cppCode(){
	return  left->cppCode() + " " + *op + " " + right->cppCode() ;
}

/*! \fn string VarName::unparse()
    \brief Unparse for VarName node : varName
*/
string VarName::unparse ( ) { 
	return lexeme ; 
} 

string VarName::cppCode(){
	return (string) lexeme;
}

/*! \fn string AnyConst::unparse()
    \brief Unparse for AnyConst node : integerConst | floatConst |  stringConst
*/
string AnyConst::unparse ( ) { 
	return constString + " "; 
} 

string AnyConst::cppCode(){
	return (string) constString + " "; 
}

/*! \fn string MatrixRefExpr::unparse()
    \brief Unparse for MatrixRefExpr node : varName '[' Expr ',' Expr ']'
*/
string MatrixRefExpr::unparse(){
       return var->unparse() + " [" + expr1->unparse() + " , " + expr2->unparse() + " ]";
}

string MatrixRefExpr::cppCode(){
	return (string) "*( " + var->cppCode() + ".access(" + expr1->cppCode() + ", " + expr2->cppCode() + ")) ";
}

/*! \fn string NestOrFuncExpr::unparse()
    \brief Unparse for NestOrFuncExpr node : varName '(' Expr ')'
*/
string NestOrFuncExpr::unparse() {
	   return var->unparse() + " (" + expr->unparse() + ")";
}

string NestOrFuncExpr::cppCode(){
	return (string) var->cppCode() + " (" + expr->cppCode() + ")";
}

/*! \fn string ParenExpr::unparse()
    \brief Unparse for ParenExpr node : '(' Expr ')'
*/
string ParenExpr::unparse() {
       return "(" + expr->unparse() + ")";
}

string ParenExpr::cppCode(){
	return (string) "(" + expr->cppCode() + ")";
}

/*! \fn string LetExpr::unparse()
    \brief Unparse for LetExpr node : 'let' Stmts 'in' Expr 'end'
*/
string LetExpr::unparse() {
       return "let " + stmts->unparse() + " in " + expr->unparse() + " end ";
}

string LetExpr::cppCode(){
	return (string) "({" + stmts->cppCode() + "(" + expr->cppCode() + ") ; })" ;
}

/*! \fn string IfElseExpr::unparse()
    \brief Unparse for IfElseExpr node : 'if' Expr 'then' Expr 'else' Expr
*/
string IfElseExpr::unparse() {
       return "if " + expr1->unparse() + " then " + expr2->unparse() + " else " + expr3->unparse();
}

string IfElseExpr::cppCode(){
  return (string) "if (" + expr1->cppCode() +") { \n " + expr2->cppCode() + "} \n else { \n" + expr3->cppCode() +" \n }" ;
}

/*! \fn string NotExpr::unparse()
    \brief Unparse for NotExpr node : '!' Expr
*/
string NotExpr::unparse() {
  return "!" + expr->unparse();
}

string NotExpr::cppCode(){
  return (string) "! (" + expr->cppCode() +") ";
}

// Stmts
// -----------------------------------------------------------

/*! \fn string EmptyStmts::unparse()
    \brief Unparse for EmptyStmts node : <<empty>>
*/
string EmptyStmts::unparse() {
  return " ";
}

string EmptyStmts::cppCode(){
	return (string) " ";
}

/*! \fn string StmtsSeq::unparse()
    \brief Unparse for StmtsSeq node : Stmt Stmts
*/
string StmtsSeq::unparse() {
  return stmt->unparse() + stmts->unparse();
}

string StmtsSeq::cppCode(){
	return (string) stmt->cppCode() + stmts->cppCode(); //Can it be this simple? I'm not sure.
}

// Stmt
// -----------------------------------------------------------

/*! \fn string DeclStmt::unparse()
    \brief Unparse for DeclStmt node : Decl
*/
string DeclStmt::unparse() {
  return decl->unparse() ;
}

string DeclStmt::cppCode(){
	return (string) decl->cppCode(); //Is this really it?
}

/*! \fn string IfStmt::unparse()
    \brief Unparse for IfStmt node : 'if' '(' Expr ')' Stmt
*/
string IfStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse();
}

string IfStmt::cppCode(){
	return (string) "if (" + ifExpr->cppCode() + ") " + thenStmt->cppCode() ;
}

/*! \fn string IfElseStmt::unparse()
    \brief Unparse for IfElseStmt node : 'if' '(' Expr ')' Stmt 'else' Stmt
*/
string IfElseStmt::unparse() {
  return "if (" + ifExpr->unparse() + ")" + thenStmt->unparse() + "\n" + "else " + elseStmt->unparse();
}

string IfElseStmt::cppCode(){
       /* The commented one is the format I'm familiar with, 
       the other one is he shorthand given in the example translation files.
       I'm not sure if I got it right. -SS
       */
      // return (string) "if (" + ifExpr->cppCode() + ") {\n  " + thenStmt->cppCode() + 
       //"\n}\nelse {\n" + elseStmt->cppCode() + "\n}"
       
	return (string) "( (" + ifExpr->cppCode() + ") ? (" +thenStmt->cppCode() + ") : " + elseStmt->cppCode() + " );";
}

/*! \fn string BlockStmt::unparse()
    \brief Unparse for BlockStmt node : '{' Stmts '}'
*/
string BlockStmt::unparse() {
  return "{ \n" + statements->unparse()+ "\n}";
}

string BlockStmt::cppCode(){
	return (string) "{ \n" + statements->cppCode()+ "\n}";
}

/*! \fn string PrintStmt::unparse()
    \brief Unparse for PrintStmt node : 'print' '(' Expr ')' ';'
*/
string PrintStmt::unparse() {
  return "print (" + printExpr->unparse() + " );" ;
}

string PrintStmt::cppCode(){
	return (string) "cout << " + printExpr->cppCode() + " ;";
}

/*! \fn string AssignStmt::unparse()
    \brief Unparse for AssignStmt node : varName '=' Expr ';'
*/
string AssignStmt::unparse() {
  return var->unparse() + " = " + rightExpr->unparse() + ";";
}

string AssignStmt::cppCode(){
	return (string) var->cppCode() + " = " + rightExpr->cppCode() + " ;";
}

/*! \fn string LongAssignStmt::unparse()
    \brief Unparse for LongAssignStmt node : varName '[' Expr ',' Expr ']' '=' Expr ';'	
*/
string LongAssignStmt::unparse() {
  return var->unparse() + "["+ leftExpr1->unparse() + "," + leftExpr2->unparse() +"] = " + rightExpr->unparse() +";";
}

string LongAssignStmt::cppCode(){
	return (string) "*("+var->cppCode() + ".access(" + leftExpr1->cppCode() + ", " + leftExpr2->cppCode() + ")) = " + rightExpr->cppCode() + " ;";
}

/*! \fn string WhileStmt::unparse()
    \brief Unparse for WhileStmt node : 'while' '(' Expr ')' Stmt
*/
string WhileStmt::unparse() { 
  return "while (" + whileExpr->unparse() + " )" + whileStmt->unparse();
}

string WhileStmt::cppCode(){
	return (string) "while (" + whileExpr->cppCode() + " )" + whileStmt->cppCode();
}

/*! \fn string ForStmt::unparse()
    \brief Unparse for ForStmt node : 'for' '(' varName '=' Expr ':' Expr ')' Stmt
*/
string ForStmt::unparse() {
  return "for (" + var->unparse() +" = " + expr1->unparse() + ":" + expr2->unparse() + ")" + statements->unparse();
}

string ForStmt::cppCode(){
       std::string var1 = var->cppCode();
	return (string) "for (" + var1 + " = " + expr1->cppCode() + "; " + var1 + " <= " + expr2->cppCode() + "; " + var1 + " ++ )" + statements->cppCode();
}
 
