#include <iostream>
#include <vector>

#include "barrier.hpp"

const size_t NUM_THREADS = 4; // number of threads to spawn

// Function to print messages and test barrier
void test(size_t thread_num, std::mutex& mut, Barrier& bar);

int main() {
    std::mutex mut; // mutex for cout
    Barrier bar(NUM_THREADS); // create barrier for threads

    // spin up some threads
    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        threads.push_back(std::thread(test, i, std::ref(mut), std::ref(bar)));
    }
    
    // join threads back in
    for (size_t i = 0; i < NUM_THREADS; ++i) {
        threads[i].join();
    }

    return 0;
}

void test(size_t thread_num, std::mutex& mut, Barrier& bar) {
    for (size_t i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(mut);
            std::cout << "Hello from thread " << thread_num << " iteration " << i << std::endl;
        }
        bar.wait();
        {
            std::lock_guard<std::mutex> lock(mut);
            std::cout << "Goodbye from thread " << thread_num << " iteration " << i << std::endl;
        }
        bar.wait();
    }
}