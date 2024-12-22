%{

#include "nodes.hpp" 
#include "output.hpp" 
#include <memory> 
#include <iostream>
#include "parser.tab.h"
%}

%%

void         { yylval =  std::shared_ptr<ast::Type>(new ast::Type(ast::BuiltInType::VOID)); return VOID;}
int          { yylval = std::shared_ptr<ast::Type>(new ast::Type(ast::BuiltInType::INT)); return INT; }
byte         { yylval = std::shared_ptr<ast::Type>(new ast::Type(ast::BuiltInType::BYTE)); return BYTE; }
bool         { yylval = std::shared_ptr<ast::Type>(new ast::Type(ast::BuiltInType::BOOL)); return BOOL;}
and          { return AND; }
or           { return OR; }
not          { return NOT; }
true         { yylval = std::shared_ptr<ast::Bool>(new ast::Bool(1)); return TRUE;}
false        { yylval = std::shared_ptr<ast::Bool>(new ast::Bool(0)); return FALSE;}
return       { return RETURN; }
if           { return IF; }
else         { return ELSE; }
while        { return WHILE; }
break        { yylval = std::shared_ptr<ast::Break>(new ast::Break()); return BREAK; }
continue     { yylval = std::shared_ptr<ast::Continue>(new ast::Continue()); return CONTINUE;}
;            { return SC; }
,            { return COMMA; }
\(            { return LPAREN; }
\)            { return RPAREN; }
\{            { return LBRACE; }
\}            { return RBRACE; }
=            { return ASSIGN; }

==                { return EQ; }
!=                { return NE; }
\<                 { return LT; }
>                 { return GT; }
\<=                { return LE; }
>=                { return GE; }
\+                        { return ADD; }
-                        { return SUB; }
\*                        { return MUL; }
\/                        { return DIV; }
[a-zA-Z_][a-zA-Z0-9_]*         { yylval = std::make_shared<ast::ID>(yytext); return ID; }
0|[1-9][0-9]*                  { yylval = std::make_shared<ast::Num>(yytext); return NUM; }
0b | [1-9][0-9]*b              { yylval = std::make_shared<ast::NumB>(yytext); return NUM_B; }
\"[^\n\r\"\\]|\\[rnt"\\]+\"    { yylval = std::make_shared<ast::String>(yytext); return STRING;}

\n      {}
[ \t\n\r]+       { /* Ignore whitespace */ }
.                {std::cout << yytext << "F" << std::endl;output::errorLex(yylineno);exit(0); }

%%

int yywrap() {
    return 1;
}
