//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_EVALUATION_H
#define EXPRESSIONEVALUATION_EVALUATION_H

#include<string>
#include<stack>

#include "Stack.h"
#include "Result.h"

class Evaluation {
public:
    Evaluation(){
        ops.empty();
        values.empty();
    };
    static bool isValid(char c);
    static bool isOperator(char c);
    static int getWeight(char op) ;
    static Result applyOp(char op, double a, double b);
    static bool hasPriority(char op1, char op2);
    static char* stringToCharPointer(std::string s, int& len);
    static char* doubleToCharPointer(double d, int& len);
    double stringToInteger(std::string s);
    Result executeToken(char op, bool isOperand, std::string& operand);
    char* getValue(bool isError, std::string& error, int *len);

public:
    std::string ss;
    Stack<char> ops;
    Stack<double> values;
};


#endif //EXPRESSIONEVALUATION_EVALUATION_H
