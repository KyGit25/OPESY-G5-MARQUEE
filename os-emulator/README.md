# OS Emulator

## Overview
This project is an OS emulator that features a command interpreter and a display output system. It includes a text marquee that can be controlled through various commands, allowing users to start and stop the marquee, set the text to be displayed, and adjust the speed of the marquee.

## Project Structure
```
os-emulator
├── src
│   ├── main.cpp                # Entry point of the OS emulator
│   ├── command_interpreter.cpp  # Implements command interpreter logic
│   ├── command_interpreter.h    # Header for command interpreter
│   ├── display.cpp              # Implements display handler
│   ├── display.h                # Header for display
│   ├── marquee.cpp              # Implements marquee logic
│   ├── marquee.h                # Header for marquee
│   ├── menu.cpp                 # Implements main menu logic
│   ├── menu.h                   # Header for menu
│   ├── utils.cpp                # Utility functions
│   └── utils.h                  # Header for utility functions
├── CMakeLists.txt               # CMake configuration file
└── README.md                    # Project documentation
```

## Features
- **Command Interpreter**: Processes user commands such as:
  - `help`: Displays available commands.
  - `start_marquee`: Starts the marquee display.
  - `stop_marquee`: Stops the marquee display.
  - `set_text <text>`: Sets the text to be displayed in the marquee.
  - `set_speed <milliseconds>`: Sets the speed of the marquee animation.
  - `exit`: Exits the emulator.

- **Text Marquee**: A scrolling text display that can be customized by the user.

- **Main Menu**: A user-friendly interface for command input and displaying available commands.

## Setup Instructions
1. Clone the repository:
   ```
   git clone <repository-url>
   ```
2. Navigate to the project directory:
   ```
   cd os-emulator
   ```
3. Create a build directory and navigate into it:
   ```
   mkdir build && cd build
   ```
4. Run CMake to configure the project:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make
   ```

## Usage
To run the OS emulator, execute the compiled binary:
```
./os-emulator
```
You will be presented with a command prompt where you can enter commands to control the marquee and interact with the emulator.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.