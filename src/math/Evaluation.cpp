//
// Created by tails on 12/07/2020.
//

#include <cctype>
#include <sstream>
#include <iostream>
#include <limits>
#include <values.h>
#include <iomanip>
#include <cfenv>
#include <stdexcept>

#include "../../include/Result.h"
#include "../../include/Evaluation.h"

bool Evaluation::isValid(char c) {
    return (('0' <= c) && (c <= '9')) ||
           (c == '+') || (c == '-') || (c == '*') || (c == '/') ||
           (c == '(') || (c == ')');
}

bool Evaluation::isOperator(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/');
}

int Evaluation::getWeight(char op) {
    if ((op == '+') || (op == '-'))
        return 1;
    else if ((op == '*') || (op == '/'))
        return 2;
    return 0;
}

Result Evaluation::applyOp(char op, double a, double b) {
    std::feclearexcept(FE_OVERFLOW);
    std::feclearexcept(FE_UNDERFLOW);
    std::feclearexcept(FE_DIVBYZERO);
    double c;
    Result result;
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
    }
    if (std::fetestexcept(FE_DIVBYZERO)) {
        std::string s;
        s.append(1,op);
        result.setException(true, "ERROR: Divide by zero");
    } else if (std::fetestexcept(FE_OVERFLOW)) {
        result.setException(true, std::string("ERROR: Overflow when executing operation ").append(1, op));
    } else if (std::fetestexcept(FE_UNDERFLOW)) {
        result.setException(true, std::string("ERROR: Underflow when executing operation ").append(1, op));
    } else {
        result.setValue(c);
    }
    return result;
}

bool Evaluation::hasPriority(char op1, char op2) {
    if (op2 == '(' || op2 == ')')
        return false;
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
        return false;
    else
        return true;
}

char *Evaluation::stringToCharPointer(std::string s, int &len) {
    len = s.size();
    char *result = new char[len + 1];
    std::copy(s.begin(), s.end(), result);
    result[len] = '\0';
    return result;
};

char *Evaluation::doubleToCharPointer(double d, int &len) {
    std::string str = std::to_string(d);
    return stringToCharPointer(str, len);
};

double stringToInteger(std::string s) {
    return std::stoi(s);
}

Result Evaluation::executeToken(char op, bool isOperand, std::string &operand) {
//    if (isOperand){
//        ss += operand;
//    } else {
//        ss += op;
//    }
//    std::cout << "expression = " << ss << std::endl;
    Result result;
//    static int dem = 0;
    if (op == '(') {
        ops.push(op);
    } else if (isOperand) {
        std::cout << "operand = " << ss << std::endl;
        int val;
        try {
            val = std::stoi(operand);
        } catch (std::exception &e) {
            result.setException(true, "ERROR: Number is overflow " + operand);
            return result;
        }
        values.push((double) val);
    } else if (op == ')') {
        while (!ops.empty() && ops.peek() != '(') {
            if (values.size() < 2) {
                result.setException(true, "ERROR: Wrong expression");
                return result;
            }
            double val2 = values.pop();
            double val1 = values.pop();
            result = applyOp(ops.pop(), val1, val2);
            if (result.isException())
                return result;
            values.push(result.getValue());
        }
        if (!ops.empty())
            ops.pop();
    } else if (isOperator(op)) {
//        dem++;
//        std::cout << "dem = " << dem << ", op = " << op << std::endl;
//        std::cout << "getWeight(ops.getSize()) = " << getWeight(ops.size()) << ", getWeight(op) = " << getWeight(op) << std::endl;
        while (!ops.empty() && getWeight(ops.peek()) >= getWeight(op)) {
            if (values.size() < 2) {
                result.setException(true, "ERROR: Wrong expression");
                return result;
            }
            double val2 = values.pop();
            double val1 = values.pop();
            result = applyOp(ops.pop(), val1, val2);
            if (result.isException())
                return result;
            values.push(result.getValue());
        }
        ops.push(op);
    }
    return result;
}

char *Evaluation::getValue(bool isError, std::string &error, int *len) {
    if (isError)
        return stringToCharPointer(error, *len);
//    std::cout << "getValue  => ops.getSize() = " << ops.size() << std::endl;
//    std::cout << "getValue  => values.getSize() = " << values.size() << std::endl;

    while (!ops.empty()) {
        if (values.size() < 2) {
            return stringToCharPointer("ERROR: Wrong expression", *len);
        } else {
            double val2 = values.pop();
            double val1 = values.pop();
            Result result = applyOp(ops.pop(), val1, val2);
            if (result.isException()) {
                return stringToCharPointer("ERROR: Wrong expression", *len);
            }
            values.push(result.getValue());
        }
    }
    if (values.size() != 1) {
        return stringToCharPointer("ERROR: Wrong expression", *len);
    }
    return doubleToCharPointer(values.pop(), *len);
}