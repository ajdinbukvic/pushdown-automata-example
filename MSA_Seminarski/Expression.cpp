#include "Expression.h"

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

std::string Expression::remove_whitespace(const std::string& str)
{
    std::string result;
    for (char c : str) {
        if (!std::isspace(c)) {
            result += c;
        }
    }
    return result;
}

bool Expression::is_non_terminal(char c)
{
    return c == 'E' || c == 'T' || c == 'F' || c == 'Q' || c == 'R';
}

bool Expression::is_terminal(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

void Expression::apply_rule(char non_terminal, char current)
{
    if (non_terminal == 'E') {
        if (isdigit(current) || current == '(' || current == '-') {
            stack.push('Q');
            stack.push('T');
            std::cout << "Primjena pravila: E -> Q T\n";
        }
        else {
            std::cout << "[GRESKA]: Ocekivan broj, '-', ili '('.\n";
            valid = false;
        }
    }
    else if (non_terminal == 'Q') {
        if (current == '+') {
            if (last_was_operator && current == '+') {
                std::cout << "[GRESKA]: Dva uzastopna operatora '+'.\n";
                valid = false;
                return;
            }
            stack.push('Q');
            stack.push('T');
            stack.push('+');
            std::cout << "Primjena pravila: Q -> Q T +\n";
            last_was_operator = true;
        }
        else if (current == '-') {
            if (last_was_operator && current == '-') {
                std::cout << "[GRESKA]: Dva uzastopna operatora '-'.\n";
                valid = false;
                return;
            }
            stack.push('Q');
            stack.push('T');
            stack.push('-');
            std::cout << "Primjena pravila: Q -> Q T -\n";
            last_was_operator = true;
        }
        else if (current == ')' || current == '\0') {
            std::cout << "Primjena epsilon pravila za Q.\n";
            last_was_operator = false;
        }
        else {
            std::cout << "[GRESKA]: Neocekivani simbol u Q.\n";
            valid = false;
        }
    }
    else if (non_terminal == 'T') {
        if (isdigit(current) || current == '(' || current == '-') {
            stack.push('R');
            stack.push('F');
            std::cout << "Primjena pravila: T -> R F\n";
        }
        else {
            std::cout << "[GRESKA]: Ocekivan broj, '-', ili '('.\n";
            valid = false;
        }
    }
    else if (non_terminal == 'R') {
        if (current == '*') {
            if (last_was_operator && current == '*') {
                std::cout << "[GRESKA]: Dva uzastopna operatora '*'.\n";
                valid = false;
                return;
            }
            stack.push('R');
            stack.push('F');
            stack.push('*');
            std::cout << "Primjena pravila: R -> R F *\n";
            last_was_operator = true;
        }
        else if (current == '/') {
            if (last_was_operator && current == '/') {
                std::cout << "[GRESKA]: Dva uzastopna operatora '/'.\n";
                valid = false;
                return;
            }
            stack.push('R');
            stack.push('F');
            stack.push('/');
            std::cout << "Primjena pravila: R -> R F /\n";
            last_was_operator = true;
        }
        else if (current == '+' || current == '-' || current == ')' || current == '\0') {
            std::cout << "Primjena epsilon pravila za R.\n";
            last_was_operator = false;
        }
        else {
            std::cout << "[GRESKA]: Neocekivani simbol u R.\n";
            valid = false;
        }
    }
    else if (non_terminal == 'F') {
        if (isdigit(current)) {
            stack.push('n');
            std::cout << "Primjena pravila: F -> n (broj)\n";
            last_was_operator = false;
        }
        else if (current == '-') {
            stack.push('F');
            consume();
            std::cout << "Primjena pravila: F -> - F (negativan broj)\n";
            last_was_operator = false;
        }
        else if (current == '(') {
            if (last_was_operator) {
                std::cout << "[GRESKA]: Nemoguce staviti operator prije zagrade.\n";
                valid = false;
                return;
            }
            stack.push(')');
            stack.push('E');
            stack.push('(');
            std::cout << "Primjena pravila: F -> ( E ) (zagrade)\n";
            last_was_operator = false;
            inside_parentheses = true;
        }
        else {
            std::cout << "[GRESKA]: Ocekivan broj, '-', ili '('.\n";
            valid = false;
        }
    }
}

double Expression::parse_number()
{
    double value = 0;
    bool negative = false;

    if (current_char() == '-') {
        negative = true;
        consume();
    }

    while (isdigit(current_char())) {
        value = value * 10 + (current_char() - '0');
        consume();
    }

    if (current_char() == '.') {
        consume();
        double fraction = 0.1;
        while (isdigit(current_char())) {
            value += (current_char() - '0') * fraction;
            fraction *= 0.1;
            consume();
        }
    }

    std::cout << "Prepoznat broj: " << value << "\n";
    return negative ? -value : value;
}

void Expression::print_stack()
{
    std::stack<char> temp_stack = stack;
    std::cout << "Stek: ";
    while (!temp_stack.empty()) {
        std::cout << temp_stack.top() << " ";
        temp_stack.pop();
    }
    std::cout << "\n";
}

char Expression::current_char(size_t offset)
{
    return (pos + offset < input.size()) ? input[pos + offset] : '\0';
}

void Expression::consume()
{
    if (pos < input.size()) {
        pos++;
    }
}

bool Expression::is_valid() const
{
    return valid;
}

bool Expression::parse()
{
    stack.push('E');

    while (!stack.empty() && valid) {
        char top = stack.top();
        char current = current_char();

        print_stack();

        if (is_non_terminal(top)) {
            stack.pop();
            apply_rule(top, current);
        }
        else if (is_terminal(top)) {
            if (top == current) {
                stack.pop();
                consume();
                std::cout << "Simbol '" << current << "' je prepoznat i skinut sa steka.\n";
                last_was_operator = false;
            }
            else {
                std::cout << "[GRESKA]: Neocekivani simbol '" << current << "'. Ocekivan '" << top << "'.\n";
                valid = false;
                return false;
            }
        }
        else if (top == 'n') {
            stack.pop();
            parse_number();
        }
        else {
            std::cout << "[GRESKA]: Neocekivani simbol na steku.\n";
            valid = false;
            return false;
        }
    }

    if (pos != input.size() && valid) {
        std::cout << "[GRESKA]: Ulaz nije potpuno validiran.\n";
        valid = false;
        return false;
    }

    return valid;
}
