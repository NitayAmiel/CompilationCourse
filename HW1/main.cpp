#include "tokens.hpp"
#include "output.hpp"


typedef tokentype tokentype;
int main() {
    enum tokentype token;

    // read tokens until the end of file is reached
    while ((token = static_cast<tokentype>(yylex()))) {
        // your code here
        
        
        output::printToken(yylineno, token, yytext); 
    }
    return 0;
}

//\"[^"\\\n\r]*\"           {return 29;}