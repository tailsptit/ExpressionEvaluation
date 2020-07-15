//
// Created by tails on 15/07/2020.
//

#ifndef EXPRESSIONEVALUATION_EVALUATION2_H
#define EXPRESSIONEVALUATION_EVALUATION2_H

#include <iostream>
#include <cmath>       /* pow */
#include <stack>
#include <iostream>
#include <string>
#include <Result.h>

#include "Stack.h"

class Evaluation2 {
private:
    Stack<char> ops;
    Stack<double> values;
    std::string operand = "";
    bool skip = false;
    bool unary = true;
    bool isOperand = false;
    Result result;
    std::string totalExp;
public:
    Evaluation2() { std::cout << "Initializing Calculator" << std::endl; }
    static bool isValid(char c);
    static bool isOperator(char c);
    static int getWeight(char a);
    static Result applyOp(char op, double a, double b);
    Result executeToken(char c);
    Result calculatePost(char c);
    static char *stringToCharPointer(std::string s, int &len);
    static char *doubleToCharPointer(double d, int &len);
    char *getValue(Result &res, int *len);
};

#endif //EXPRESSIONEVALUATION_EVALUATION2_H
