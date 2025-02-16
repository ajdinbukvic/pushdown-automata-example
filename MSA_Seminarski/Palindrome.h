#pragma once

#include <stack>
#include <string>

class Palindrome {
private:
    std::string input;

    void print_stack(const std::stack<char>& stack);
public:
    explicit Palindrome(std::string input)
        : input(std::move(input)) {
    }

    bool parse();
};

