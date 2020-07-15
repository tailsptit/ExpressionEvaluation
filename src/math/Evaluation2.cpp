//
// Created by tails on 15/07/2020.
//

#include <cfenv>
#include "Evaluation2.h"

bool Evaluation2::isValid(char c) {
    return (('0' <= c) && (c <= '9')) ||
           (c == '+') || (c == '-') || (c == '*') || (c == '/') ||
           (c == '(') || (c == ')');
}


bool Evaluation2::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '^' || c == '!' ||
           c == '%' || c == '~' || c == '#';
}

int Evaluation2::getWeight(char a) {
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

Result Evaluation2::applyOp(char op, double a, double b) {
    std::feclearexcept(FE_OVERFLOW);
    std::feclearexcept(FE_UNDERFLOW);
    std::feclearexcept(FE_DIVBYZERO);
    double c;
    Result res;
    switch (op) {
        case '+':
            c = a + b;
            break;
        case '-':
            c = a - b;
            break;
        case '*':
            c = a * b;
            break;
        case '/':
            c = a / b;
            break;
        case '^':
            pow(a, b);
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        std::cout << "ERROR: Divide by zero" << std::endl;
        res.setException(true, "ERROR: Divide by zero");
    } else if (std::fetestexcept(FE_OVERFLOW)) {
        std::cout << std::string("ERROR: Overflow when executing operation ").append(1, op) << std::endl;
        res.setException(true, std::string("ERROR: Overflow when executing operation ").append(1, op));
    } else if (std::fetestexcept(FE_UNDERFLOW)) {
        std::cout << std::string("ERROR: Underflow when executing operation ").append(1, op) << std::endl;
        res.setException(true, std::string("ERROR: Underflow when executing operation ").append(1, op));
    } else {
        res.setValue(c);
    }
    return res;
}

//double Evaluation2::applyOp(char op, double op1, double op2) {
//    switch (op) {
//        case '+':
//            return op1 + op2;
//        case '-':
//            return op1 - op2;
//        case '*':
//            return op1 * op2;
//        case '/':
//            return op1 / op2;
//        case '^':
//            return pow(op1, op2);
//        default:
//            throw "InvalidOperationException";
//    }
//}

Result Evaluation2::executeToken(char c) {
//    std::cout << "executeToken " << c << std::endl;
    if (c == ' ') return result;
    if (!isOperator(c)) { // character '0' <= c <= '9'
        isOperand = true;
        result = calculatePost(c);
        unary = false;
    } else {
        if (isOperand) {
            result = calculatePost(',');
            if (result.isException()) return result;
        }
        isOperand = false;
        if (c != '(' && c != ')') {
            if (unary) {
                if (c == '-') c = '~';
                else if (c == '+') c = '#';
                else {
                    result.setException(true, "Invalid input expression");
                    return result;
                }
            }
            try {
                if (getWeight(c) <= getWeight(ops.peek())) {
                    result = calculatePost(ops.pop());
                    if (result.isException()) return result;

                    result = calculatePost(',');
                    if (result.isException()) return result;
                }
            } catch (std::exception &e) {
                result.setException(true, "Invalid input expression");
                return result;
            }
            ops.push(c);
            unary = true;
        }
        if (c == '(') { ops.push(c); }
        if (c == ')') {
            if (ops.empty()) {
                result.setException(true, "Invalid input expression");
                return result;
            }
            for (char t = ops.pop(); t != '('; t = ops.pop()) {
                result = calculatePost(t);
                if (result.isException()) return result;
                result = calculatePost(',');
                if (result.isException()) return result;
            }
        }
    }
    return result;
}

Result Evaluation2::calculatePost(char c) {
    if (!isOperator(c)) {
        if (c == ',') {
            if (skip) {
                skip = false;
                return result;
            }
            values.push(std::stoi(operand));
            operand = "";
        } else {
            operand.push_back(c);
        }
    } else {
        if (c == '~') {
            double op1 = values.pop();
            values.push(-op1);
        } else if (c == '#');
        else {
            double op2 = values.pop();
            double op1 = values.pop();
            Result res = applyOp(c, op1, op2);
            if (res.isException())
                return res;
            values.push(res.getValue());
        }
        skip = true;
    }
    return result;
}

char *Evaluation2::stringToCharPointer(std::string s, int &len) {
    len = s.size();
    char *res = new char[len + 1];
    std::copy(s.begin(), s.end(), res);
    res[len] = '\0';
    return res;
}

char *Evaluation2::doubleToCharPointer(double d, int &len) {
    std::string str = std::to_string(d);
    return stringToCharPointer(str, len);
}

char *Evaluation2::getValue(Result &res, int *len) {
    if (res.isException())
        return stringToCharPointer(res.getException(), *len);
    std::cout << "values.size() = " << values.size() << std::endl;
    if (values.size() != 1 || ops.size() != 0) {
        return stringToCharPointer("ERROR: Invalid input expression", *len);
    }
    return doubleToCharPointer(values.pop(), *len);
}