#include <iostream>

#include "../../include/ThreadPool.h"

ThreadPool::ThreadPool() : state(IDLE), poolSize(4) {}
ThreadPool::ThreadPool(size_t _poolSize) : state(IDLE), poolSize(_poolSize) {}

// Destructor joins all threads
ThreadPool::~ThreadPool() {
    for (std::thread &worker: workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

void ThreadPool::setPoolSize(size_t size) {
    poolSize = size;
}

size_t ThreadPool::getSize() const {
    return poolSize;
}

void ThreadPool::start() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        state = RUNNING;
        unsigned int numWorkingThreads = poolSize < pQueueTasks.size() ? poolSize : pQueueTasks.size();
        for (unsigned int i = workers.size(); i < numWorkingThreads; i++) {
            workers.emplace_back(std::thread(&ThreadPool::startWorker, this));
        }
    }
    condition.notify_all();
}

// Thread worker
void ThreadPool::startWorker() {
    CallBack *task;
    while (true) {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return state == STOP || !pQueueTasks.empty(); });
            if (state == STOP && pQueueTasks.empty()) {
                return;
            }
            task = (pQueueTasks.front()).release();
            pQueueTasks.pop();
        }
        task->run();
    }
}

// Add new work to pool
void ThreadPool::addTask(CallBack *task) {
    {
        std::unique_lock<std::mutex> lock(workerMutex);
        if (state == RUNNING && workers.size() < poolSize) {
            workers.emplace_back(std::thread(&ThreadPool::startWorker, this));
        }
    }
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (state == STOP) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        pQueueTasks.emplace(std::unique_ptr<CallBack>(task));
    }
    condition.notify_one();
}

// Blocks and wait for all previously submitted pQueueTasks to be completed
void ThreadPool::awaitTermination() {
    condition.notify_all();
    for (std::thread &worker: workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

// Shut down the ThreadPool. This method does not wait for previously submitted pQueueTasks to be completed.
void ThreadPool::stop() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        state = STOP;
    }
    condition.notify_all();
}