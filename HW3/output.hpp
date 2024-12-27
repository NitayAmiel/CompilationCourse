#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <map>

#include <string>
#include <sstream>
#include "visitor.hpp"
#include "nodes.hpp"

const unsigned int SIZE_OF_TYPE = 1;
namespace output {
    /* Error handling functions */

    void errorLex(int lineno);

    void errorSyn(int lineno);

    void errorUndef(int lineno, const std::string &id);

    void errorDefAsFunc(int lineno, const std::string &id);

    void errorUndefFunc(int lineno, const std::string &id);

    void errorDefAsVar(int lineno, const std::string &id);

    void errorDef(int lineno, const std::string &id);

    void errorPrototypeMismatch(int lineno, const std::string &id, std::vector<std::string> &paramTypes);

    void errorMismatch(int lineno);

    void errorUnexpectedBreak(int lineno);

    void errorUnexpectedContinue(int lineno);

    void errorMainMissing();

    void errorByteTooLarge(int lineno, int value);

    /* ScopePrinter class
     * This class is used to print scopes in a human-readable format.
     */
    class ScopePrinter {
    private:
        std::stringstream globalsBuffer;
        std::stringstream buffer;
        int indentLevel;
        
        std::string indent() const;

    public:
        ScopePrinter();

        void beginScope();

        void endScope();

        void emitVar(const std::string &id, const ast::BuiltInType &type, int offset);

        void emitFunc(const std::string &id, const ast::BuiltInType &returnType,
                      const std::vector<ast::BuiltInType> &paramTypes);

        friend std::ostream &operator<<(std::ostream &os, const ScopePrinter &printer);
    };

    
    typedef struct
    {
        std::string name;
        ast::BuiltInType type;
        int offset;
    }  VariableAttributes ;
    
    typedef struct
    {
        std::string name;
        ast::BuiltInType ret_type;
        std::vector<VariableAttributes> paramTypes;
        int offset;
    }  SymTableEntry ;

    typedef struct
    {
        // TO DO
    }  TypeTableEntry ;
    
    class MyVisitor : public Visitor {
    private:
        std::vector<std::vector<SymTableEntry>> sym_table;
        std::vector<int> offset_table;
        std::map<std::string, TypeTableEntry> type_table;
        ScopePrinter scope_printer;
        std::string current_function_name;
        unsigned int in_while;
        bool first_run_on_function_declerations;

        /* Helper function to print a string with the current indentation */
        //void print_indented(const std::string &str);

        /* Functions to manage the indentation level */
        // void enter_child();

        // void enter_last_child();

        // void leave_child();
        void insert_variable(std::string name, ast::BuiltInType type);
        void MyVisitor :: insert_func(std::string name, ast::BuiltInType return_type , std::vector<VariableAttributes> params);
        void begin_Scope();
        void end_scope();
        const SymTableEntry* id_exists(std::string name);
        SymTableEntry * MyVisitor :: id_exists_and_change(std::string name);

       // bool resolved_forward_references();

    public:
        MyVisitor();

        void visit(ast::Num &node) override;

        void visit(ast::NumB &node) override;

        void visit(ast::String &node) override;

        void visit(ast::Bool &node) override;

        void visit(ast::ID &node) override;

        void visit(ast::BinOp &node) override;

        void visit(ast::RelOp &node) override;

        void visit(ast::Not &node) override;

        void visit(ast::And &node) override;

        void visit(ast::Or &node) override;

        void visit(ast::Type &node) override;

        void visit(ast::Cast &node) override;

        void visit(ast::ExpList &node) override;

        void visit(ast::Call &node) override;

        void visit(ast::Statements &node) override;

        void visit(ast::Break &node) override;

        void visit(ast::Continue &node) override;

        void visit(ast::Return &node) override;

        void visit(ast::If &node) override;

        void visit(ast::While &node) override;

        void visit(ast::VarDecl &node) override;

        void visit(ast::Assign &node) override;

        void visit(ast::Formal &node) override;

        void visit(ast::Formals &node) override;

        void visit(ast::FuncDecl &node) override;

        void visit(ast::Funcs &node) override;
    };
}



#endif //OUTPUT_HPP
