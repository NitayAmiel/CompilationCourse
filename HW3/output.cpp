#include "output.hpp"
#include <iostream>

namespace output {
    /* Helper functions */

    static void check_error_definitons(std::shared_ptr<ast::Exp> node, int line = 0);

    static void check_error_definitons(std::shared_ptr<ast::Exp> node, int line){
        if(node == nullptr){
            return;
        }
        if(line == 0){
            line = node->line;
        }
        if(node->type == ast::BuiltInType::UN_DEF){
            errorUndef(line, std::dynamic_pointer_cast<ast::ID>(node)->value);
        }
        if(node->type == ast::BuiltInType::DEF_AS_FUNC){
            errorDefAsFunc(line, std::dynamic_pointer_cast<ast::ID>(node)->value);
        }
    }
    static bool matching_types (ast::BuiltInType x, ast::BuiltInType y){
        return (x == y ) || (x == ast::BuiltInType::INT && y == ast::BuiltInType::BYTE);
    }
    static bool is_numerical (ast::BuiltInType x){
        return (x == ast::BuiltInType::INT ||  x == ast::BuiltInType::BYTE);
    }
    static bool is_function (const  SymTableEntry * IdEntry){

        return ((IdEntry != nullptr) && (IdEntry->paramTypes.size() != 0));
    }

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

