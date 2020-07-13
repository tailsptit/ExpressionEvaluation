//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_SOCKET_H
#define EXPRESSIONEVALUATION_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "FileDescriptor.h"

class Socket : public FileDescriptor {
public:
    Socket() = default;
    Socket(const std::string _hostname) : FileDescriptor(-1, true), hostname(_hostname) {}
    Socket(const int fd, bool _autoClose = true) : FileDescriptor(fd, _autoClose) {}

    virtual ~Socket() {}

    static Socket *createClientSocket(const std::string hostname, const int port, bool block = true);

    static Socket *createServerSocket(const int port, bool block = true);

    virtual int readn(void *buffer, const int n) const;

    virtual int writen(const void *buf, const int n) const;

    virtual int send(void *buffer, const int n) const;

    virtual int receive(const void *buffer, const int n) const;

private:
    std::string hostname;
};

#endif  /* EXPRESSIONEVALUATION_SOCKET_H */
