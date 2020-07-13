//
// Created by tails on 12/07/2020.
//

#include <cctype>
#include <sstream>
#include <iostream>
#include <limits>
#include <values.h>
#include <tgmath.h>
#include <iomanip>

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
    long long lla = (long long) a, llb = (long long) b, llc;
    Result result;
    switch (op) {
        case '+':
            if (((b < 0) && (a < std::numeric_limits<double>::min() - b)) ||
                ((b > 0) && (a > std::numeric_limits<double>::max() - b))) {
                result.setException(true, "Overflow when ADDITION");
            } else {
                result.setValue(a + b);
            };
            break;
        case '-':
            if (((b > 0) && (a < std::numeric_limits<double>::min() + b)) ||
                ((b < 0) && (a > std::numeric_limits<double>::max() + b))) {
                result.setException(true, "Overflow when SUBTRACTION");
            } else {
                result.setValue(a - b);
            };
            break;
        case '*':
            llc = lla * llb;
            if (lla != 0 && llc / lla != llb) {
                result.setException(true, "Overflow when MULTIPLICATION");
            } else {
                result.setValue(a * b);
            }
            break;
        case '/':
            if (fabs(b) < 1e-17){
                result.setException(true, "Overflow when DIVISION. Division by zero");
            } else if (fabs(b) < 1) {
                double dabs = fabs(b);
                double limit = DBL_MAX * dabs;
                if ((a < -limit) || (a > limit)) {
                    result.setException(true, "Overflow when DIVISION. INF");
                } else {
                    result.setValue(a / b);
                }
            } else {
                result.setValue(a / b);
            }
            break;
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

/*
  Infix to postfix conversion. Only +, -, *, / operators are expected.
*/
std::string Evaluation::postfixConversion(const std::string& exp) {
    std::string postfix;
    Stack<char> stack;     //stack to convert string from infix to postfix
    // scan all characters one by one
    for (int i = 0; i < exp.length(); ++i) {
        char c = exp.at(i);
        // if character is blank space then continue
        if (isblank(c)) continue;

        if (isdigit(c) || isalpha(c)){
            postfix += c;
            if ((i+1 < exp.length()) && (!isdigit(exp.at(i+1)))){
                postfix += ' ';
            }
        }
        // if the character is an '(' then push it to stack
        else if (c == '('){
            stack.push(c);
        }
        // if the character is an ')', pop and output from the stack util an '(' is encountered
        else if (c == ')'){
            while (!stack.empty() && stack.peek() != '(')
                postfix += stack.pop();
            if (!stack.empty() && stack.peek() != '(')
                return "Invalid Expression";
            else
                stack.pop();
        } else {
            while (!stack.empty() && getWeight(c) <= getWeight(stack.peek())){
                if (stack.peek() == '(')
                    return "Invalid Expression";
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }
    // pop all the operators from the stack
    while (!stack.empty()) {
        if (stack.peek() == '(')
            return "Invalid Expression";
        postfix += stack.pop();
    }
    return postfix;
}
//
//// evaluatePostfix Postfix exp and return output
Result Evaluation::evaluatePostfix(const std::string &exp) {
    Stack<double> stack;
    Result result;
    // scan all characters one by one
    for (int i = 0; i < exp.length(); i++) {
        // if character is blank space then continue
        if (exp[i] == ' ') continue;
        else if (isOperator(exp[i])) {
            // pop two operands from stack.
            double operand2 = stack.peek(); stack.pop();
            double operand1 = stack.peek(); stack.pop();

            double val2 = stack.pop();
            double val1 = stack.pop();
            result = applyOp(exp[i], val1, val2);
            if (result.isException())
                return result;
            stack.push(result.getValue());
        } else if (isdigit(exp[i])) {
            // Extract the operand from the string, keep incrementing i as long as getting a digit
            double digit = 0.0;
            while (i < exp.length() && isdigit(exp[i])) {
                // For a number with more than one digits, as we are scanning from left to right
                if (digit > ((DBL_MAX) / 10.0)){
                    result.setException(true, "Number isEx");
                    return result;
                } else {
                    digit = (digit * 10.0) + (exp[i] - '0');
                }
                i++;
            }
            // when of while loop with i set to a non-numeric character or end of string
            // decrement i because it will be incremented in increment section of loop once again.
            i--;
            stack.push(digit);
        }
    }
    result.setValue(stack.pop());
    return result;
}

Result Evaluation::evaluate(const std::string &exp) {
    std::cout << std::setprecision(17);
    Stack<double> values;
    Stack<char> ops;
    int i;
    Result result;
    // scan all characters one by one
    for (i = 0; i < exp.length(); i++) {
        // if character is blank space then continue
        if (isblank(exp[i])) continue;
        if (exp[i] == '(') {
            ops.push(exp[i]);
        } else if (isdigit(exp[i])) {
            double digit = 0.0;
            while (i < exp.length() && isdigit(exp[i])) {
                if (digit > ((DBL_MAX) / 10.0)){
                    result.setException(true, "Number isEx");
                    return result;
                } else {
                    digit = (digit * 10.0) + (exp[i] - '0');
                }
                i++;
            }
            i--;
            values.push(digit);
//            92233720319999999
        }
            // if the character is an ')', pop and output from the stack util an '(' is encountered
        else if (exp[i] == ')') {
            while (!ops.empty() && ops.peek() != '(') {
                double val2 = values.pop();
                double val1 = values.pop();
                result = applyOp(ops.pop(), val1, val2);
                if (result.isException())
                    return result;
                values.push(result.getValue());
            }
            // pop opening brace.
            if (!ops.empty())
                ops.pop();
        }
            // character is an operator
        else if (isOperator(exp[i])) {
            while (!ops.empty() && getWeight(ops.peek()) >= getWeight(exp[i])) {
                double val2 = values.pop();
                double val1 = values.pop();
                result = applyOp(ops.pop(), val1, val2);
                if (result.isException())
                    return result;
                values.push(result.getValue());
            }
            // put current value to ops
            ops.push(exp[i]);
        }
    }
    // pop all the operators from the stack
    while (!ops.empty()) {
        double val2 = values.pop();
        double val1 = values.pop();
        result = applyOp(ops.pop(), val1, val2);
        if (result.isException())
            return result;
        values.push(result.getValue());
    }
    result.setValue(values.pop());
    return result;
}
