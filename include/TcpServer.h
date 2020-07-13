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
#include "Message.h"
#include "EventManager.h"

class TcpServer {
public:
    TcpServer(int port, int poolSize = 5);
    void start();

private:
    void handleTcpConnection();
    void handleReading(int fd);
    void handleWriting(int fd);
    void removeSession(int fd);

private:
    std::shared_ptr<Socket> listenSocket;
    EventManager eventManger;
    std::map<int, Message *> mapMessages;
    std::mutex mtx;
};

#endif  /* CEXPRESSIONEVALUATION_TCPSERVER_H */
