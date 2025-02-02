#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <map>

#include <string>
#include <sstream>
#include "visitor.hpp"
#include "nodes.hpp"

const int MESSAGE_ERROR_SIZE = std::string("Error division by zero").length()+1;
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


    class CodeBuffer {
    private:
        std::stringstream globalsBuffer;
        std::stringstream buffer;
        int labelCount;
        int varCount;
        int stringCount;

        friend std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer);

    public:
        CodeBuffer();

        // Returns a string that represents a label not used before
        // Usage examples:
        //      emitLabel(freshLabel());
        //      buffer << "br label " << freshLabel() << std::endl;
        std::string freshLabel();

        // Returns a string that represents a variable not used before
        // Usage examples:
        //      std::string var = freshVar();
        //      buffer << var << " = icmp eq i32 0, 0" << std::endl;
        std::string freshVar();

        // Emits a label into the buffer
        void emitLabel(const std::string &label);

        // Emits a constant string into the globals section of the code.
        // Returns the name of the constant. For the string of the length n (not including null character), the type is [n+1 x i8]
        // Usage examples:
        //      std::string str = emitString("Hello, World!");
        //      buffer << "call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* " << str << ", i32 0, i32 0))" << std::endl;
        std::string emitString(const std::string &str);

        // Emits a string into the buffer
        void emit(const std::string &str);

        // Template overload for general types
        template<typename T>
        CodeBuffer &operator<<(const T &value) {
            buffer << value;
            return *this;
        }

        // Overload for manipulators (like std::endl)
        CodeBuffer &operator<<(std::ostream &(*manip)(std::ostream &));

        std::string emit_zext(std::string reg_to_zext);

        void insert_str_divide_by_0(std::string reg_name, std::string error_msg); // need to check if there is importance to type
    };

    std::ostream &operator<<(std::ostream &os, const CodeBuffer &buffer);
    
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
        std::string current_function_name;
        unsigned int in_while;
        std::vector<std::string> exit_labels, loop_head_labels;
        //std::string exit_label, loop_head_label;
        bool first_run_on_function_declerations;
        std::string error_msg_divide_0_ptr;
        long long int scope_id;

        /* Helper function to print a string with the current indentation */
        //void print_indented(const std::string &str);

        /* Functions to manage the indentation level */
        // void enter_child();

        // void enter_last_child();

        // void leave_child();
        void insert_variable(std::string name, ast::BuiltInType type, const int* offset_ptr = nullptr);
        void insert_func(std::string name, ast::BuiltInType return_type , std::vector<VariableAttributes> params, bool without_printing = false);
        void begin_Scope();
        void end_scope();
        std::string get_reg_name_variable(std::string name);
        const SymTableEntry* id_exists(std::string name);
        SymTableEntry *  id_exists_and_change(std::string name);

       // bool resolved_forward_references();

    public:
        CodeBuffer code_buffer;
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
