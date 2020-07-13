//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_WRITEDATA_H
#define EXPRESSIONEVALUATION_WRITEDATA_H

#include <string.h>
#include <FSM.h>

class WriteData {
public:
    WriteData() = default;
    WriteData(int _bufferSize) : bufferSize(_bufferSize) {
        buffer = new char[bufferSize];
    }
    ~WriteData() {
        if (buffer) {
            delete[] buffer;
        }
    };

    void setState(enum State _state) {
        state = _state;
    }

    enum State getState() const {
        return state;
    };
    void resetBuffer(int size) {
        if (buffer) {
            delete[] buffer;
        }
        buffer = new char[size];
        bufferSize = size;
    };

    int getBufferSize() const { return bufferSize; }


    void writeToBuffer(const char *data, int size) {
        if (size < 0 || !buffer) {
            return;
        }
        memcpy(buffer, data, size);
    }

    char *charBuffer() const {
        return buffer;
    }

private:
    char *buffer = nullptr;
    int bufferSize = 0;
    State state = INIT;
};

#endif //EXPRESSIONEVALUATION_WRITEDATA_H
