//
// Created by tails on 12/07/2020.
//

#include <cstdio>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

#include "../../include/Result.h"
#include "../../include/TcpServer.h"
//#include "../../include/Evaluation.h"
//#include "../../include/Evaluation2.h"
//#include "../../include/Evaluation3.h"
#include "../../include/Evaluation4.h"
#include "../../include/BufferedDataReader.h"


TcpServer::TcpServer(int port, int poolSize) : eventManger(poolSize) {
    std::cout << "Create server socket a port " << port << std::endl;
    listenSocket.reset(Socket::createServerSocket(port, true));
}

void TcpServer::start() {
    if (listenSocket->getIsClosed()) {
        fprintf(stderr, "FAIL: Server not successfully initialized yet.\n");
        return;
    }
    // TODO: Submit it to event manager.
    eventManger.addTask(new CallBack(&TcpServer::handleTcpConnection, this));
    eventManger.start();
    eventManger.awaitTermination();
    std::cout << "Terminate server" << std::endl;
}

void TcpServer::handleTcpConnection() {
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);
    /* Accept actual connection from the client */
    while (true) {
        int accept_fd = accept(listenSocket->getFd(), (struct sockaddr *) &client_addr, &client_addr_len);
        static int num = 0;
        if (accept_fd < 0) {
            std::cerr << "ERORR: Accept connection failed" << std::endl;
            continue;
        }
        std::cout << "Accept new connection from " << inet_ntoa(client_addr.sin_addr) << ":"
                  << ntohs(client_addr.sin_port) << std::endl;
        std::cout << "Total connection: " << ++num << std::endl;
        std::cout << "Change to Reading mode. Socket Id = " << accept_fd << std::endl;
        eventManger.addTaskWaitingReadable(accept_fd, new CallBack(&TcpServer::handleReading, this, accept_fd));
    }
}
//
//void TcpServer::handleReading(int fd) {
//    std::cout << "Reading data from client" << std::endl;
//    Message *message = nullptr;
//    {
//        std::unique_lock<std::mutex> lock(mtx);
//        if (mapMessages.find(fd) == mapMessages.end()) {
//            mapMessages[fd] = new Message(64);
//        }
//        message = mapMessages[fd];
//    }
//
//    // Create a buffered data reader on the socket.
//    std::unique_ptr<FileDescriptor> upClientSocket(new Socket(fd, false));
//    BufferedDataReader br(std::move(upClientSocket));
//
//    // Begin reading message data.
//    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
//        char c;
//        int nread;
//        bool isError = false;
//        std::string error;
//        bool isOperand = false;
//        std::string operand;
//        Evaluation math;
//        Result result;
//        bool isEmptyExpression = true;
//        while ((nread = br.read(&c)) > 0) {
//            if (c == '\n') {
////                std::cout << "GOI HAM XU LY: " << c << std::endl;
//                if (!isError && isOperand) {
//                    std::cout << "GOI HAM XU LY: " << operand << std::endl;
//                    isError = math.executeToken(' ', true, operand).isException();
//                }
//                break;
//            } else {
//                isEmptyExpression = false;
//                if (!isError && c == ' ') {
//                    if (isOperand) {
//                        std::cout << "GOI HAM XU LY: " << operand << std::endl;
//                        isError = math.executeToken(' ', true, operand).isException();
//                        isOperand = false;
//                        operand = "";
//                    }
//                } else if (!isError && (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')')) {
//                    if (isOperand) {
//                        std::cout << "GOI HAM XU LY: " << operand << std::endl;
//                        isError = math.executeToken(' ', true, operand).isException();
//                        isOperand = false;
//                        operand = "";
//                    }
//                    std::cout << "GOI HAM XU LY: " << c << std::endl;
//                    math.executeToken(c, false, operand);
//                } else if (!isError && !Evaluation::isValid(c)) {
//                    isError = true;
//                    error = std::string("ERROR: Invalid character in expresion: ").append(1, c);
//                    operand = "";
//                } else {
//                    isOperand = true;
//                    operand.append(1, c);
//                }
//            }
//        }
//        if (!isEmptyExpression) {
//            int *len = new int;
//            char *writeData = math.getValue(isError, error, len);
//            message->resetBuffer(*len + 1);
//            message->writeToBuffer(writeData, *len + 1);
//            message->setState(Message::WRITING);
//            delete len;
//            delete[] writeData;
//        }
//        if ((nread == 0) || (errno != EAGAIN && errno != 0)) {
//            std::cout << "Close connection. Socket Id " << fd << std::endl;
//            removeSession(fd);
//            return;
//        }
//    }
//
//    // Submit new handler to event manager
//    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
//        std::cout << "Re-Adding to Reading mode. Socket Id = " << fd << std::endl;
//        eventManger.modifyTaskWaitingStatus(fd, EPOLLIN | EPOLLONESHOT,
//                                            new CallBack(&TcpServer::handleReading2, this, fd));
//    } else if (message->getState() == Message::WRITING) {
//        std::cout << "Change to Writing mode. Socket = " << fd << std::endl;
//        //eventManger.RemoveTaskWaitingReadable(fd);
//        eventManger.modifyTaskWaitingStatus(fd, EPOLLOUT | EPOLLONESHOT,
//                                            new CallBack(&TcpServer::handleWriting, this, fd));
//    }
//}

