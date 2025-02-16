#include "Palindrome.h"

#include <iostream>
#include <stack>
#include <string>
#include <algorithm>
#include <cctype>

void Palindrome::print_stack(const std::stack<char>& stack)
{
    std::stack<char> temp = stack;
    std::cout << "Stek: ";
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
}

bool Palindrome::parse()
{
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    std::transform(input.begin(), input.end(), input.begin(), ::tolower);

    std::cout << "Tekst bez razmaka i u malim slovima: " << input << std::endl;

    std::stack<char> stack;
    size_t length = input.size();

    std::cout << "Dodavanje simbola na stek - prva polovina stringa.\n";
    for (size_t i = 0; i < length / 2; ++i) {
        std::cout << "Dodavanje simbola '" << input[i] << "' na stek.\n";
        stack.push(input[i]);
        print_stack(stack); 
    }

    size_t start = (length % 2 == 0) ? length / 2 : (length / 2) + 1;
    std::cout << "Poredjenje s drugom polovinom stringa.\n";
    for (size_t i = start; i < length; ++i) {
        char top = stack.top();
        std::cout << "Poredjenje: simbol sa steka '" << top << "' sa simbolom u stringu '" << input[i] << "'\n";

        if (stack.empty() || top != input[i]) {
            std::cout << "[GRESKA]: Simboli se ne podudaraju.\n";
            return false;
        }
        stack.pop();
        std::cout << "Simboli su jednaki, uklanjanje simbola '" << top << "' sa steka.\n";
        print_stack(stack); 
    }

    if (stack.empty()) {
        return true;
    }
    else {
        std::cout << "[GRESKA]: Stek nije prazan, uneseni tekst nije palindrom.\n";
        return false;
    }
}
