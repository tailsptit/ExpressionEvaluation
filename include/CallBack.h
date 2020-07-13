//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_CALLBACK_H
#define EXPRESSIONEVALUATION_CALLBACK_H
#include <functional>

class CallBack {
public:
    template<class F, class... Args>
    CallBack(F &&f, Args &&... args) {
        task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
    }

    void run() {
        task();
    }

    virtual ~CallBack() {}

private:
    std::function<void()> task;
};

#endif /* EXPRESSIONEVALUATION_CALLBACK_H */
