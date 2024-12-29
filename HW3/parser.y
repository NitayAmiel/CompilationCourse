%{

#include "nodes.hpp"
#include "output.hpp"
#include <iostream>

// bison declarations
extern int yylineno;
extern int yylex();

void yyerror(const char*);

// root of the AST, set by the parser and used by other parts of the compiler
std::shared_ptr<ast::Node> program;

using namespace std;

// TODO: Place any additional declarations here
%}
%token VOID INT BOOL BYTE

%token TRUE FALSE

%token RETURN
%token IF WHILE

%token BREAK CONTINUE
%token SC
%token COMMA
%token NUM_B NUM ID


%token COMMENT STRING

%right ASSIGN
%left OR 
%left AND
%left  NE LT  LE GE EQ GT
%left ADD SUB
%left MUL DIV
%right NOT
%left LPAREN RPAREN LBRACE RBRACE
%right ELSE




// TODO: Define precedence and associativity here

%%

// While reducing the start variable, set the root of the AST
Program:  Funcs { program = $1; }
;

Funcs:    {$$ = std::make_shared<ast::Funcs>();}
 |  FuncDecl Funcs { std::dynamic_pointer_cast<ast::Funcs>($2)->push_front(std::dynamic_pointer_cast<ast::FuncDecl>($1));$$ = $2; }
   
;

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE {$$ = std::make_shared<ast::FuncDecl>(std::dynamic_pointer_cast<ast::ID>($2), std::dynamic_pointer_cast<ast::Type>($1), std::dynamic_pointer_cast<ast::Formals>($4), std::dynamic_pointer_cast<ast::Statements>($7));}
;

RetType: Type {$$ = $1;}
       | VOID {$$ = $1;}
;

Formals: {$$ = std::make_shared<ast::Formals>();}
 |  FormalsList { $$ = $1; }
;

FormalsList: FormalDecl {$$ = std::make_shared<ast::Formals>(std::dynamic_pointer_cast<ast::Formal>($1));}
           | FormalDecl COMMA FormalsList {$$ = $3; std::dynamic_pointer_cast<ast::Formals>($$)->push_front( std::dynamic_pointer_cast<ast::Formal>($1));}
;

FormalDecl: Type ID {$$ = std::make_shared<ast::Formal>(std::dynamic_pointer_cast<ast::ID>($2), std::dynamic_pointer_cast<ast::Type>($1) );}
;

Statements: Statement {$$  = std::make_shared<ast::Statements>(std::dynamic_pointer_cast<ast::Statement>($1)); }
          |  Statements Statement {$$ = $1;  std::dynamic_pointer_cast<ast::Statements>($$)->push_back(std::dynamic_pointer_cast<ast::Statement>($2));}
;

Statement: LBRACE Statements RBRACE {std::dynamic_pointer_cast<ast::Statements>($2)->in_middle_of_braces = true;$$ = $2;}
         | Type ID SC {$$ = std::make_shared<ast::VarDecl>(std::dynamic_pointer_cast<ast::ID>($2), std::dynamic_pointer_cast<ast::Type>($1));}
         | Type ID ASSIGN Exp SC {$$ = std::make_shared<ast::VarDecl>(std::dynamic_pointer_cast<ast::ID>($2), std::dynamic_pointer_cast<ast::Type>($1), std::dynamic_pointer_cast<ast::Exp>($4));}
         | ID ASSIGN Exp SC {$$ = std::make_shared<ast::Assign>(std::dynamic_pointer_cast<ast::ID>($1), std::dynamic_pointer_cast<ast::Exp>($3));}
         | Call SC {$$ = $1;}
         | RETURN SC {$$ = std::make_shared<ast::Return>();}
         | RETURN Exp SC { $$ = std::make_shared<ast::Return>(std::dynamic_pointer_cast<ast::Exp>($2));}
         | IF LPAREN Exp RPAREN Statement {$$ = std::make_shared<ast::If>(std::dynamic_pointer_cast<ast::Exp>($3), std::dynamic_pointer_cast<ast::Statement>($5));}
         | IF LPAREN Exp RPAREN Statement ELSE Statement {$$ = std::make_shared<ast::If>(std::dynamic_pointer_cast<ast::Exp>($3), std::dynamic_pointer_cast<ast::Statement>($5), std::dynamic_pointer_cast<ast::Statement>($7));}
         | WHILE LPAREN Exp RPAREN Statement {$$ = std::make_shared<ast::While>(std::dynamic_pointer_cast<ast::Exp>($3), std::dynamic_pointer_cast<ast::Statement>($5));}
         | BREAK SC {$$ =$1;}
         | CONTINUE SC {$$ = $1;}
;

Call: ID LPAREN ExpList RPAREN {$$ = std::make_shared<ast::Call>(std::dynamic_pointer_cast<ast::ID>($1), std::dynamic_pointer_cast<ast::ExpList>($3));}
    | ID LPAREN RPAREN {$$ = std::make_shared<ast::Call>(std::dynamic_pointer_cast<ast::ID>($1));}
;

ExpList: Exp {$$ = std::make_shared<ast::ExpList>(std::dynamic_pointer_cast<ast::Exp>($1));}
       | Exp COMMA ExpList { $$ = $3; std::dynamic_pointer_cast<ast::ExpList>($$)->push_front(std::dynamic_pointer_cast<ast::Exp>($1));}
;

Type: INT { $$ = $1;}
    | BYTE { $$ = $1;}
    | BOOL { $$ = $1;}
;


Exp: LPAREN Exp RPAREN {$$ = $2;}
   | Exp ADD Exp {$$ = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3), ast::BinOpType::ADD);}
   | Exp SUB Exp {$$ = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3), ast::BinOpType::SUB);}
   | Exp MUL Exp {$$ = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3), ast::BinOpType::MUL);}
   | Exp DIV Exp {$$ = std::make_shared<ast::BinOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3), ast::BinOpType::DIV);}
   | ID { $$ = $1;}
   | Call {$$ = $1;}
   | NUM {$$ = $1;}
   | NUM_B {$$ = $1;}
   | STRING {$$ = $1;}
   | TRUE {$$ = $1;}
   | FALSE {$$ = $1;}
   | NOT Exp { $$ = std::make_shared<ast::Not>(std::dynamic_pointer_cast<ast::Exp>($2)); }
   | Exp AND Exp { $$ = std::make_shared<ast::And>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3)); }
   | Exp OR Exp { $$ = std::make_shared<ast::Or>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3)); }
| Exp EQ Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::EQ); }
| Exp NE Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::NE); }
| Exp LT Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::LT); }
| Exp GT Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::GT); }
| Exp LE Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::LE); }
| Exp GE Exp                    {$$ = std::make_shared<ast::RelOp>(std::dynamic_pointer_cast<ast::Exp>($1), std::dynamic_pointer_cast<ast::Exp>($3),ast::RelOpType::GE); }
   | LPAREN Type RPAREN Exp        {$$ = std::make_shared<ast::Cast>(std::dynamic_pointer_cast<ast::Exp>($4), std::dynamic_pointer_cast<ast::Type>($2)); }
;

// TODO: Define grammar here

%%

void yyerror(const char*){
	
    output::errorSyn(yylineno);
       exit(0);
}
// TODO: Place any additional code here
