# ESP32 FreeRTOS Button and LED Example

This code is a simple example of using FreeRTOS on an ESP32 microcontroller to control a button and an LED. It defines two tasks, cyclic_task and acyclic_task, that run concurrently.

## Folder contents

The project **Lab2** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt` files that provide set of directives and instructions describing the project's source files and targets (executable, library, or both).

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```

## Getting Started
Clone or Download the Code: You can clone this code repository or download the source files to your local development environment.

* Modify GPIO Pins (Optional):

    * You can change the GPIO pins for the button and LED by editing the constants in the code.
    * By default, BUTTON_PIN is set to GPIO pin 4. If your button is connected to a different pin, update this value accordingly.

* Build and Flash:

    * Build the code using the ESP-IDF build system.
    * Flash the compiled binary to your ESP32 device.

## Code Overview
* cyclic_task:
    * This task periodically prints "2012667" every second.
    * It serves as a cyclic task that runs continuously in the background.
* acyclic_task:
    * This task monitors the state of a button (connected to BUTTON_PIN).
    * When the button is pressed (logic level 0), it prints "ESP32" to the console.
    * The task checks the button state every 10 milliseconds and introduces a 1-second delay to avoid multiple button presses.
* Running the Code
    After flashing the code to your ESP32, the two tasks (cyclic_task and acyclic_task) will start running.

    * The cyclic_task will continuously print your student identifier ("2012667") to the console every second.
    * The acyclic_task will monitor the button state. When the button connected to BUTTON_PIN is pressed, it will print "ESP32" to the console.

## Running commands

* Build the Project

    * Run `idf.py build`

* Flash onto the Device

    * Run `idf.py -p PORT flash`

* Monitor the Output

    * Run `idf.py -p PORT monitor`