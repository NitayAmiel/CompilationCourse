#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

enum tokentype {
    VOID = 1,
    INT,
    BYTE,
    BOOL,
    AND,
    OR,
    NOT,
    TRUE,
    FALSE,
    RETURN,
    IF,
    ELSE,
    WHILE,
    BREAK,
    CONTINUE,
    SC,
    COMMA,
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    ASSIGN,
    RELOP,
    BINOP,
    COMMENT,
    ID,
    NUM,
    NUM_B,
    STRING
};
enum ERROR_VALUE{
    NO_ERROR,
    UNKNOWN_CHAR,
    UNCLOSED_STRING,
    UNDEFINED_ESCAPE
};

extern int yylineno;
extern char *yytext;
extern int yyleng;

struct string_state{
    std::string str;
    ERROR_VALUE ERROR_TYPE;
};

extern struct string_state string_data ;
extern int yylex();

#endif //TOKENS_HPP
