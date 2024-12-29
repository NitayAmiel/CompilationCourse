#include "nodes.hpp"
#include "output.hpp"
#include <iostream>

// Extern from the bison-generated parser
extern int yyparse();

extern std::shared_ptr<ast::Node> program;

int main() {
    // Parse the input. The result is stored in the global variable `program`
    yyparse();
    // Print the AST using the PrintVisitor
    output::MyVisitor Visitor;
    program->accept(Visitor);
    std::cout << Visitor.scope_printer;
}
