//
// Created by tails on 12/07/2020.
//

#ifndef EXPRESSIONEVALUATION_THREADPOOL_H
#define EXPRESSIONEVALUATION_THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include "CallBack.h"

class ThreadPool {
public:
    enum State {IDLE, RUNNING, STOP};
    ThreadPool();
    ThreadPool(size_t _poolSize);
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ~ThreadPool();

    void setPoolSize(size_t size);
    size_t getSize() const;
    void addTask(CallBack *task);
    void awaitTermination();
    void start();
    void stop();

private:
    void startWorker();
    std::vector<std::thread> workers;
    std::queue<std::unique_ptr<CallBack>> pQueueTasks;
    std::mutex workerMutex;
    std::mutex queueMutex;
    std::condition_variable condition;
    State state;
    unsigned int poolSize;
};

#endif /* EXPRESSIONEVALUATION_THREADPOOL_H */
