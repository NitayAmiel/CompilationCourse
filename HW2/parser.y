%{

#include "nodes.hpp"
#include "output.hpp"

// bison declarations
extern int yylineno;
extern int yylex();

void yyerror(const char*);

// root of the AST, set by the parser and used by other parts of the compiler
std::shared_ptr<ast::Node> program;

using namespace std;

// TODO: Place any additional declarations here
%}

%token <shared_ptr<ast::ID>> ID
// TODO: Define tokens here

// TODO: Define precedence and associativity here

%%

// While reducing the start variable, set the root of the AST
Program:  Funcs { program = $1; }
;

Funcs: FuncDecl Funcs {}
| 





Funcs: FuncDecl Funcs {}
     | /* empty */ {}
;

FuncDecl: RetType ID LPAREN Formals RPAREN LBRACE Statements RBRACE {}
;

RetType: Type {}
       | VOID {}
;

Formals: FormalsList {}
       | /* empty */ {}
;

FormalsList: FormalDecl {}
           | FormalDecl COMMA FormalsList {}
;

FormalDecl: Type ID {}
;

Statements: Statement{}
          |  Statements Statement {}
;

Statement: LBRACE Statement RBRACE {}
         | Type ID SC {}
         | Type ID ASSIGN Exp SC {}
         | ID ASSIGN Exp SC {}
         | Call SC {}
         | RETURN SC {}
         | RETURN Exp SC {}
         | IF LPAREN Exp RPAREN Statement {}
         | IF LPAREN Exp RPAREN Statement ELSE Statement {}
         | WHILE LPAREN Exp RPAREN Statement {}
         | BREAK SC {}
         | CONTINUE SC {}
;

Call: ID LPAREN ExpList RPAREN {}
    | ID LPAREN RPAREN {}
;

ExpList: Exp {$$ = new ExpList($1);}
       | Exp COMMA ExpList { $$ = $3; $$->push_front($1);}
;

Type: INT { $$ = $1;}
    | BYTE { $$ = $1;}
    | BOOL { $$ = $1;}
;


Exp: LPAREN Exp RPAREN {$$ = $2;}
   | Exp BINOP Exp {$$ = new BINOP($1, $3, $2);}
   | ID { $$ = $1;}
   | Call {$$ = $1;}
   | NUM {$$ = $1;}
   | NUM_B {$$ = $1;}
   | STRING {$$ = $1;}
   | TRUE {$$ = $1;}
   | FALSE {$$ = $1;}
   | NOT Exp {$$ = new Not($2);}
   | Exp AND Exp { $$ = new And($1, $3);}
   | Exp OR Exp { $$ = new Or($1, $3);}
   | Exp RELOP Exp { $$ = new RelOp($1, $3, $2);}
   | LPAREN Type RPAREN Exp {$$ = new Cast($4, $2);}
;

// TODO: Define grammar here

%%

// TODO: Place any additional code here