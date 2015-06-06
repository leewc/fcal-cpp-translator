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


// Stmts
class Stmts : public Node {
} ;

class EmptyStmts : public Stmts {
public:
    EmptyStmts ( ) { } ;
    std::string unparse ();
private:
    EmptyStmts(const EmptyStmts &) {} ;
} ;

class StmtsSeq : public Stmts {
public:
    StmtsSeq ( Stmt *_stmt, Stmts *_stmts) : stmt(_stmt), stmts(_stmts) { } ;
    std::string unparse ( );
private:
    Stmt *stmt ;
    Stmts *stmts ;
    StmtsSeq () : stmt(NULL), stmts(NULL) { } ;
    StmtsSeq (const StmtsSeq &) {} ;
} ;

class Stmt : public Node {
} ;

class BinOpExpr : public Expr {
public:
    BinOpExpr ( Expr *_left, std::string *_op, Expr *_right)
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
    VarName (std::string _lexeme ) : lexeme(_lexeme) { } ;
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


#endif

