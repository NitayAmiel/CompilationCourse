%{
#include <stdio.h>
#include <string>
#include <cstring>
#include "tokens.hpp"

struct string_state string_data = {"", ERROR_VALUE::NO_ERROR};

void nl();
void pushString(std::string s);
void handle_escape(char* cur_text, bool is_digit = false);
void return_initial();
void error_handle_ud_escape(int error_length);
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
[ \t]                { ;}
\n                     {;}

\"                   { BEGIN(STRING); string_data.str = "\"";}

<STRING>([^\\\n\r\"]+)                              {pushString(yytext);}
<STRING>\\[nrt\\\"0]                                {handle_escape(yytext);}
<STRING>\\.                                {error_handle_ud_escape(1, ERROR_VALUE::UNDEFINED_ESCAPE);return 29;}
<STRING>[\n\r]                                      { error_handle_ud_escape(1, ERROR_VALUE::UNKNOWN_CHAR);return 29;}
<STRING>[^\"\\]*\\x{DIGITX}{DIGITX}                 { handle_escape(yytext,  true);}
<STRING>[^\"\\]*\\x{DIGITX}                 { error_handle_ud_escape(2, ERROR_VALUE::UNDEFINED_ESCAPE); return 29;}


<STRING>\"                  { return_initial(); return 29;}
<STRING><<EOF>>             { string_data.ERROR_TYPE = ERROR_VALUE::UNCLOSED_STRING; return 29;}

.                           { string_data.ERROR_TYPE = ERROR_VALUE::UNKNOWN_CHAR; return 29;}

%%

void nl(){
    yylineno;
}

void pushString(std::string s) {
    string_data.str += s;
}

void handle_escape(char* cur_text, bool is_digit){
    pushString(cur_text);
    char target = 0;
    int index_replace = 2;
    int suffix_size = 1;
    if(is_digit == false){
        switch (cur_text[1])
        {
        case 'n':
            target = '\n';
            break;
        case 't':
            target = '\t';
            break;
        case 'r':
            target = '\r';
            break;
        case '0':
            target = '\0';
            break;
        case '\\':
            target = '\\';
            break;
        case '"':
            target = '"';
            break;

        default:
            break;
        }
    }
    else{
        target = stoi(string_data.str.substr(string_data.str.size() - 2), nullptr, 16);
        if(target > 0x7e || target < 0x20){
            //TO DO error
            return;
        }
        index_replace = 4;
        suffix_size = 3;
    }
    string_data.str[string_data.str.size() - index_replace] = target;
    string_data.str =string_data.str.substr(0, string_data.str.size() - suffix_size);
}

void return_initial(){
    BEGIN(INITIAL);
    pushString(yytext);
}

void error_handle_ud_escape(int error_length, ERROR_VALUE error_type){
    string_data.ERROR_TYPE = error_type;
    string_data.str = string_data.str.substr(string_data.str.size()-error_length, error_length);
}