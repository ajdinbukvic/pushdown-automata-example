#pragma once

#include <stack>
#include <string>

class Expression {
private:
    std::string input;
    size_t pos;
    std::stack<char> stack;
    bool last_was_operator;  
    bool inside_parentheses; 
    bool valid; 

    std::string remove_whitespace(const std::string& str);
    bool is_non_terminal(char c);
    bool is_terminal(char c);
    void apply_rule(char non_terminal, char current);
    double parse_number();
    void print_stack();
    char current_char(size_t offset = 0);
    void consume();
    bool is_valid() const;

public:
    explicit Expression(const std::string& input)
        : input(remove_whitespace(input)), pos(0), last_was_operator(false), inside_parentheses(false), valid(true) {
    }

    bool parse();
};
