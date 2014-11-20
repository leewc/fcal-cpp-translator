/*! \file ast.h
    \brief The abstract syntax tree header file
    \author Sophia Stembridge
    \author Wen Chuan Lee
    
*/

#ifndef Node_H
#define Node_H

#include <string>
#include <iostream> 

#include "scanner.h"

class Node ;
class Expr ;
class Decl ;
class Root ;
class Stmts ;
class Stmt ;
class VarName;

//Node
class Node {
	public:
 	//! Virtual method in Node class for unparsing back to FCAL
		virtual std::string unparse ( ) { return " This should be pure virtual ";} ;
 	//! Virtual method in Node class for translating into C++
		virtual std::string cppCode ( ) { return " This should be pure virtual" ; } ;
		virtual ~Node() { };
} ;

//Root
class Root : public Node {
 public:
 //! Constructor for Root node.
 Root(VarName *v, Stmts *s) : varName(v), stmts(s) { } ;
  std::string unparse ();
  virtual ~Root() ;
 private:
  VarName *varName ;
  Stmts *stmts ;
 Root() : varName(NULL), stmts(NULL) { } ;
  Root(const Root &) {};
} ;

//Stmt
class Stmt: public Node {} ;

class DeclStmt: public Stmt {
 public: 
 //! Constructor for DeclStmt node.
 DeclStmt(Decl *_decl) : decl(_decl) {};
  std::string unparse ();
 private:
  Decl *decl; //need to double check this -lee
  DeclStmt(const DeclStmt &) {};
} ;

class IfStmt:public Stmt {
 public:
 //! Constructor for IfStmt node.
  IfStmt(Expr *_ifExpr, Stmt *_thenStmt) : ifExpr(_ifExpr), thenStmt(_thenStmt) {};
  std::string unparse();
 private:
  Expr *ifExpr;
  Stmt *thenStmt;
  //IfStmt () : ifExpr(NULL), thenStmt(NULL) {}; 
  IfStmt(const IfStmt &) {};
} ;

class IfElseStmt: public Stmt {
 public:
 //! Constructor for IfElseStmt node.
 IfElseStmt(Expr *_ifExpr, Stmt *_thenStmt, Stmt *_elseStmt) : ifExpr(_ifExpr), thenStmt(_thenStmt), elseStmt(_elseStmt) {};
   std::string unparse();
 private:
   Expr *ifExpr;
   Stmt *thenStmt;
   Stmt *elseStmt;
   IfElseStmt(const IfElseStmt &){};
} ;

class BlockStmt: public Stmt {
 public:
 //! Constructor for BlockStmt node.
 BlockStmt(Stmts *_statements) : statements(_statements) {};
  std::string unparse();
 private:
  Stmts *statements;
  BlockStmt(const BlockStmt &){};
} ;

class PrintStmt: public Stmt {
 public:
 //! Constructor for PrintStmt node.
 PrintStmt(Expr *_printExpr) : printExpr(_printExpr) {};
  std::string unparse();
 private:
  Expr *printExpr;
  PrintStmt(const PrintStmt &){};
} ;

class AssignStmt: public Stmt {
 public: 
 //! Constructor for AssignStmt node.
 AssignStmt(VarName *_var, Expr *_rightExpr) : var(_var), rightExpr(_rightExpr) {} ;
  std::string unparse();
 private:
  VarName *var;
  Expr *rightExpr;
  AssignStmt(const AssignStmt &){};
} ;


class LongAssignStmt: public Stmt {
 public: 
 //! Constructor for LongAssignStmt node.
 LongAssignStmt(VarName *_var, Expr* _leftExpr1, Expr* _leftExpr2, Expr* _rightExpr) :
  var(_var), leftExpr1 (_leftExpr1), leftExpr2(_leftExpr2), rightExpr (_rightExpr) {};
  std::string unparse();
 private: 
  VarName *var;
  Expr *leftExpr1;
  Expr *leftExpr2;
  Expr *rightExpr;
  LongAssignStmt(const LongAssignStmt &){};
} ;

class WhileStmt: public Stmt {
 public: 
 //! Constructor for WhileStmt node.
 WhileStmt(Expr* _whileExpr, Stmt* _whileStmt) : whileExpr(_whileExpr), whileStmt(_whileStmt){};
  std::string unparse();
 private:
  Expr *whileExpr;
  Stmt *whileStmt;
  // WhileStmt(): whileExpr(NULL), whileStmt(NULL) {}; 
  WhileStmt(const WhileStmt &){};
} ;

class ForStmt: public Stmt { 
 public:
 //! Constructor for ForStmt node.
 ForStmt(VarName* _varName, Expr* _expr1, Expr* _expr2, Stmt* _stmt): var(_varName), expr1 (_expr1), expr2(_expr2),statements (_stmt) {};
  std::string unparse();
 private:
  VarName *var;
  Expr *expr1;
  Expr *expr2;
  Stmt *statements;
  ForStmt(const ForStmt &){};
} ;

//Stmts
class Stmts : public Node {} ;

class EmptyStmts : public Stmts {
public:
 //! Constructor for EmptyStmts node.
    EmptyStmts( ){} ;
    std::string unparse ();
private:
    EmptyStmts(const EmptyStmts &) {} ;
} ;

