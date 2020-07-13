//
// Created by tails on 08/07/2020.
//
//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_EXPRESSION_H
#define EXPRESSIONEVALUATION_EXPRESSION_H

#include <typeinfo>
#include <iostream>
#include <sstream>
#include <random>

class Expression {
public:
    Expression(int _numOperands, int _maxOperand, int _minOperand, bool _allowBrackets, char _ops[]){
        numOperands = _numOperands;
        maxOperand = _maxOperand;
        minOperand = _minOperand;
        allowBrackets = _allowBrackets;
        for (int o = 0; o < 4; o++) {
            ops[o] = _ops[o];
        }
        gen = std::mt19937(rd());
        rnd = std::uniform_int_distribution<>(minOperand, maxOperand);
    }

    std::string generate(int numExpression);
    void generate(const std::string& file, int numExpression);
    int nextInt();
    bool nextBool();

private:
    int numOperands = 10;
    int maxOperand = 1000;
    int minOperand = 0;
    bool allowBrackets = true;
    char ops[4] = {'+', '-', '*', '/'};
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<int> rnd;
};


#endif //EXPRESSIONEVALUATION_EXPRESSIONGENERATOR_H