//void TcpServer::handleReading(int fd) {
//    std::cout << "Reading data from client" << std::endl;
//    Message *message = nullptr;
//    {
//        std::unique_lock<std::mutex> lock(mtx);
//        if (mapMessages.find(fd) == mapMessages.end()) {
//            mapMessages[fd] = new Message(64);
//        }
//        message = mapMessages[fd];
//    }
//
//    // Create a buffered data reader on the socket.
//    std::unique_ptr<FileDescriptor> upClientSocket(new Socket(fd, false));
//    BufferedDataReader br(std::move(upClientSocket));
//
//    // Begin reading message data.
//    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
//        char c;
//        int nread;
//        Evaluation2 math;
//        Result result;
//        bool isEmptyExpression = true;
//        math.executeToken('(');
//        while ((nread = br.read(&c)) > 0) {
//            if (c == '\n') {
//                if (!result.isException() && !isEmptyExpression) {
//                    result = math.executeToken(')');
//                }
//                break;
//            } else if (result.isException()) {
//                continue;
//            } else if (c == ' ') {
//                continue;
//            } else if (!Evaluation2::isValid(c)) {
//                isEmptyExpression = false;
//                result.setException(true, std::string("ERROR: Invalid character in expresion: ").append(1, c));
//            } else {
//                isEmptyExpression = false;
//                result = math.executeToken(c);
//            }
//        }
//        std::cout << "=====================================================================" << std::endl;
//        std::cout << "getException() = " << result.getException()<< std::endl;
//        std::cout << "isException() = " << result.isException()<< std::endl;
//        std::cout << "isEmptyExpression() = " << isEmptyExpression<< std::endl;
//
//        if (!isEmptyExpression) {
//            int *len = new int;
//            char *writeData = math.getValue(result, len);
//            message->resetBuffer(*len + 1);
//            message->writeToBuffer(writeData, *len + 1);
//            message->setState(Message::WRITING);
//            delete len;
//            delete[] writeData;
//        }
//        if ((nread == 0) || (errno != EAGAIN && errno != 0)) {
//            std::cout << "Close connection. Socket Id " << fd << std::endl;
//            removeSession(fd);
//            return;
//        }
//    }
//
//    // Submit new handler to event manager
//    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
//        std::cout << "Re-Adding to Reading mode. Socket Id = " << fd << std::endl;
//        eventManger.modifyTaskWaitingStatus(fd, EPOLLIN | EPOLLONESHOT,
//                                            new CallBack(&TcpServer::handleReading2, this, fd));
//    } else if (message->getState() == Message::WRITING) {
//        std::cout << "Change to Writing mode. Socket = " << fd << std::endl;
//        //eventManger.RemoveTaskWaitingReadable(fd);
//        eventManger.modifyTaskWaitingStatus(fd, EPOLLOUT | EPOLLONESHOT,
//                                            new CallBack(&TcpServer::handleWriting, this, fd));
//    }
//}

