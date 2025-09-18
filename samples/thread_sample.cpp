#include <iostream>
#include <thread>
#include <mutex>

// A mutex to protect the shared `count` variable and
// ensure that the output is not jumbled.
std::mutex mtx;
int count = 1;

// This is the function that each thread will execute.
// It takes an integer `id` to identify the thread.
void print_numbers(int id, int iteration) {
    
    for (int i=0; (i < iteration); i++)
    {
        // Lock the mutex to ensure exclusive access to the shared resources.
        std::unique_lock<std::mutex> lock(mtx);
        
        std::cout << "Thread " << id << ": " << count << std::endl;
        count++;
        
        // Unlock the mutex when the scope ends.
        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

}

int main() {
    // Create two threads, passing the `print_numbers` function
    // and a unique ID for each thread.
    std::thread thread1(print_numbers, 1, 10);
    std::thread thread2(print_numbers, 2, 10);

    // Wait for both threads to finish their execution.
    thread1.join();
    thread2.join();

    std::cout << "All threads have finished." << std::endl;
    return 0;
}