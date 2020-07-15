//
// Created by tails on 15/07/2020.
//

#ifndef EXPRESSIONEVALUATION_STACK_H
#define EXPRESSIONEVALUATION_STACK_H
#include <stack>

template<typename T>
class Stack {
public:
    void push(T val){ _stack.push(val); }
    bool empty(){ return _stack.empty(); }
    T peek(){ return _stack.top(); }
    T pop(){
        T val = _stack.top();
        _stack.pop();
        return val;
    }
    int size(){ return _stack.size(); };
private:
    std::stack<T> _stack;
};

#endif //EXPRESSIONEVALUATION_STACK_H
