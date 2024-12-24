#include "output.hpp"
#include <iostream>

namespace output {
    /* Helper functions */

    static std::string toString(ast::BuiltInType type) {
        switch (type) {
            case ast::BuiltInType::INT:
                return "int";
            case ast::BuiltInType::BOOL:
                return "bool";
            case ast::BuiltInType::BYTE:
                return "byte";
            case ast::BuiltInType::VOID:
                return "void";
            case ast::BuiltInType::STRING:
                return "string";
            default:
                return "unknown";
        }
    }

    /* Error handling functions */

    void errorLex(int lineno) {
        std::cout << "line " << lineno << ": lexical error\n";
        exit(0);
    }

    void errorSyn(int lineno) {
        std::cout << "line " << lineno << ": syntax error\n";
        exit(0);
    }

    void errorUndef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " variable " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorDefAsFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a function" << std::endl;
        exit(0);
    }

    void errorDefAsVar(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is a variable" << std::endl;
        exit(0);
    }

    void errorDef(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " symbol " << id << " is already defined" << std::endl;
        exit(0);
    }

    void errorUndefFunc(int lineno, const std::string &id) {
        std::cout << "line " << lineno << ":" << " function " << id << " is not defined" << std::endl;
        exit(0);
    }

    void errorMismatch(int lineno) {
        std::cout << "line " << lineno << ":" << " type mismatch" << std::endl;
        exit(0);
    }

    void errorPrototypeMismatch(int lineno, const std::string &id, std::vector<std::string> &paramTypes) {
        std::cout << "line " << lineno << ": prototype mismatch, function " << id << " expects parameters (";

        for (int i = 0; i < paramTypes.size(); ++i) {
            std::cout << paramTypes[i];
            if (i != paramTypes.size() - 1)
                std::cout << ",";
        }

        std::cout << ")" << std::endl;
        exit(0);
    }

    void errorUnexpectedBreak(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected break statement" << std::endl;
        exit(0);
    }

    void errorUnexpectedContinue(int lineno) {
        std::cout << "line " << lineno << ":" << " unexpected continue statement" << std::endl;
        exit(0);
    }

    void errorMainMissing() {
        std::cout << "Program has no 'void main()' function" << std::endl;
        exit(0);
    }

    void errorByteTooLarge(int lineno, const int value) {
        std::cout << "line " << lineno << ": byte value " << value << " out of range" << std::endl;
        exit(0);
    }

    /* ScopePrinter class */

    ScopePrinter::ScopePrinter() : indentLevel(0) {}

    std::string ScopePrinter::indent() const {
        std::string result;
        for (int i = 0; i < indentLevel; ++i) {
            result += "  ";
        }
        return result;
    }

    void ScopePrinter::beginScope() {
        indentLevel++;
        buffer << indent() << "---begin scope---" << std::endl;
    }

    void ScopePrinter::endScope() {
        buffer << indent() << "---end scope---" << std::endl;
        indentLevel--;
    }

    void ScopePrinter::emitVar(const std::string &id, const ast::BuiltInType &type, int offset) {
        buffer << indent() << id << " " << toString(type) << " " << offset << std::endl;
    }

    void ScopePrinter::emitFunc(const std::string &id, const ast::BuiltInType &returnType,
                                const std::vector<ast::BuiltInType> &paramTypes) {
        globalsBuffer << id << " " << "(";

        for (int i = 0; i < paramTypes.size(); ++i) {
            globalsBuffer << toString(paramTypes[i]);
            if (i != paramTypes.size() - 1)
                globalsBuffer << ",";
        }

        globalsBuffer << ")" << " -> " << toString(returnType) << std::endl;
    }

    std::ostream &operator<<(std::ostream &os, const ScopePrinter &printer) {
        os << "---begin global scope---" << std::endl;
        os << printer.globalsBuffer.str();
        os << printer.buffer.str();
        os << "---end global scope---" << std::endl;
        return os;
    }



    MyVisitor::MyVisitor(){
        std::vector<SymTableEntry> initial_vector;
        this->sym_table.push_back(initial_vector);
        this->insert_func("print", ast::BuiltInType::VOID, std::vector<ast::BuiltInType>({ast::BuiltInType::STRING}));
        this->insert_func("printi", ast::BuiltInType::VOID, std::vector<ast::BuiltInType>({ast::BuiltInType::INT}));
        this->offset_table.push_back(0);
        
    }


