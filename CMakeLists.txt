cmake_minimum_required(VERSION 3.16)
project(ExpressionEvaluation)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)

include_directories(include)

add_executable(ExpressionEvaluation
        src/common/Socket.cpp
        src/common/ThreadPool.cpp
        src/common/EventManager.cpp
        src/common/FileDescriptor.cpp
        src/math/Evaluation.cpp
        src/math/Expression.cpp
        src/server/TcpServer.cpp
        src/factory/DataFactory.cpp
        mainServer.cpp include/Result.h src/math/Evaluation2.cpp include/Evaluation2.h include/FSM.h)