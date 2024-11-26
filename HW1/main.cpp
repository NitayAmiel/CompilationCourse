#include "tokens.hpp"
#include "output.hpp"


typedef tokentype tokentype;
int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        const char* print_msg = yytext;
        if(token == tokentype::STRING){
            print_msg = string_data.str.c_str();
        }
        
        output::printToken(yylineno, token, print_msg); 
    }
    return 0;
}


//\"[^"\\\n\r]*\"           {return 29;}

/*
<STRING>[^\"\\]*\\n          { handle_escape(yytext, '\n');}
<STRING>[^\"\\]*\\t          { handle_escape(yytext, '\t');}
<STRING>[^\"\\]*\\r          { handle_escape(yytext, '\r');}
<STRING>[^\"\\]*\\0          { handle_escape(yytext, 0);}
<STRING>[^\"\\]*\\\\          { handle_escape(yytext, '\');}
<STRING>[^\"\\]*\\          { handle_escape(yytext, 0);}
*/