// TO DO  :  updating the Exp->type
    void MyVisitor::visit(ast::Num &node) {
        node.type = ast::BuiltInType::INT;
    }

    void MyVisitor::visit(ast::NumB &node) {
        // to check sizes of numb
        if(node.value > 127 || node.value < -128) {
            errorByteTooLarge(node.line, node.value);
        }
        node.type = ast::BuiltInType::BYTE;
    }

    void MyVisitor::visit(ast::String &node) {
        node.type = ast::BuiltInType::STRING;
    }

    void MyVisitor::visit(ast::Bool &node) {
        node.type = ast::BuiltInType::BOOL;
    }

    void MyVisitor::visit(ast::ID &node) { /* NOTHING? */}

    void MyVisitor::visit(ast::BinOp &node) {
        std::string op;
        node.type = ast::BuiltInType::BOOL;

        switch (node.op) {
            case ast::BinOpType::ADD:
                op = "+";
                break;
            case ast::BinOpType::SUB:
                op = "-";
                break;
            case ast::BinOpType::MUL:
                op = "*";
                break;
            case ast::BinOpType::DIV:
                op = "/";
                break;
        }

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::RelOp &node) {
        std::string op;

        switch (node.op) {
            case ast::RelOpType::EQ:
                op = "==";
                break;
            case ast::RelOpType::NE:
                op = "!=";
                break;
            case ast::RelOpType::LT:
                op = "<";
                break;
            case ast::RelOpType::LE:
                op = "<=";
                break;
            case ast::RelOpType::GT:
                op = ">";
                break;
            case ast::RelOpType::GE:
                op = ">=";
                break;
        }

        print_indented("RelOp: " + op);

        enter_child();
        node.left->accept(*this);
        leave_child();


        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::Type &node) {
        print_indented("Type: " + toString(node.type));
    }

    void MyVisitor::visit(ast::Cast &node) {
        print_indented("Cast");

        enter_child();
        node.exp->accept(*this);
        leave_child();

        enter_last_child();
        node.target_type->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::Not &node) {
        print_indented("Not");

        enter_last_child();
        node.exp->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::And &node) {
        print_indented("And");

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::Or &node) {
        print_indented("Or");

        enter_child();
        node.left->accept(*this);
        leave_child();

        enter_last_child();
        node.right->accept(*this);
        leave_child();
    }


