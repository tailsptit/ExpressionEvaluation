//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_UTILS_H
#define EXPRESSIONEVALUATION_UTILS_H

class Utils {
public:
    template<typename T>
    static T max(T t1, T t2) { return t1 > t2 ? t1 : t2; }

    template<typename T>
    static T min(T t1, T t2) { return t1 < t2 ? t1 : t2; }

};

#endif /* EXPRESSIONEVALUATION_UTILS_H */