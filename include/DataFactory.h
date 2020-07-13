//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_DATAFACTORY_H
#define EXPRESSIONEVALUATION_DATAFACTORY_H

#include <string>

class DataFactory {
public:
    DataFactory(){};
    static char getOperator(int val);
    static void generate(const std::string &file, int numOperands);
    static std::string generate(int numExpressions, int numOperands, int maxOperand, int minOperand, bool allowBracket, char ops[]);
    static void generate(const std::string &file, int numExpressions, int numOperands, int maxOperand, int minOperand, bool allowBracket, char ops[]);
};

#endif //EXPRESSIONEVALUATION_DATAFACTORY_H