// ----------------------------------------------------------------
// Nitay 
    void MyVisitor::visit(ast::ExpList &node) {
        print_indented("ExpList");

        for (auto it = node.exps.rbegin(); it != node.exps.rend(); ++it) {
            if (it != node.exps.rend() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void MyVisitor::visit(ast::Call &node) {
        print_indented("Call");

        enter_child();
        node.func_id->accept(*this);
        leave_child();

        enter_last_child();
        node.args->accept(*this);
        leave_child();
    }



    void MyVisitor::visit(ast::Statements &node) {
        print_indented("Statements");

        for (auto it = node.statements.begin(); it != node.statements.end(); ++it) {
            if (it != node.statements.end() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

// Shaychuck
    void MyVisitor::visit(ast::Break &node) {
        print_indented("Break");
    }

    void MyVisitor::visit(ast::Continue &node) {
        print_indented("Continue");
    }


// Nitay ush
    void MyVisitor::visit(ast::Return &node) {
        print_indented("Return");

        if (node.exp) {
            enter_last_child();
            node.exp->accept(*this);
            leave_child();
        }
    }

    void MyVisitor::visit(ast::If &node) {
        print_indented("If");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_child();
        } else {
            enter_last_child();
        }
        node.then->accept(*this);
        leave_child();

        if (node.otherwise) {
            enter_last_child();
            node.otherwise->accept(*this);
            leave_child();
        }
    }

    void MyVisitor::visit(ast::While &node) {
        print_indented("While");

        enter_child();
        node.condition->accept(*this);
        leave_child();

        enter_last_child();
        node.body->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::VarDecl &node) {
        node.id->accept(*this);
        node.type->accept(*this);
        if (node.init_exp) {
            node.init_exp->accept(*this);
            if(node.init_exp->type != node.type->type){
                errorMismatch(node.line);
            }
        }
        const SymTableEntry* id_entry = id_exists(node.id->value);
        if(id_entry ) {
            if(id_entry->paramTypes.size() == 0) {
                errorDef(node.line, node.id->value);
            }else{
                errorDefAsFunc(node.line, node.id->value);
            }
        }
        insert_variable(node.id->value, node.type->type);
    }

    void MyVisitor::visit(ast::Assign &node) {
        node.id->accept(*this);
        node.exp->accept(*this);
        const SymTableEntry* id_entry = id_exists(node.id->value);
        if(id_entry == nullptr) {
            errorUndef(node.line, node.id->value);    
        }else if(id_entry->paramTypes.size() > 0) {
            errorDefAsFunc(node.line, node.id->value);
        }else if(id_entry->ret_type != node.exp->type){
            errorMismatch(node.line);
        }

    }

    void MyVisitor::visit(ast::Formal &node) {
        print_indented("Formal");

        enter_child();
        node.id->accept(*this);
        leave_child();

        enter_last_child();
        node.type->accept(*this);
        leave_child();
    }

    void MyVisitor::visit(ast::Formals &node) {
        for (auto it = node.formals.rbegin(); it != node.formals.rend(); ++it) {
            (*it)->accept(*this);
        }
    }

    void MyVisitor::visit(ast::FuncDecl &node) {
        node.id->accept(*this);
        node.return_type->accept(*this);
        node.formals->accept(*this);

        std::vector<VariableAttributes> parameters;
        for(int i = 0 ; i < node.formals->formals.size(); ++i) {
            parameters.push_back({node.formals->formals[i]->id->value, node.formals->formals[i]->type->type, -i});
        }

        const SymTableEntry *entry = this->id_exists(node.id->value);
        if(entry) {
            errorDef(node.line, node.id->value);
        } else {
            this->insert_func(node.id->value, node.return_type->type, parameters);
        }
        node.body->accept(*this);
    }

    void MyVisitor::visit(ast::Funcs &node) {
        print_indented("Funcs");

        for (auto it = node.funcs.begin(); it != node.funcs.end(); ++it) {
            if (it != node.funcs.end() - 1) {
                enter_child();
            } else {
                enter_last_child();
            }
            (*it)->accept(*this);
            leave_child();
        }
    }

    void MyVisitor :: insert_variable(std::string name, ast::BuiltInType type)
    {
        int offset = this->offset_table.back();
        std::vector<VariableAttributes> dummy;
        SymTableEntry element = {name, type, dummy, offset};
        this->sym_table.back().push_back(element);
        this->scope_printer.emitVar(name, type, offset);
        this->offset_table.back()+= SIZE_OF_TYPE;
    }

    void MyVisitor :: insert_func(std::string name, ast::BuiltInType return_type , std::vector<VariableAttributes> params)
    {
        SymTableEntry element = {name, return_type, params, 0};
        this->sym_table.front().push_back(element);
        std::vector<ast::BuiltInType> params_array;
        for(auto const &param : params){
            params_array.push_back(param.type);
        }
        this->scope_printer.emitFunc(name, return_type, params_array);
    }

    void MyVisitor :: begin_Scope()
    {
        std::vector<SymTableEntry> initial_vector;
        this->sym_table.push_back(initial_vector);
        this->offset_table.push_back(this->offset_table.back());
        this->scope_printer.beginScope();
    }

    void MyVisitor :: end_scope()
    {
        this->sym_table.pop_back();
        this->offset_table.pop_back();
        this->scope_printer.endScope();

    }

    const SymTableEntry * MyVisitor :: id_exists(std::string name)
    {
        for(auto const & s : this->sym_table){
            for(auto const &d : s){
                if(d.name == name){
                    return &d;
                }
            }
        }

        return nullptr;
    }


}

