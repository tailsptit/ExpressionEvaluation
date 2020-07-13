//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_RESULT_H
#define EXPRESSIONEVALUATION_RESULT_H

#include <string>

class Result {
public:
    Result() { isEx = false; value = 0;};

    bool isException() { return isEx; }
    void setException(bool _isEx, std::string _exceptionContent) {
        isEx = _isEx;
        exceptionContent = _exceptionContent;
    }
    std::string getException() { return exceptionContent; }
    double getValue() { return value; }
    void setValue(double _value) { value = _value; }

private:
    bool isEx = false;
    std::string exceptionContent = "";
    double value = 0;
};

#endif //EXPRESSIONEVALUATION_RESULT_H