class StmtsSeq : public Stmts {
public:
 //! Constructor for StmtsSeq node.
    StmtsSeq( Stmt *_stmt, Stmts *_stmts) : stmt(_stmt), stmts(_stmts) { } ;
    std::string unparse ( );
private:
    Stmt *stmt ;
    Stmts *stmts ;
    StmtsSeq () : stmt(NULL), stmts(NULL) { } ;
    StmtsSeq (const StmtsSeq &) {} ;
} ;

//Decl
class Decl : public Node {
};

class SimpleDecl : public Decl {
public:
 //! Constructor for SimpleDecl node.
       SimpleDecl(std::string _kwd, VarName *_var) : kwd(_kwd), var(_var) {};
       std::string unparse();
private:
        std::string kwd;
        VarName *var;
        SimpleDecl (const SimpleDecl &) {} ;
} ;

class MatrixDecl : public Decl {
public:
 //! Constructor for MatrixDecl node.
       MatrixDecl(VarName *_var1, Expr *_expr1) : var1(_var1), expr1(_expr1) {};
       std::string unparse();
private:
        VarName *var1;
        Expr *expr1;
        MatrixDecl (const MatrixDecl &) {} ;
} ;

class LongMatrixDecl : public Decl {
public:
 //! Constructor for LongMatrixDecl node.
       LongMatrixDecl(VarName *_var1, VarName *_var2, VarName *_var3, Expr *_expr1, Expr *_expr2, Expr *_expr3) : var1(_var1), var2(_var2), var3(_var3), expr1(_expr1), expr2(_expr2), expr3(_expr3) {};
       std::string unparse();
private:
        VarName *var1;
        VarName *var2;
        VarName *var3;
        Expr *expr1;
        Expr *expr2;
        Expr *expr3;
        LongMatrixDecl (const LongMatrixDecl &) {} ;
} ;

//Expr
class Expr : public Node {
} ;

class BinOpExpr : public Expr {
public:
 //! Constructor for BinOpExpr node.
    BinOpExpr( Expr *_left, std::string *_op, Expr *_right)
    : left(_left), op(_op), right(_right) { } ;
    std::string unparse ( ) ;
private:
    Expr *left ;
    std::string *op ;
    Expr *right ;
    BinOpExpr(const BinOpExpr &) { } ;
} ;

class VarName : public Expr {
public:
 //! Constructor for VarName node.
    VarName(std::string _lexeme ) : lexeme(_lexeme) { } ;
    std::string unparse ( ) ;
private:
    std::string lexeme ;
    VarName ( ) : lexeme( (std::string) "") { } ;
    VarName (const VarName &) { } ;
} ;

class AnyConst : public Expr {
public:
 //! Constructor for AnyConst node.
    AnyConst ( std::string _s ) : constString(_s) { } ;
    std::string unparse ( ) ;
private:
    std::string constString ;
    AnyConst() {};
    AnyConst(const AnyConst &) {};
} ;

class NestOrFuncExpr : public Expr {
public:
 //! Constructor for NestOrFuncExpr node.
       NestOrFuncExpr(VarName *_var, Expr *_expr) : var(_var), expr(_expr) {};
       std::string unparse();
private:
        VarName *var;
        Expr *expr;
        NestOrFuncExpr(const NestOrFuncExpr &) {};
};

class ParenExpr : public Expr {
public:
 //! Constructor for ParenExpr node.
    ParenExpr(Expr *_centerExpr) :expr(_centerExpr) {} ;
    std::string unparse ( ) ;
private:
    Expr *expr;
    ParenExpr (const ParenExpr &) { } ;
} ;

class MatrixRefExpr : public Expr {
public:
 //! Constructor for MatrixRefExpr node.
       MatrixRefExpr(VarName *_var, Expr *_expr1, Expr *_expr2) : var(_var), expr1(_expr1), expr2(_expr2){};
       std::string unparse();
private:
        VarName *var;
        Expr *expr1;
        Expr *expr2;
        MatrixRefExpr(const MatrixRefExpr &) {};
};

class LetExpr : public Expr {
public:
 //! Constructor for LetExpr node.
       LetExpr(Stmts *_stmts, Expr *_expr) : stmts(_stmts), expr(_expr) {};
       std::string unparse();
private:
        Stmts *stmts;
        Expr *expr;
        LetExpr(const LetExpr &) {};
};

class IfElseExpr : public Expr {
public:
 //! Constructor for IfElseExpr node.
       IfElseExpr(Expr *_expr1, Expr *_expr2, Expr *_expr3) : expr1(_expr1), expr2(_expr2), expr3(_expr3) {};
       std::string unparse();
private:
        Expr *expr1;
        Expr *expr2;
        Expr *expr3;
        IfElseExpr(const IfElseExpr &) {};
};

class NotExpr : public Expr {
public:
 //! Constructor for NotExpr node.
       NotExpr(Expr *_expr) : expr(_expr) {};
       std::string unparse();
private:
        Expr *expr;
        NotExpr(const NotExpr &) {};
};

#endif

