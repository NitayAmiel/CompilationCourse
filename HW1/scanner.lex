%{
#include <stdio.h>
#include <string>
#include <cstring>
#include "tokens.hpp"

std::string str = "";

void nl();
void pushString(std::string s);

%}

%option yylineno
%option noyywrap

/* Rules Section */
DIGIT  [0-9]
DIGITX  [0-9a-fA-F]
LETTER [a-zA-Z]
WORD   {LETTER}({LETTER}|{DIGIT})*
NUM    [1-9][0-9]*|0

%x      STRING
%%
void                { return tokentype::VOID;}
int                { return tokentype::INT;}
byte                { return tokentype::BYTE;}
bool                { return tokentype::BOOL;}
and                { return tokentype::AND;}
or                { return tokentype::OR;}
not                { return tokentype::NOT;}
true                { return tokentype::TRUE;}
false                { return tokentype::FALSE;}
return               { return 10;}
if                { return 11;}
else                { return 12;}
while                { return 13;}
break                { return 14;}
continue                { return 15;}
;                { return 16;}
,               { return 17;}
\(                { return 18;}
\)                { return 19;}
{                { return 20;}
}                { return 21;}
=                { return 22;}
==|!=|<|>|<=|>=              { return 23;}
\+|-|\*|\/             { return 24;}
\/\/.*                       {return 25;}
{WORD}                          {return 26;}
{NUM}                {return 27;}
{NUM}b              {return 28;}
[ \t]                { }
\n                     {nl();}

\"                   { BEGIN(STRING); str = "\"";}
<STRING>[^\"\\]*\\n          { pushString(yytext); str[str.size() - 2] = '\n'; str =str.substr(0, str.size() - 1);}
<STRING>[^\"\\]*\\t          { pushString(yytext); str.replace(str.size() - 2, 2, "\t");}
<STRING>[^\"\\]*\\x{DIGITX}{DIGITX}          { pushString(yytext); str[str.size() - 4] = stoi(str.substr(str.size() - 2), nullptr, 16); str = str.substr(0, str.size() - 3);}

<STRING>[^\"\\]*\"           { BEGIN(INITIAL); pushString(yytext); yytext = (char*)malloc((str.size() + 1)*sizeof(char)); std::strcpy(yytext, str.c_str()); return 29;}



. { return 0;}

%%

void nl(){
    yylineno;
}

void pushString(std::string s) {
    str += s;
}
