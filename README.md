# Electronic Voting System

## Project Overview

This project implements a standalone Electronic Voting System designed for secure and efficient elections using a microcontroller (PIC18F4722), an LCD display, and a 7-segment display for real-time vote visualization. The system is built to provide a user-friendly interface for voters and ensure accurate vote counting.

The primary goal was to develop a robust embedded solution for electoral processes, focusing on input management, candidate selection, and vote tallying, all within a compact hardware setup.

## Features

* **Real-time Vote Management:** Handles voter inputs and updates candidate vote counts dynamically.
* **User-Friendly Interface:** Utilizes an LCD (Liquid Crystal Display) for displaying candidate information and voting prompts.
* **Intuitive Candidate Selection:** Employs an Analog-to-Digital Converter (ADC) input (simulated by a potentiometer in Proteus) for selecting candidates.
* **Vote Counting & Display:** Accurately tallies votes for multiple candidates and displays the highest vote count on a 4-digit 7-segment display.
* **Time-Limited Voting:** Implements a countdown timer for the voting period.
* **Debounce Implementation:** Ensures accurate button presses by handling switch debouncing in software.
* **Modular C Code:** Organized into separate header and source files for better maintainability and readability.

## Hardware Components

The system is designed to be implemented on a **PIC18F4722 microcontroller**. Key hardware components include:

* **PIC18F4722 Microcontroller:** The central processing unit for the system.
* **LCD (Liquid Crystal Display):** Used for displaying menus, candidate names, and voting prompts. (e.g., a 16x2 or 20x4 LCD).
* **7-Segment Display (4-digit):** Displays the real-time highest vote count.
* **Push Buttons:** For entering the number of voters, incrementing digits, and confirming votes.
* **Potentiometer:** Simulates an analog input for candidate selection (connected to an ADC channel, e.g., AN0).
* **Resistors & Transistors:** Supporting components for interfacing displays and buttons.

## Software / Development Environment

* **Microcontroller Language:** C
* **IDE:** MPLAB IDE (or similar PIC development environment)
* **Simulation Tool:** Proteus (for circuit design and simulation)

## Code Structure

The project's codebase is organized into the following files:

* `include.h`: Global definitions, pin assignments for LCD and 7-segment display, ADC configuration, and function prototypes.
* `lcd.h`: Header file for LCD control function prototypes.
* `lcd.c`: Implementation of LCD functions (initialize, command, data, clear, set cursor, write string).
* `proj1.c`: Main program logic, including ADC initialization and read, `int_to_str`, `str_to_int`, `blinker`, `update_votes`, `get_candidate_index`, `display_digit`, `display_number`, `find_highest_votes`, and the `main` function.

## How it Works

1.  **System Initialization:** The LCD, ADC, and I/O ports are initialized upon power-up.
2.  **Voter Count Input:** The system first prompts the user to enter the total number of voters using push buttons and displays the input on the LCD.
3.  **Candidate Selection:** During the active voting phase, an analog input (from the potentiometer) is read via the ADC. Different ranges of the ADC value correspond to different candidates.
4.  **Vote Casting:** A dedicated button press confirms the vote for the currently selected candidate.
5.  **Vote Tallying:** The `update_votes` function increments the vote count for the selected candidate.
6.  **Real-time Display:**
    * The LCD shows the current candidate being selected and the remaining voting time.
    * The 7-segment display continuously updates to show the highest number of votes received by any candidate so far.
7.  **Voting Conclusion:** Once the set number of voters has cast their votes or the timer expires, the system enters a final state, optionally displaying the results.

## Getting Started

To simulate or run this project:

1.  **Software Installation:**
    * Install MPLAB X IDE (or your preferred PIC C compiler).
    * Install Proteus for circuit simulation.
2.  **Clone the Repository:**
    ```bash
    git clone [https://github.com/Alirazbtw/electronic-voting-system.git](https://github.com/Alirzabtw/electronic-voting-system.git)
    cd electronic-voting-system
    ```
3.  **Open in Proteus:**
    * Open the `.pdsprj` file (Proteus project file) from the cloned repository to view the circuit diagram and simulation setup.
4.  **Compile the Code:**
    * Open the C source files (`.c` and `.h`) in MPLAB IDE.
    * Compile the code to generate the `.hex` file.
5.  **Load Firmware to Microcontroller (in Proteus):**
    * In Proteus, double-click the PIC18F4722 microcontroller.
    * Browse and select the generated `.hex` file as the firmware.
6.  **Run Simulation:**
    * Start the simulation in Proteus to observe the system's operation.

## Contributing

Feel free to fork this repository, submit pull requests, or open issues for any improvements or bug fixes.

## License

This project is licensed under the [MIT License](LICENSE) - see the `LICENSE` file for details.

## Contact

* alirza.taghizadeh.2017@gmail.com
