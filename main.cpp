#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <iomanip>
#include <queue>

// --- Shared State and Thread Control ---
std::atomic<bool> is_running{true};

// Marquee control
std::string marquee_text = "Welcome to the Marquee OS Emulator!";
std::atomic<bool> marquee_running{false};
std::atomic<int> marquee_speed{200}; // ms per shift

// Shared display buffers
std::string marquee_display_buffer = "";
std::mutex marquee_mutex;

std::string prompt_display_buffer = "";
std::mutex prompt_mutex;

std::queue<std::string> command_queue;
std::mutex command_queue_mutex;

// --- Utility Function ---
void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void print_prompt() {
    gotoxy(1, 3);
    std::cout << "\033[K"; // clear line
    std::cout << "Type 'help' for commands." << std::flush;

    gotoxy(1, 4);
    std::cout << "\033[K"; // clear line
    std::cout << "Command> " << std::flush;
}

// --- Thread Functions ---
void keyboard_handler_thread_func() {
    std::string command_line;
    while (is_running) {
        std::getline(std::cin, command_line);
        if (!command_line.empty()) {
            std::unique_lock<std::mutex> lock(command_queue_mutex);
            command_queue.push(command_line);
        }
    }
}

void marquee_logic_thread_func(int display_width) {
    int pos = display_width;
    while (is_running) {
        if (marquee_running) {
            std::string to_display(display_width, ' ');
            {
                std::unique_lock<std::mutex> lock(marquee_mutex);
                int text_len = (int)marquee_text.size();
                for (int i = 0; i < text_len; i++) {
                    int idx = pos + i;
                    if (idx >= 0 && idx < display_width) {
                        to_display[idx] = marquee_text[i];
                    }
                }
                marquee_display_buffer = to_display;
            }

            pos--;
            if (pos < -((int)marquee_text.size())) {
                pos = display_width;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(marquee_speed));
    }
}

void display_thread_func() {
    const int refresh_rate_ms = 50;
    while (is_running) {
        std::cout << "\033[s";
        // update only the marquee line
        gotoxy(1, 1);        
        std::cout << "\033[K"; // clear line
        {
            std::unique_lock<std::mutex> lock(marquee_mutex);
            std::cout << marquee_display_buffer << std::flush;
        }
        std::cout << "\033[u" << std::flush;

        std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate_ms));
    }
}


// --- Main Function (Command Interpreter Thread) ---
int main() {
    std::thread marquee_logic_thread(marquee_logic_thread_func, 40);
    std::thread display_thread(display_thread_func);
    std::thread keyboard_handler_thread(keyboard_handler_thread_func);

    std::cout << "\033c"; // full terminal reset
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    gotoxy(1, 2);
    std::cout << "\033[K";
    print_prompt();

    // Main loop for commands
    while (is_running) {
        std::string command_line;
        {
            std::unique_lock<std::mutex> lock(command_queue_mutex);
            if (!command_queue.empty()) {
                command_line = command_queue.front();
                command_queue.pop();
            }
        }

        if (!command_line.empty()) {
            std::istringstream iss(command_line);
            std::string cmd;
            iss >> cmd;

            gotoxy(1, 5); // logs start at line 5
            std::cout << "\033[J";

            if (cmd == "help") {
                std::cout << "Available commands:\n"
                          << " help          - Show this help menu\n"
                          << " start_marquee - Start marquee animation\n"
                          << " stop_marquee  - Stop marquee animation\n"
                          << " set_text      - Set marquee text\n"
                          << " set_speed     - Set marquee speed in ms\n"
                          << " exit          - Exit program\n";
            } else if (cmd == "start_marquee") {
                marquee_running = true;
                std::cout << "Marquee started.\n";
            } else if (cmd == "stop_marquee") {
                marquee_running = false;
                std::cout << "Marquee stopped.\n";
            } else if (cmd == "set_text") {
                std::string new_text;
                std::getline(iss, new_text);
                if (!new_text.empty() && new_text[0] == ' ') new_text.erase(0, 1);
                if (!new_text.empty()) {
                    std::unique_lock<std::mutex> lock(marquee_mutex);
                    marquee_text = new_text;
                }
                std::cout << "Marquee text updated.\n";
            } else if (cmd == "set_speed") {
                int new_speed;
                iss >> new_speed;
                if (new_speed > 0) {
                    marquee_speed = new_speed;
                    std::cout << "Speed updated.\n";
                } else {
                    std::cout << "Invalid speed.\n";
                }
            } else if (cmd == "exit") {
                is_running = false;
                std::cout << "Exiting program...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            } else {
                std::cout << "Unknown command: " << cmd << "\n";
            }

            // always restore prompt after command
            print_prompt();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    if (marquee_logic_thread.joinable()) marquee_logic_thread.join();
    if (display_thread.joinable()) display_thread.join();
    if (keyboard_handler_thread.joinable()) keyboard_handler_thread.join();

    std::cout << "\033[0m\033[2J\033[H"; 
    std::cout.flush();

    return 0;
}
