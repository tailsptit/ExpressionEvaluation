//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_TCPSERVER_H
#define EXPRESSIONEVALUATION_TCPSERVER_H

#include <map>
#include <vector>
#include <mutex>
#include <iostream>

#include "Socket.h"
#include "WriteData.h"
#include "EventManager.h"

class TcpServer {
public:
    TcpServer(int port, int poolSize = 5);
    void start();

private:
    void handleTcpConnection();
    void handleReadRequest(int fd);
    void handleReadRequest2(int fd);
    void handleWriteRequest(int fd);
    void removeSession(int fd);

private:
    std::shared_ptr<Socket> listenSocket;
    EventManager eventManger;
    std::map<int, WriteData *> mapMessages;
    std::mutex mtx;
};

#endif  /* CEXPRESSIONEVALUATION_TCPSERVER_H */