    static std::string toStringCapitalLetters(ast::BuiltInType type) {
        switch (type) {
            case ast::BuiltInType::INT:
                return "INT";
            case ast::BuiltInType::BOOL:
                return "BOOL";
            case ast::BuiltInType::BYTE:
                return "BYTE";
            case ast::BuiltInType::VOID:
                return "VOID";
            case ast::BuiltInType::STRING:
                return "STRING";
            default:
                return "UNKNOWN";
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
        VariableAttributes print_param_attributes = { "param", ast::BuiltInType::STRING , 0};
        std::vector<VariableAttributes> print_params = {print_param_attributes};
        VariableAttributes printi_param_attributes = { "param", ast::BuiltInType::INT , 0};
        std::vector<VariableAttributes> printi_params = {printi_param_attributes};
        this->insert_func("print", ast::BuiltInType::VOID, print_params);
        this->insert_func("printi", ast::BuiltInType::VOID, printi_params);
        //this->insert_func("printi", ast::BuiltInType::VOID, std::vector<ast::BuiltInType>({ast::BuiltInType::INT}));
        this->offset_table.push_back(0);
        

        // trying to manage from here
        this->first_run_on_function_declerations = true;
        this->in_while = 0;
    }


    void MyVisitor::visit(ast::Num &node) {
        node.type = ast::BuiltInType::INT;
    }

    void MyVisitor::visit(ast::NumB &node) {
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

    void MyVisitor::visit(ast::ID &node) { 
        const SymTableEntry* id_entry = id_exists(node.value);
        if(id_entry ){
            node.type = !is_function(id_entry) ? id_entry->ret_type : ast::BuiltInType::DEF_AS_FUNC;
        }else{
            node.type = ast::BuiltInType::UN_DEF;
        }
    }

    void MyVisitor::visit(ast::BinOp &node) {
        node.left->accept(*this);
        node.right->accept(*this);
        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(!is_numerical(node.left->type) || !is_numerical(node.right->type)){
            errorMismatch(node.line);
        }
        if(node.left->type == ast::BuiltInType::INT || node.right->type == ast::BuiltInType::INT) {
            node.type = ast::BuiltInType::INT;
        }else{
            node.type = ast::BuiltInType::BYTE;
        }
    }

    void MyVisitor::visit(ast::RelOp &node) {
        node.type = ast::BuiltInType::BOOL;

        node.left->accept(*this);
        node.right->accept(*this);
        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(!is_numerical(node.left->type) || !is_numerical(node.right->type)){
            errorMismatch(node.line);
        }
    }

    void MyVisitor::visit(ast::Type &node) { /*NOTHING*/ }

    void MyVisitor::visit(ast::Cast &node) {
        node.exp->accept(*this);
        node.target_type->accept(*this);
        ast::BuiltInType target = node.target_type->type;
        ast::BuiltInType casted = node.exp->type ;
        check_error_definitons(node.exp);
        if(casted == target){
            node.type = node.target_type->type;
            return;
        }
        if(!is_numerical(target) || !is_numerical(casted)) {
            errorMismatch(node.line);
        }
        node.type = node.target_type->type;
      
      /*  try {
        std::shared_ptr<ast::ID> id_obj = std::dynamic_pointer_cast<ast::ID>(node.exp);
        if (id_obj) {
            SymTableEntry* id_entry = id_exists_and_change(id_obj->value);
            if(!id_entry){
                errorUndef(node.line, id_obj->value);
            }
            if(is_function(id_entry)){
                errorDefAsFunc(node.line, id_obj->value);
            }
            id_entry->ret_type = target;
        } else {
            throw std::bad_cast();
        }
        }
        catch (const std::bad_cast&) {
            return;
        }*/
    }

    void MyVisitor::visit(ast::Not &node) {
        node.exp->accept(*this);
        check_error_definitons(node.exp);
        if(node.exp->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        node.type = ast::BuiltInType::BOOL;
    }

    void MyVisitor::visit(ast::And &node) {
        node.left->accept(*this);
        node.right->accept(*this);
        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(node.left->type != ast::BuiltInType::BOOL || node.right->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        
        node.type = ast::BuiltInType::BOOL;
    }

    void MyVisitor::visit(ast::Or &node) {
        node.left->accept(*this);
        node.right->accept(*this);
        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(node.left->type != ast::BuiltInType::BOOL || node.right->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        node.type = ast::BuiltInType::BOOL;
    }


// ----------------------------------------------------------------
// Nitay 
    void MyVisitor::visit(ast::ExpList &node) {
        for (auto it = node.exps.rbegin(); it != node.exps.rend(); ++it) {            
            (*it)->accept(*this);
        }
    }

    void MyVisitor::visit(ast::Call &node) {

        node.func_id->accept(*this);
        const SymTableEntry* id_entry = id_exists(node.func_id->value);
        if (!id_entry) {
            errorUndefFunc(node.line, node.func_id->value);
        }else if(is_function(id_entry) == false) {
            errorDefAsVar(node.line, node.func_id->value);
        }
        bool is_print = id_entry->name.find("print") != std::string::npos;
        node.args->accept(*this);
        std::vector<std::string> params_types ;
        for(auto param : id_entry->paramTypes) {
            if(!is_print && param.type == ast::BuiltInType::STRING) {
                errorMismatch(node.args->line);
            }
            params_types.push_back(toStringCapitalLetters(param.type));
        }
        for(std::shared_ptr<ast::Exp> param : node.args->exps){
            check_error_definitons(param, node.line);
            if(param->type == ast::BuiltInType::VOID){
                errorPrototypeMismatch(node.line, node.func_id->value, params_types);
            }
        }
        node.type = id_entry->ret_type;
        if(node.args->exps.size() == 0 &&  id_entry->paramTypes.at(0).type == ast::BuiltInType::VOID){
            return;
        }
        if(node.args->exps.size() != id_entry->paramTypes.size()) {
            errorPrototypeMismatch(node.line, node.func_id->value, params_types);
        }
        for(int i = 0; i < id_entry->paramTypes.size(); i++){
            if(!matching_types(id_entry->paramTypes[i].type,  node.args->exps[i]->type )){
                errorPrototypeMismatch(node.line, node.func_id->value, params_types);
            }
        }
    }





    void MyVisitor::visit(ast::Statements &node) {
        // maybe need to be removed
        if(node.in_middle_of_braces){
            this->begin_Scope();
        }
        ////////////////////////////////


        for (auto it = node.statements.begin(); it != node.statements.end(); ++it) {            
            (*it)->accept(*this);
        }

        // maybe need to be removed
        if(node.in_middle_of_braces){
            this->end_scope();
        }
        ////////////////////////////////
    }

    void MyVisitor::visit(ast::Break &node) {
        if (this->in_while == 0) {
            errorUnexpectedBreak(node.line);
        }
    }

    void MyVisitor::visit(ast::Continue &node) {
        if (this->in_while == 0) {
            errorUnexpectedContinue(node.line);
        }
    }


    void MyVisitor::visit(ast::Return &node) {
        if (node.exp) {
            node.exp->accept(*this);
            check_error_definitons(node.exp);
        }
        const SymTableEntry *id_entry = id_exists(this->current_function_name);
        ast::BuiltInType return_type = id_entry->ret_type;
        if(return_type == ast::BuiltInType::STRING){
            errorMismatch(node.line);
        }
        if ((node.exp && !matching_types(return_type, node.exp->type) ) || (node.exp == nullptr && return_type != ast::BuiltInType::VOID)){
            errorMismatch(node.line);
        }
    }

    void MyVisitor::visit(ast::If &node) {
        node.condition->accept(*this);
        if(node.otherwise){
            check_error_definitons(node.condition,  node.line);
        }else{
            check_error_definitons(node.condition,  node.then->line);
        }
        if(node.condition->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        this->begin_Scope();
        node.then->accept(*this);
        this->end_scope();

        if (node.otherwise) {
            this->begin_Scope();
            node.otherwise->accept(*this);
            this->end_scope();
        }
    }

    void MyVisitor::visit(ast::While &node) {
        node.condition->accept(*this); 
        check_error_definitons(node.condition,  node.line);
        if(node.condition->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        this->in_while++;
        this->begin_Scope();
        node.body->accept(*this);
        this->end_scope();
        this->in_while--;
    
    }

    void MyVisitor::visit(ast::VarDecl &node) {
        node.id->accept(*this);
        node.type->accept(*this);
        if(node.type->type == ast::BuiltInType::VOID){
            errorMismatch(node.line);
        }
        if (node.init_exp) {
            node.init_exp->accept(*this);
            check_error_definitons(node.init_exp);
            if(node.init_exp->type == ast::BuiltInType::STRING){
                errorMismatch(node.init_exp->line);
            }
            if(!matching_types(node.type->type , node.init_exp->type )){
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
        check_error_definitons(node.exp);
        if(node.exp->type == ast::BuiltInType::STRING){
            errorMismatch(node.exp->line);
        }
        const SymTableEntry* id_entry = id_exists(node.id->value);
        if(id_entry == nullptr) {
            errorUndef(node.line, node.id->value);    
        }else if(id_entry->paramTypes.size() > 0) {
            errorDefAsFunc(node.line, node.id->value);
        }else if(!matching_types( id_entry->ret_type , node.exp->type)){
            errorMismatch(node.line);
        }

    }

    void MyVisitor::visit(ast::Formal &node) {
        node.id->accept(*this);
        node.type->accept(*this);
    }

    void MyVisitor::visit(ast::Formals &node) {
        for (auto it = node.formals.rbegin(); it != node.formals.rend(); ++it) {
            (*it)->accept(*this);
        }

    }

    void MyVisitor::visit(ast::FuncDecl &node) {
        if(this->first_run_on_function_declerations){
            node.id->accept(*this);
            node.return_type->accept(*this);
            if(node.return_type->type == ast::BuiltInType::STRING){
                errorMismatch(node.return_type->line);
            }
            node.formals->accept(*this);

            std::vector<VariableAttributes> parameters;
            for(int i = 0 ; i < node.formals->formals.size(); ++i) {
                parameters.push_back({node.formals->formals[i]->id->value, node.formals->formals[i]->type->type, -(i+1)});
            }
            if(parameters.size() == 0){
                parameters.push_back({"dummy", ast::BuiltInType::VOID});
            }
            const SymTableEntry *entry = this->id_exists(node.id->value);
            if(entry) {
                errorDef(node.line, node.id->value);
            } else {
                this->insert_func(node.id->value, node.return_type->type, parameters);
            }
        
        }else{
            this->begin_Scope();
            this->current_function_name = node.id->value;
            const SymTableEntry * id_entry = this->id_exists(node.id->value);
            // TO DO 
            // maintain the offset and symtable
            
            
            const SymTableEntry * id_entry_of_param;
            for(int i = 0 ; i < id_entry->paramTypes.size(); i++){
                VariableAttributes param = id_entry->paramTypes[i];
                id_entry_of_param = this->id_exists(param.name);
                if(id_entry_of_param){
                    if(is_function(id_entry_of_param)){
                        errorDefAsFunc(node.line, param.name);
                    }else{
                        errorDef(node.line, param.name);
                    }
                }
                if(param.type == ast::BuiltInType::VOID){
                    break;
                }
                this->insert_variable(param.name, param.type, &param.offset);
                //this->scope_printer.emitVar(param.name, param.type, param.offset);
            }
            node.body->accept(*this);
            this->end_scope();
        }
    }

    void MyVisitor::visit(ast::Funcs &node) {

        for (auto it = node.funcs.begin(); it != node.funcs.end(); ++it) {
            (*it)->accept(*this);
        }
        const SymTableEntry* id_entry = id_exists("main");
        if(id_entry == nullptr || !is_function(id_entry) || id_entry->ret_type != ast::BuiltInType::VOID || id_entry->paramTypes.size() > 1 || id_entry->paramTypes.at(0).type != ast::BuiltInType::VOID) {
                errorMainMissing();
        }
        this->first_run_on_function_declerations = false;
        for (auto it = node.funcs.begin(); it != node.funcs.end(); ++it) {
            (*it)->accept(*this);
        }
    }

    void MyVisitor :: insert_variable(std::string name, ast::BuiltInType type, const int* offset_ptr) 
    {
        int offset = offset_ptr ? *offset_ptr : this->offset_table.back();
        std::vector<VariableAttributes> dummy;
        SymTableEntry element = {name, type, dummy, offset};
        this->sym_table.back().push_back(element);
        this->scope_printer.emitVar(name, type, offset);
        if(offset_ptr == nullptr) {
            this->offset_table.back()+= SIZE_OF_TYPE;
        }
    }

    void MyVisitor :: insert_func(std::string name, ast::BuiltInType return_type , std::vector<VariableAttributes> params)
    {
        SymTableEntry element = {name, return_type, params, 0};
        this->sym_table.front().push_back(element);
        std::vector<ast::BuiltInType> params_array;
        for(auto const &param : params){
            if(param.type == ast::BuiltInType::VOID){
                break;
            }
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

    SymTableEntry * MyVisitor :: id_exists_and_change(std::string name)
    {
        for(auto  & s : this->sym_table){
            for(auto  &d : s){
                if(d.name == name){
                    return &d;
                }
            }
        }

        return nullptr;
    }


}

