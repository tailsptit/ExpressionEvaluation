//
// Created by tails on 14/07/2020.
//

#ifndef EXPRESSIONEVALUATION_MATH_H
#define EXPRESSIONEVALUATION_MATH_H

#include <iostream>
#include <math.h>       /* pow */
#include <stack>
#include <iostream>
#include <string>
#include "Result.h"

class Math {
public:
    Stack<char> ops;
    Stack<double> values;
    std::string operand1 = "";
    std::string operand2 = "";
    bool skip = false;
    bool unary = true;
    bool isOperand = false;
    Result result;

    Math() {
        std::cout << "Initializing Calculator" << std::endl;
    }

    static int getWeight(char a) {
        if (a == '+' || a == '-')
            return 1;
        else if (a == '*' || a == '/')
            return 2;
        else if (a == '^')
            return 3;
        else if (a == '~' || a == '#')
            return 4;
        return 0;
    }

    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!' ||
               c == '%' || c == '~' || c == '#';
    }

    static double applyOp(double op1, double op2, char c) {
        switch (c) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
            case '^':
                return pow(op1, op2);
            default:
                throw "InvalidOperationException";
        }
    }

    Result executeToken(char c) {
        if (!isOperator(c)) { // number '0' <= c <= '9'
            isOperand = true;
            calculatePost(c);
            unary = false;
        } else {
            if (isOperand) {
//                calculatePost(operand1);
                calculatePost(',');
            }
            isOperand = false;
            if (c != '(' && c != ')') {
                if (unary) {
                    if (c == '-') c = '~';
                    else if (c == '+') c = '#';
                    else
                        throw "invalid input string";
                }
                try {
                    if (getWeight(c) <= getWeight(ops.peek())) {
                        calculatePost(ops.pop());
                        calculatePost(',');
                    }
                } catch (std::exception &e) {
                    std::cout << "TO POST: " << e.what() << std::endl;
                }
                ops.push(c);
                unary = true;
            }
            if (c == '(') { ops.push(c); }
            if (c == ')') {
                for (char t = ops.pop(); t != '('; t = ops.pop()) {
                    calculatePost(t);
                    calculatePost(',');
                }
            }
        }
        result.setException(false, "");
        return result;
    }

    void calculatePost(char c) {
        if (!isOperator(c)) {
            if (c == ',') {
                if (skip) {
                    skip = false;
                    return;
                }
                values.push(std::stoi(operand2));
                operand2 = "";
            } else {
                operand2.push_back(c);
            }
        } else {
            if (c == '~') {
                double op1 = values.pop();
                values.push(-op1);
            } else if (c == '#');
            else {
                double op2 = values.pop();
                double op1 = values.pop();
                values.push(applyOp(op1, op2, c));
            }
            skip = true;
        }
    }

    char *stringToCharPointer(std::string s, int &len) {
        len = s.size();
        char *res = new char[len + 1];
        std::copy(s.begin(), s.end(), res);
        res[len] = '\0';
        return res;
    };

    char *doubleToCharPointer(double d, int &len) {
        std::string str = std::to_string(d);
        return stringToCharPointer(str, len);
    };

    char *getValue(bool isError, std::string &error, int *len) {
        if (isError)
            return stringToCharPointer(error, *len);

        if (values.getSize() != 1) {
            return stringToCharPointer("ERROR: Wrong expression", *len);
        }
        return doubleToCharPointer(values.pop(), *len);
    }
};


#endif //EXPRESSIONEVALUATION_MATH_H
