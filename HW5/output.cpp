#include "output.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace output {
    /* Helper functions */
    void CodeBuffer::insert_str_divide_by_0(std::string reg_name, std::string error_msg){
        std::string tmp_reg = this->freshVar();
        std::string tmp_error_msg_reg = this->freshVar();
        std::string non_zero_label = this->freshLabel();
        std::string zero_label = this->freshLabel();

        std::string res = tmp_reg + " = icmp eq i32 " + reg_name + ", 0\n";
        res +=" br i1 " + tmp_reg + ", label " +  zero_label + ", label " + non_zero_label + "\n";
        this->emit(res);
        this->emitLabel(zero_label);
        res =  tmp_error_msg_reg + " = getelementptr  [" +  std::to_string(MESSAGE_ERROR_SIZE) + " x i8], [" + std::to_string(MESSAGE_ERROR_SIZE) + " x i8]* " +  + ", i32 0, i32 0\n";
        res += "call void @print(i8* " + tmp_error_msg_reg + "\n call void @exit(i32 1)\n";
        res+= "br label " + non_zero_label + "\n";
        this->emit(res);
        this->emitLabel(non_zero_label);
    }
    // static std::string check_str_divide_by_0(std::string reg_name, std::string tmp_reg,  std::string error_msg){
    //     int size_of_str = MESSAGE_ERROR_SIZE;
    //     std::string res = tmp_reg + " = icmp eq i32 " + reg_name + ", 0\n";
    //     res +=" br i1 " + tmp_reg + ", label %zero_case, label %non_zero_case\n";
    //     res += "zero_case:\n %msg_ptr = getelementptr  [" +  std::to_string(size_of_str) + " x i8], [" + std::to_string(size_of_str) + " x i8]* " + error_msg + ", i32 0, i32 0\n call void @print(i8* %msg_ptr)\n call void @exit(i32 1)\n br label %non_zero_case\n non_zero_case:\n";
    //     return res; 
    // }

    
    
    static std::string get_register_name(const SymTableEntry& id_entry ){
        return "%" + std::to_string(-(id_entry.offset+1));
    }

    static bool defined_as_parameter(const SymTableEntry& id_entry){
        return id_entry.offset < 0;
    }
    static std::string loadFileContent(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open file: " + filename);
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }

    static bool return_occured(const std::string & str_func){
        return str_func.empty();
    }
    static void signal_return_occured( std::string & str_func){
        str_func = "";
    }


    // static std::string create_def_func( ast::BuiltInType ret_type,std::string name, std::vector<ast::BuiltInType>& args){
    //     std::string res = "define " + get_type_string(ret_type) + "@" + name + "(" ;
       
    //     }
    // }
    static std::string op_to_string(ast::RelOpType type) {
        switch (type) {
            case ast::RelOpType::EQ:
                return "eq";
            case ast::RelOpType::NE:
                return "ne";
            case ast::RelOpType::LT:
                return "lt";
            case ast::RelOpType::GT:
                return "gt";
            case ast::RelOpType::LE:
                return "le";
            case ast::RelOpType::GE:
                return "ge";
        }
    }

    static std::string _get_type_string(ast::BuiltInType type){
        switch(type){
            case ast::BuiltInType::INT:
                return "i32";
            case ast::BuiltInType::BYTE:
                return "i8";
            case ast::BuiltInType::BOOL:
                return "i1";
            case ast::BuiltInType::VOID:
                return "void";
            case ast::BuiltInType::STRING:
                return "i8*";
                //TODO
        }
    }

    static std::string get_type_string(ast::BuiltInType type){
        return _get_type_string(type) + " ";
    }

    static std::string get_ptr_type_string(ast::BuiltInType type){
        return _get_type_string(type) + "* ";
    }

    static std::string create_string_of_params(std::vector<ast::BuiltInType>& args){
         
        bool first_param = true;
        std::string res = "(";
        for(auto const &param : args){
            if(param == ast::BuiltInType::VOID){
                break;
            }
            if(!first_param){
                res += ", ";
            }else{
                first_param = false;
            }
            res += get_type_string(param);
        }
        res += ")";
        return res;
    }

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


    CodeBuffer::CodeBuffer() : labelCount(0), varCount(0), stringCount(0) {}

    std::string CodeBuffer::freshLabel() {
        return "%label_" + std::to_string(labelCount++);
        //return "label_" + std::to_string(labelCount++);
    }

    std::string CodeBuffer::freshVar() {
        return "%t" + std::to_string(varCount++);
    }

    std::string CodeBuffer::emitString(const std::string &str) {
        std::string var = "@.str" + std::to_string(stringCount++);
        globalsBuffer << var << " = constant [" << str.length() + 1 << " x i8] c\"" << str << "\\00\"";
        return var;
    }

    void CodeBuffer::emit(const std::string &str) {
        buffer << str << std::endl;
    }

    void CodeBuffer::emitLabel(const std::string &label) {
        buffer << label.substr(1) << ":" << std::endl;
    }

    CodeBuffer &CodeBuffer::operator<<(std::ostream &(*manip)(std::ostream &)) {
        buffer << manip;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer) {
        os << buffer.globalsBuffer.str() << std::endl << buffer.buffer.str();
        return os;
    }


    MyVisitor::MyVisitor(){
        this->code_buffer.emit(loadFileContent("print_functions.llvm"));
        this->error_msg_divide_0_ptr = this->code_buffer.emitString("Error division by zero");
        std::vector<SymTableEntry> initial_vector;
        this->sym_table.push_back(initial_vector);
        VariableAttributes print_param_attributes = { "param", ast::BuiltInType::STRING , 0};
        std::vector<VariableAttributes> print_params = {print_param_attributes};
        VariableAttributes printi_param_attributes = { "param", ast::BuiltInType::INT , 0};
        std::vector<VariableAttributes> printi_params = {printi_param_attributes};

        bool no_need_print_decl_defs = true;
        this->insert_func("print", ast::BuiltInType::VOID, print_params, no_need_print_decl_defs);
        this->insert_func("printi", ast::BuiltInType::VOID, printi_params, no_need_print_decl_defs);
        //this->insert_func("printi", ast::BuiltInType::VOID, std::vector<ast::BuiltInType>({ast::BuiltInType::INT}));
        this->offset_table.push_back(0);
        

        // trying to manage from here
        this->first_run_on_function_declerations = true;
        this->in_while = 0;
    }


    void MyVisitor::visit(ast::Num &node) {
        node.type = ast::BuiltInType::INT;

        node.reg = std::to_string(node.value);
    }

    void MyVisitor::visit(ast::NumB &node) {
        if(node.value > 255 ) {
            errorByteTooLarge(node.line, node.value);
        }
        node.type = ast::BuiltInType::BYTE;


        node.reg = this->code_buffer.freshVar();
        this->code_buffer.emit(node.reg + " = add i8 0, " + std::to_string(node.value));
    }

    void MyVisitor::visit(ast::String &node) {
        node.type = ast::BuiltInType::STRING;

        node.reg = this->code_buffer.freshVar();
        
        std::string var = this->code_buffer.emitString(node.value);
        this->code_buffer.emit(node.reg + " = getelementptr [" + std::to_string(node.value.length() + 1) + " x i8], [" + std::to_string(node.value.length() + 1) + " x i8]* " + var + ", i32 0, i32 0");
    }

    void MyVisitor::visit(ast::Bool &node) {
        node.type = ast::BuiltInType::BOOL;

        node.reg = this->code_buffer.freshVar();
        this->code_buffer.emit(node.reg + " = add i1 0, " + (node.value ? "true" : "false"));
    }

    void MyVisitor::visit(ast::ID &node) { 
        const SymTableEntry* id_entry = id_exists(node.value);
        if(id_entry ) {
            node.type = !is_function(id_entry) ? id_entry->ret_type : ast::BuiltInType::DEF_AS_FUNC;
            if(node.type != ast::BuiltInType::DEF_AS_FUNC) {
                if(defined_as_parameter(*id_entry)){
                    node.reg = get_register_name(*id_entry);
                    //this->code_buffer.emit(node.reg + " = load " + get_type_string(node.type) + ", " + get_type_string(node.type) + get_register_name(*id_entry));
                }
                else {
                node.reg = this->code_buffer.freshVar();
                this->code_buffer.emit(node.reg + " = load " + get_type_string(node.type) + ", " + get_ptr_type_string(node.type) +  "%v" + node.value);
                }
            }
        }else {
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

        std::string type_string = get_type_string(node.type);

        node.reg = this->code_buffer.freshVar();
        switch (node.op) {
            case ast::BinOpType::ADD:
                this->code_buffer.emit( node.reg + " = add "  + get_type_string(node.type) + node.left->reg + ", " + node.right->reg  );
                break;
            case ast::BinOpType::SUB:
                this->code_buffer.emit( node.reg + " = sub "  + get_type_string(node.type) + node.left->reg + ", " + node.right->reg  );
                break;
            case ast::BinOpType::MUL:
                this->code_buffer.emit( node.reg + " = mul "  + get_type_string(node.type) + node.left->reg + ", " + node.right->reg  );
                break;
            case ast::BinOpType::DIV:
                this->code_buffer.insert_str_divide_by_0(node.right->reg, this->error_msg_divide_0_ptr);
                if(node.type == ast::BuiltInType::INT) {
                    this->code_buffer.emit(
                            node.reg + " = sdiv " + get_type_string(node.type) + node.left->reg + ", " + node.right->reg);
                }
                else {
                    this->code_buffer.emit(
                            node.reg + " = udiv " + get_type_string(node.type) + node.left->reg + ", " + node.right->reg);
                }
                break;
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

        ast::BuiltInType op_type = ast::BuiltInType::BYTE;
        if(node.left->type == ast::BuiltInType::INT || node.right->type == ast::BuiltInType::INT) {
            op_type = ast::BuiltInType::INT;
        }

        node.reg = code_buffer.freshVar();
        std::string singed_letter = op_type == ast::BuiltInType::BYTE ? "u" : "s";
        code_buffer.emit(node.reg + " = icmp " + singed_letter + op_to_string(node.op)
                            + get_type_string(op_type) + node.left->reg + ", " + node.right->reg);
        //code_buffer.emit("br i1 " + node.reg + " label " + node.true_label + " label " + node.false_label);
    }

    void MyVisitor::visit(ast::Type &node) { /*NOTHING*/ }

    void MyVisitor::visit(ast::Cast &node) {
        node.exp->accept(*this);
        node.target_type->accept(*this);
        ast::BuiltInType target = node.target_type->type;
        ast::BuiltInType casted = node.exp->type ;
        check_error_definitons(node.exp);
        /*if(casted == target){
            node.type = node.target_type->type;
            return;
        }*/
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
        std::string true_label = node.exp->true_label;
        node.exp->true_label = node.exp->false_label;
        node.exp->false_label = true_label;
        node.exp->accept(*this);
        check_error_definitons(node.exp);
        if(node.exp->type != ast::BuiltInType::BOOL){
            errorMismatch(node.exp->line);
        }
        node.type = ast::BuiltInType::BOOL;
    }

    void MyVisitor::visit(ast::And &node) {
        // node.left->true_label = code_buffer.freshLabel();
        // node.left->false_label = node.false_label;
        node.left->accept(*this);

        if(!node.false_label.empty()) {
            node.true_label = this->code_buffer.freshLabel();
            this->code_buffer.emit("br i1 " + node.left->reg + " ,label " + node.true_label + " ,label " + node.false_label);
            this->code_buffer.emitLabel(node.true_label);
        }



       // this->code_buffer.emitLabel(node.left->true_label);
        // node.right->true_label = node.true_label;
        // node.right->false_label = node.false_label;

        node.right->accept(*this);

        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(node.left->type != ast::BuiltInType::BOOL){
            errorMismatch(node.left->line);
        }
        if(node.right->type != ast::BuiltInType::BOOL){
            errorMismatch(node.right->line);
        }
    
        node.type = ast::BuiltInType::BOOL;

        node.reg = this->code_buffer.freshVar();
        this->code_buffer.emit(node.reg + " = and " + get_type_string(node.type) + node.left->reg + ", " + node.right->reg);
    }

    void MyVisitor::visit(ast::Or &node) {
        node.left->accept(*this);
        if(!node.true_label.empty()) {
            node.false_label = this->code_buffer.freshLabel();
            this->code_buffer.emit("br i1 " + node.left->reg + " ,label " + node.true_label + " ,label " + node.false_label);
            this->code_buffer.emitLabel(node.false_label);
        }


        //node.left->true_label = node.true_label;
        //node.left->false_label = code_buffer.freshLabel();


        // code_buffer.emitLabel(node.left->false_label);
        // node.right->true_label = node.true_label;
        // node.right->false_label = node.false_label;

        node.right->accept(*this);
        check_error_definitons(node.left);
        check_error_definitons(node.right);
        if(node.left->type != ast::BuiltInType::BOOL || node.right->type != ast::BuiltInType::BOOL){
            errorMismatch(node.line);
        }
        node.type = ast::BuiltInType::BOOL;
    
        node.reg = this->code_buffer.freshVar();
        this->code_buffer.emit(node.reg + " = or " + get_type_string(node.type) + node.left->reg + ", " + node.right->reg);
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
            check_error_definitons(param);//, node.line);
            if(param->type == ast::BuiltInType::VOID){
                errorPrototypeMismatch(node.line, node.func_id->value, params_types);
            }
        }
        node.type = id_entry->ret_type;
        if(node.args->exps.size() == 0 &&  id_entry->paramTypes.at(0).type == ast::BuiltInType::VOID){
            goto llvm_part;
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
    llvm_part:
        std::string cmd_string ;
        if(id_entry->ret_type == ast::BuiltInType::VOID){
            cmd_string = "call " + get_type_string(id_entry->ret_type) + "@" + id_entry->name + "(";
        }else{
            node.reg = this->code_buffer.freshVar();
            cmd_string = node.reg + " = call " + get_type_string(id_entry->ret_type) + "@" + id_entry->name + "(";
        }
        bool first_param = true;
        for(auto param : node.args->exps){
            if(param->type == ast::BuiltInType::VOID){
                break;
            }
            if(!first_param){
                cmd_string += ", ";
            }else{
                first_param = false;
            }
            cmd_string += get_type_string(param->type);
            cmd_string += param->reg;
        }
        cmd_string += ")";
        this->code_buffer.emit(cmd_string);

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
        //code_buffer.emit("br label " + node.next_label);
        if(node.in_middle_of_braces){
            this->end_scope();
        }
        ////////////////////////////////
    }

    void MyVisitor::visit(ast::Break &node) {
        if (this->in_while == 0) {
            errorUnexpectedBreak(node.line);
        }
        code_buffer.emit("br label " + exit_label);
    }

    void MyVisitor::visit(ast::Continue &node) {
        if (this->in_while == 0) {
            errorUnexpectedContinue(node.line);
        }
        code_buffer.emit("br label " + loop_head_label);
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
        
        std::string return_str = "ret " + get_type_string(return_type);
        if(node.exp){
            return_str += node.exp->reg;
        }
        this->code_buffer.emit(return_str);
        signal_return_occured(this->current_function_name);
    }

    void MyVisitor::visit(ast::If &node) {

        std::string if_next_true_label = code_buffer.freshLabel();
        std::string if_next_false_label = code_buffer.freshLabel();
        std::string next_label = node.otherwise ? this->code_buffer.freshLabel() : if_next_false_label;

        node.condition->true_label =if_next_true_label; 
        node.condition->false_label =if_next_false_label; 
        node.condition->accept(*this);
        code_buffer.emit("br i1 " + node.condition->reg + " ,label " + if_next_true_label + " ,label " + if_next_false_label);
        this->code_buffer.emitLabel(if_next_true_label);
        // node.condition->true_label = code_buffer.freshLabel();
        // node.condition->false_label = node.otherwise ? code_buffer.freshLabel() : node.condition->true_label;
         //node.then->next_label = code_buffer.freshLabel();
        // if(node.otherwise){
        //     node.otherwise->next_label = node.then->next_label;
        // }

        //node.condition->accept(*this);
        check_error_definitons(node.condition);

        //code_buffer.emit("br i1 " + node.condition->reg + " ,label " + node.condition->true_label + " ,label " + node.condition->false_label);
        /*if(node.otherwise){
            check_error_definitons(node.condition);//,  node.line);
        }else{
            check_error_definitons(node.condition,  node.then->line);
        }
        */
        if(node.condition->type != ast::BuiltInType::BOOL){
            errorMismatch(node.condition->line);
        }

        //code_buffer.emitLabel(node.condition->true_label);

        this->begin_Scope();
        node.then->accept(*this);
        this->end_scope();

        this->code_buffer.emit("br label " + next_label);
        if (node.otherwise) {

            this->code_buffer.emitLabel(if_next_false_label);
            // code_buffer.emitLabel(node.condition->false_label);

            this->begin_Scope();
            node.otherwise->accept(*this);
            this->end_scope();
            this->code_buffer.emit("br label " + next_label);

        }

        code_buffer.emitLabel(next_label );
        //code_buffer.emitLabel(node.then->next_label );
        //code_buffer.emit("br label" + node.next_label);
    }

    void MyVisitor::visit(ast::While &node) {
        loop_head_label = code_buffer.freshLabel();
        exit_label = code_buffer.freshLabel();
        node.condition->true_label = code_buffer.freshLabel();
        node.condition->false_label = exit_label;

        code_buffer.emitLabel(loop_head_label );

        node.condition->accept(*this); 
        check_error_definitons(node.condition);//,  node.line);
        if(node.condition->type != ast::BuiltInType::BOOL){
            errorMismatch(node.condition->line);
        }

        code_buffer.emitLabel(node.condition->true_label);
        node.body->next_label = loop_head_label;

        this->in_while++;
        this->begin_Scope();
        node.body->accept(*this);
        this->end_scope();
        this->in_while--;

        code_buffer.emitLabel(node.condition->false_label);
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

        if(node.init_exp){
            
            this->code_buffer.emit( "store " + get_type_string(node.type->type) + node.init_exp->reg + " , "+ get_ptr_type_string(node.type->type) + "%v" +node.id->value );
        }
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

        this->code_buffer.emit( "store " + get_type_string(node.exp->type) + node.exp->reg + " , "+ get_ptr_type_string(id_entry->ret_type) + "%" + node.id->value );
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
                errorDef(node.id->line, node.id->value);
            } else {
                this->insert_func(node.id->value, node.return_type->type, parameters);
            }

        }else{
            this->begin_Scope();
            this->current_function_name = node.id->value;
            const SymTableEntry * id_entry = this->id_exists(node.id->value);
            // TO DO 
            // maintain the offset and symtable
            
            std::vector<ast::BuiltInType> params_array;
            
            const SymTableEntry * id_entry_of_param;
            for(int i = 0 ; i < id_entry->paramTypes.size(); i++){
                VariableAttributes param = id_entry->paramTypes[i];
                id_entry_of_param = this->id_exists(param.name);
                if(id_entry_of_param){
                    if(is_function(id_entry_of_param)){
                        errorDefAsFunc(node.formals->formals[i]->line, param.name);
                    }else{
                        errorDef(node.formals->formals[i]->line, param.name);
                    }
                }
                if(param.type == ast::BuiltInType::VOID){
                    break;
                }
                this->insert_variable(param.name, param.type, &param.offset);
                //this->scope_printer.emitVar(param.name, param.type, param.offset);
                params_array.push_back(param.type);
            }

            this->code_buffer.emit("define " + get_type_string(id_entry->ret_type) + "@" + id_entry->name + create_string_of_params(params_array) + " {");
            this->code_buffer.emitLabel(this->code_buffer.freshLabel());

            node.body->accept(*this);

            if(!return_occured(this->current_function_name) ){
                std::string return_cmd = "ret " + get_type_string(id_entry->ret_type);
                if(is_numerical(id_entry->ret_type)){
                    return_cmd += " 0";
                }else if(id_entry->ret_type == ast::BuiltInType::BOOL){
                    return_cmd += " false";
                }
                this->code_buffer.emit(return_cmd);
            }

            this->code_buffer.emit("}");
            
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
        //this->scope_printer.emitVar(name, type, offset);
        if(offset_ptr == nullptr) { // var decl
            this->offset_table.back() += SIZE_OF_TYPE;


            this->code_buffer.emit("%v" + name + " = alloca " + get_type_string(type));
        }




    }

    void MyVisitor :: insert_func(std::string name, ast::BuiltInType return_type , std::vector<VariableAttributes> params, bool without_printing)
    {
        SymTableEntry element = {name, return_type, params, 0};
        this->sym_table.front().push_back(element);
        std::vector<ast::BuiltInType> params_array;
        
        if(without_printing){
            return;
        }
        for(auto const &param : params){
            if(param.type == ast::BuiltInType::VOID){
                break;
            }
            params_array.push_back(param.type);
        }
        //this->code_buffer.emit("declare " + get_type_string(return_type) + " @" + name + create_string_of_params(params_array));
        //this->scope_printer.emitFunc(name, return_type, params_array);
    }

    void MyVisitor :: begin_Scope()
    {
        std::vector<SymTableEntry> initial_vector;
        this->sym_table.push_back(initial_vector);
        this->offset_table.push_back(this->offset_table.back());
       // this->scope_printer.beginScope();
    }

    void MyVisitor :: end_scope()
    {
        this->sym_table.pop_back();
        this->offset_table.pop_back();
       // this->scope_printer.endScope();

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

