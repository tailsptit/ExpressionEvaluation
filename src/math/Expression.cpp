//
// Created by tails on 12/07/2020.
//

#include <string>
#include <fstream>

#include "../../include/Expression.h"

std::string Expression::generate(int numExpression) {
    std::stringstream buffer;
    int localNumOperands = numOperands - 1;
    for (int expId = 0; expId < numExpression; expId++) {
        // generates and appends the first number to file
        buffer << nextInt();
        int brackets = 0;
        for (int i = 0; i < localNumOperands; i++) {
            int number = nextInt();
            // Generates random operator and append
            char op = ops[nextInt() % 4];
            if (op == 'x') {
                op = '*';
            }
            if (op == '/' && number == 0) {
                i--;
                continue;
            }
            buffer << op;
            // Creates a bracket
            bool inBrackets = false;
            if (nextBool() && i != localNumOperands - 1 && allowBrackets) {
                buffer << "(";
                inBrackets = true;
                brackets++;
            }
            buffer << number;
            // Ends a bracket if exists
            if (brackets > 0 && !inBrackets && nextBool()) {
                buffer << ")";
                brackets--;
            }
        }
        // Ends all brackets
        for (int i = 0; i < brackets; i++) {
            buffer << ")";
        }
        buffer << '\n';
    }
    return buffer.str();
}

void Expression::generate(const std::string& file, int numExpression) {
    int localNumOperands = numOperands - 1;
    std::ofstream buffer(file);
    for (int expId = 0; expId < numExpression; expId++) {
        // generates and appends the first number to file
        buffer << nextInt();
        int brackets = 0;
        for (int i = 0; i < localNumOperands; i++) {
            // Generates random number
            int number = nextInt();

            // Generates random operator and append
            char op = ops[nextIntOperator() % 4];
            if (op == 'x') {
                op = '*';
            }
            if (op == '/' && number == 0) {
                i--;
                continue;
            }
            buffer << op;
            // Creates a bracket
            bool inBrackets = false;
            if (nextBool() && i != localNumOperands - 1 && allowBrackets) {
                buffer << "(";
                inBrackets = true;
                brackets++;
            }
            // Appends the generated number
            buffer << number;
            // Ends a bracket if exists
            if (brackets > 0 && !inBrackets && nextBool()) {
                buffer << ")";
                brackets--;
            }
        }
        // Ends all brackets
        for (int i = 0; i < brackets; i++) {
            buffer << ")";
        }
        buffer << '\n';
    }
    buffer.close();
}

int Expression::nextInt() {
    return rndOperand(gen);
}

int Expression::nextIntOperator(){
    return rndOperator(gen);
}


bool Expression::nextBool() {
    return rndOperand(gen) % 2 == 1;
}