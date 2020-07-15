//
// Created by tails on 15/07/2020.
//

#ifndef EXPRESSIONEVALUATION_EVALUATION4_H
#define EXPRESSIONEVALUATION_EVALUATION4_H

#include <stack>
#include <fenv.h>
#include <charconv>
#include "Stack.h"

class Evaluation4 {
    Stack<char> ops;
    Stack<double> values;
    Result result;
    bool isOperand = false;
    std::string operand = "";
    bool mayBeUnary = true;

public:
    static bool isEmpty(char c) {
        return c == ' ';
    }

    static bool isOp(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    static bool isUnary(char c) {
        return c == '+' || c == '-';
    }

    static int weight(char op) {
        if (op < 0) // unary operator
            return 3;
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return -1;
    }

    static bool isValid(char c) {
        return (('0' <= c) && (c <= '9')) ||
               (c == '+') || (c == '-') || (c == '*') || (c == '/') ||
               (c == '(') || (c == ')');
    }

    static char *stringToCharPointer(std::string s, int &len) {
        len = s.size();
        char *res = new char[len + 1];
        std::copy(s.begin(), s.end(), res);
        res[len] = '\0';
        return res;
    }

    static char *doubleToCharPointer(double d, int &len) {
        std::string str = std::to_string(d);
        return stringToCharPointer(str, len);
    }

    Result applyOp(Stack<double> &st, char op) {
        Result res;
        double c;
        if (op < 0) {
            int left = st.pop();
            switch (-op) {
                case '+':
                    c = left;
                    break;
                case '-':
                    c = -left;
                    break;
            }
            st.push(c);
        } else {
            std::feclearexcept(FE_OVERFLOW);
            std::feclearexcept(FE_UNDERFLOW);
            std::feclearexcept(FE_DIVBYZERO);
            double right = st.pop();
            double left = st.pop();
            switch (op) {
                case '+':
                    c = left + right;
                    break;
                case '-':
                    c = left - right;
                    break;
                case '*':
                    c = left * right;
                    break;
                case '/':
                    c = left / right;
                    break;
            }
            if (std::fetestexcept(FE_DIVBYZERO)) {
                res.setException(true, "ERROR: Divide by zero");
            } else if (std::fetestexcept(FE_OVERFLOW)) {
                std::cout << std::string("ERROR: Overflow when executing operation ").append(1, op) << std::endl;
                res.setException(true, std::string("ERROR: Overflow when executing operation ").append(1, op));
            } else if (std::fetestexcept(FE_UNDERFLOW)) {
                std::cout << std::string("ERROR: Underflow when executing operation ").append(1, op) << std::endl;
                res.setException(true, std::string("ERROR: Underflow when executing operation ").append(1, op));
            } else {
                res.setValue(c);
                st.push(c);
            }
        }
        return res;
    }

    Result applyOp(char op) {
        Result res;
        double c;
        if (op < 0) {
            int left = values.pop();
            switch (-op) {
                case '+':
                    c = left;
                    break;
                case '-':
                    c = -left;
                    break;
            }
            values.push(c);
        } else {
            std::feclearexcept(FE_OVERFLOW);
            std::feclearexcept(FE_UNDERFLOW);
            std::feclearexcept(FE_DIVBYZERO);
            double right = values.pop();
            double left = values.pop();
            switch (op) {
                case '+':
                    c = left + right;
                    break;
                case '-':
                    c = left - right;
                    break;
                case '*':
                    c = left * right;
                    break;
                case '/':
                    c = left / right;
                    break;
            }
            if (std::fetestexcept(FE_DIVBYZERO)) {
                res.setException(true, "ERROR: Divide by zero");
            } else if (std::fetestexcept(FE_OVERFLOW) || std::fetestexcept(FE_UNDERFLOW)) {
                std::cout << std::string("ERROR: Overflow when executing operation ").append(1, op) << std::endl;
                res.setException(true, std::string("ERROR: Overflow when executing operation ").append(1, op));
            } else {
                res.setValue(c);
                values.push(c);
            }
        }
        return res;
    }

    int executeToken(string &s) {
        for (int i = 0; i < (int) s.size(); i++) {
            if (isEmpty(s[i]))
                continue;

            if (s[i] == '(') {
                ops.push('(');
                mayBeUnary = true;
            } else if (s[i] == ')') {
                while (ops.peek() != '(') {
                    applyOp(values, ops.peek());

                    ops.pop();
                }
                ops.pop();
                mayBeUnary = false;
            } else if (isOp(s[i])) {
                char cur_op = s[i];
                if (mayBeUnary && isUnary(cur_op))
                    cur_op = -cur_op;
                while (!ops.empty() && ((cur_op >= 0 && weight(ops.peek()) >= weight(cur_op)) ||
                                        (cur_op < 0 && weight(ops.peek()) > weight(cur_op)))) {
                    applyOp(values, ops.peek());
                    ops.pop();
                }
                ops.push(cur_op);
                mayBeUnary = true;
            } else {
                int number = 0;
                while (i < (int) s.size() && isalnum(s[i])) {
                    number = number * 10 + s[i++] - '0';
                }
                --i;
                values.push(number);
                mayBeUnary = false;
            }
        }
        while (!ops.empty()) {
            applyOp(values, ops.peek());
            ops.pop();
        }
        return values.peek();
    }

    int executeToken2(string &s) {
        for (char c : s) {
            executeToken(c);
        }
        if (isOperand) {
            values.push(std::stoi(operand));
        }
        while (!ops.empty()) {
            applyOp(values, ops.peek());
            ops.pop();
        }
        return values.peek();
    }

    Result executeToken(char c) {
        Result res;
        if (c == ' ') return result;
        if (c >= '0' && c <= '9') { // number '0' <= c <= '9'
            isOperand = true;
            operand.push_back(c);
        } else {
            if (isOperand) {
                int number;
//                std::from_chars(operand.data(),operand.data() + operand.size(), number);
                try {
                    number = std::stoi(operand);
                } catch (std::exception &e) {
                    res.setException(true, "ERROR: Overflow " + operand);
                    return res;
                }
                values.push(number);
                operand = "";
                mayBeUnary = false;
            }
            isOperand = false;
            if (c == '(') {
                ops.push('(');
                mayBeUnary = true;
            } else if (c == ')') {
                while (!ops.empty() && ops.peek() != '(') {
                    res = applyOp(ops.peek());
                    if (res.isException()) return res;
                    ops.pop();
                }
                ops.pop();
                mayBeUnary = false;
            } else if (isOp(c)) {
                char cOp = c;
                if (mayBeUnary && isUnary(cOp))
                    cOp = -cOp;
                while (!ops.empty() && ((cOp >= 0 && weight(ops.peek()) >= weight(cOp)) ||
                                        (cOp < 0 && weight(ops.peek()) > weight(cOp)))) {
                    res = applyOp(ops.peek());
                    if (res.isException()) return res;
                    ops.pop();
                }
                ops.push(cOp);
                mayBeUnary = true;
            }
        }
        return result;
    }

    Result getValue() {
        Result res;
        if (isOperand) {
            int number;
//            std::from_chars(operand.data(),operand.data() + operand.size(), number);
            try {
                number = std::stoi(operand);
            } catch (std::exception &e) {
                res.setException(true, "ERROR: Overflow " + operand);
                return res;
            }
            values.push(number);
        }
        while (!ops.empty()) {
            res = applyOp(ops.peek());
            if (res.isException()) return res;
            ops.pop();
        }
        if (ops.size() != 0 || values.size() != 1) {
            res.setException(true, "Invalid input expression");
            return res;
        }
        result.setValue(values.peek());
        return result;
    }
};

#endif //EXPRESSIONEVALUATION_EVALUATION4_H
