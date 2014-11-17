#ifndef Node_H
#define Node_H

#include <string>
#include <iostream> 

#include "scanner.h"

class Node ;

class RootAbs ;
class Stmts ;
class Stmt ;
class Expr ;
class LExpr ;
class Decl ;
class VarName ;

// Node
class Node {
	public:
		virtual std::string unparse ( ) { return " This should be pure virtual ";} ;
		virtual std::string cppCode ( ) { return " This should be pure virtual" ; } ;
		virtual ~Node() { }
} ;


class Expr : public Node {
} ;



class Root : public Node {
public:
    Root(VarName *v, Stmts *s) : varName(v), stmts(s) { } ;
    std::string unparse ();
    virtual ~Root() ;
private:
    VarName *varName ;
    Stmts *stmts ;
    Root() : varName(NULL), stmts(NULL) { } ;
    Root(const Root &) {};
} ;

// Stmt
class Stmt: public Node {} ;

class DeclStmt: public Stmt {
 public: 
  DeclStmt(Decl *_decl){};
  std::string unparse ();
 private:
  Decl *decl; //need to double check this -lee
  DeclStmt(const DeclStmt &) {};
}
class IfStmt: public Stmt {
 public:
  IfStmt(Expr *_ifExpr, Stmt *_thenStmt){};
  std::string unparse();
 private:
  Expr *ifExpr;
  Stmt *thenStmt;
  IfStmt(const IfStmt &) {};
}

class IfElseStmt: public IfStmt {
 public:
   IfElseStmt(Expr *_ifExpr, Stmt *_thenStmt, Stmt *_elseStmt){};
   std::string unparse();
 private:
   Stmt *elseStmt;
   IfElseStmt(const IfElseStmt &){};
}

class BlockStmt: public Stmt {
 public:
  BlockStmt(Stmts *_statements) {};
  std::string unparse();
 private:
  Stmts *statements;
  BlockStmt(const BlockStmt &){};
}

class PrintStmt: public Stmt {
 public:
  PrintStmt(Expr *_printExpr){};
  std::string unparse();
 private:
  Expr *printExpr;
  PrintStmt(const PrintStmt &){};
}

class AssignStmt: public Stmt {
 public: 
  AssignStmt(VarName *_var, Expr *_rightExpr){} ;
  std::string unparse();
 private:
  VarName *var;
  Expr *rightExpr;
  AssignStmt(const AssignStmt &){};
}


class LongAssignStmt: public Stmt {
 public: 
  longAssignStmt(Expr* _leftExpr, Expr* _rightExpr){};
  std::string unparse();
 private: 
  Expr *leftExpr;
  Expr *righExpr;
  LongAssignStmt(const longAssignStmt &){};
}

class WhileStmt: public Stmt {
 public: 
  whileStmt(Expr* _whileExpr, Stmt* _whileStmt){};
  std::string unparse();
 private:
  Expr *WhileExpr;
  Stmt *WhileStmt;
  WhileStmt(const whileStmt &){};
}

class forStmt: public Stmt { 
 public:
  forStmt(VarName _varName, Expr* _expr1, Expr* _expr2, Stmt* _stmt);
  std::string unparse();
 private:
  VarName *var;
  Expr *expr1;
  Expr *expr2;
  Stmt *statements;
  forStmt(const forStmt &){};
}

// Stmts
class Stmts : public Node {} ;

class EmptyStmts : public Stmts {
public:
    EmptyStmts( ){} ;
    std::string unparse ();
private:
    EmptyStmts(const EmptyStmts &) {} ;
} ;

class StmtsSeq : public Stmts {
public:
    StmtsSeq( Stmt *_stmt, Stmts *_stmts) : stmt(_stmt), stmts(_stmts) { } ;
    std::string unparse ( );
private:
    Stmt *stmt ;
    Stmts *stmts ;
    StmtsSeq () : stmt(NULL), stmts(NULL) { } ;
    StmtsSeq (const StmtsSeq &) {} ;
} ;

//Decls
class Decl : public Node {
};

class SimpleDecl : public Decl {
public:
       SimpleDecl(std::string _kwd, VarName *_var) : kwd(_kwd), var(_var) {};
       std::string unparse();
private:
        std::string kwd;
        VarName *var;
        SimpleDecl (const SimpleDecl &) {} ;
} ;

class MatrixDecl : public Decl {
public:
       MatrixDecl(VarName *_var1, Expr *_expr1) : var1(_var1), expr1(_expr1) {};
       std::string unparse();
private:
        VarName *var1;
        Expr *expr1;
        MatrixDecl (const MatrixDecl &) {} ;
} ;

class LongMatrixDecl : public Decl {
public:
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

//Expresssions

class BinOpExpr : public Expr {
public:
    BinOpExpr( Expr *_left, std::string *_op, Expr *_right)
    : left(_left), op(_op), right(_right) { } ;
    std::string unparse ( ) ;
private:
    Expr *left ;
    std::string *op ;
    Expr *right ;
    BinOpExpr() : left(NULL), op(NULL), right(NULL) {} ;
    BinOpExpr(const BinOpExpr &) { } ;
} ;


// VarName
class VarName : public Expr {
public:
    VarName(std::string _lexeme ) : lexeme(_lexeme) { } ;
    std::string unparse ( ) ;
private:
    std::string lexeme ;
    VarName ( ) : lexeme( (std::string) "") { } ;
    VarName (const VarName &) { } ;
} ;

class AnyConst : public Expr {
public:
    AnyConst ( std::string _s ) : constString(_s) { } ;
    std::string unparse ( ) ;
private:
    std::string constString ;
    AnyConst() {};
    AnyConst(const AnyConst &) {};
} ;

class NestOrFuncExpr : public Expr {
public:
       NestOrFuncExpr(VarName *_var, Expr *_expr) : var(_var), expr(_expr) {};
       std::string unparse();
private:
        VarName *var;
        Expr *expr;
        NestOrFuncExpr(const NestOrFuncExpr &) {};
};

class MatrixRefExpr : public Expr {
public:
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
       LetExpr(Stmts *_stmts, Expr *_expr) : stmts(_stmts), expr(_expr) {};
       std::string unparse();
private:
        Stmts *stmts;
        Expr *expr;
        LetExpr(const LetExpr &) {};
};

class IfElseExpr : public Expr {
public:
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
       NotExpr(Expr *_expr) : expr(_expr) {};
       std::string unparse();
private:
        Expr *expr;
        NotExpr(const NotExpr &) {};
};

#endif