//5.52 => stoi
//cu = > 5.12

void TcpServer::handleReading(int fd) {
    std::cout << "Reading data from client" << std::endl;
    Message *message = nullptr;
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (mapMessages.find(fd) == mapMessages.end()) {
            mapMessages[fd] = new Message(64);
        }
        message = mapMessages[fd];
    }

    // Create a buffered data reader on the socket
    std::unique_ptr<FileDescriptor> upClientSocket(new Socket(fd, false));
    BufferedDataReader br(std::move(upClientSocket));

    // Reading data
    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
        char c;
        int nread;
        Evaluation4 math;
        Result result;
        bool isEmptyExpression = true;
        while ((nread = br.read(&c)) > 0) {
            if (c == '\n') {
                break;
            } else if (c == ' ') {
                continue;
            } else if (!result.isException() && !Evaluation4::isValid(c)) {
                isEmptyExpression = false;
                std::string error = std::string("ERROR: Invalid character: ");
                error.push_back(c);
                std::cout << error << std::endl;
                result.setException(true, error);
            } else if (!result.isException()) {
                isEmptyExpression = false;
                result = math.executeToken(c);
            }
        }

        if (!isEmptyExpression) {
            int *len = new int;
            char *writeData;
            if (!result.isException()) {
                result = math.getValue();
            }
            if (result.isException()) {
                writeData = Evaluation4::stringToCharPointer(result.getException(), *len);
            } else {
                writeData = Evaluation4::doubleToCharPointer(result.getValue(), *len);
            }
            message->resetBuffer(*len + 1);
            message->writeToBuffer(writeData, *len + 1);
            message->setState(Message::WRITING);
            delete len;
            delete[] writeData;
        }
//        if ((nread == 0) || (errno != EAGAIN && errno != 0)) {
//            std::cout << "Close connection. Socket Id " << fd << std::endl;
//            removeSession(fd);
//            return;
//        }
    }

    // Submit new handler to event manager
    if (message->getState() == Message::INIT || message->getState() == Message::READING) {
        std::cout << "Re-Adding to Reading mode. Socket Id = " << fd << std::endl;
        eventManger.modifyTaskWaitingStatus(fd, EPOLLIN | EPOLLONESHOT,
                                            new CallBack(&TcpServer::handleReading, this, fd));
    } else if (message->getState() == Message::WRITING) {
        std::cout << "Change to Writing mode. Socket = " << fd << std::endl;
        //eventManger.RemoveTaskWaitingReadable(fd);
        eventManger.modifyTaskWaitingStatus(fd, EPOLLOUT | EPOLLONESHOT,
                                            new CallBack(&TcpServer::handleWriting, this, fd));
    }
}

void TcpServer::handleWriting(int fd) {
    std::cout << "Sending back the result to client" << std::endl;
    Message *message = nullptr;
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (mapMessages.find(fd) == mapMessages.end()) {
            mapMessages[fd] = new Message(32);
        }
        message = mapMessages[fd];
    }

    int nwrite = write(fd, message->charBuffer(), message->getBufferSize());
    if (nwrite < 0) {
        removeSession(fd);
    }
    std::cout << "Change to Reading mode. Socket Id = " << fd << std::endl;
    message->setState(Message::READING);
    eventManger.modifyTaskWaitingStatus(fd, EPOLLIN | EPOLLONESHOT,
                                        new CallBack(&TcpServer::handleReading, this, fd));
}

void TcpServer::removeSession(int fd) {
    eventManger.removeAwaitingTask(fd);
    close(fd);
    // Delete socket fd from map
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (mapMessages.find(fd) == mapMessages.end()) {
            return;
        }
        delete mapMessages[fd];
        mapMessages.erase(mapMessages.find(fd));
    }
}