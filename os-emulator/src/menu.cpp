#include <iostream>
#include "menu.h"

// Constructor for the Menu class
Menu::Menu() {}

// Display the main menu and available commands
void Menu::display() {
    std::cout << "=== OS Emulator Menu ===" << std::endl;
    std::cout << "1. Start Marquee" << std::endl;
    std::cout << "2. Stop Marquee" << std::endl;
    std::cout << "3. Set Text" << std::endl;
    std::cout << "4. Set Speed" << std::endl;
    std::cout << "5. Help" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << "Please enter your choice: ";
}

// Handle user input for menu selection
int Menu::handle_input() {
    int choice;
    std::cin >> choice;
    return choice;
}