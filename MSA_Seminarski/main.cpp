#include <iostream>
#include <string>
#include "Palindrome.h"
#include "Expression.h"

int main() {

    std::string palindrome_input;
    std::cout << "Unesite recenicu: ";
    std::getline(std::cin, palindrome_input);

    Palindrome palindromeParser(palindrome_input);
    if (palindromeParser.parse()) {
        std::cout << "Uneseni tekst je palindrom.\n";
    }
    else {
        std::cout << "Uneseni tekst nije palindrom.\n";
    }

    std::string expression_input;
    std::cout << "Unesite izraz: ";
    std::getline(std::cin, expression_input);

    Expression expressionParser(expression_input);
    if (expressionParser.parse()) {
        std::cout << "Uneseni izraz je validan.\n";
    }
    else {
        std::cout << "Uneseni izraz nije validan.\n";
    }

    return 0;
}
