# COS214_Practical4
Group 35:
Hayley Nel - u25101821
Keagan van Biljon -
Mohammed Lutchka -u25588304

Project Overview

TaskForge is a film-production work processing system.

The production is represented as a nested hierarchy of:

- Production
- Sequences
- Scenes
- Shots

The system makes use of the following design patterns:

- Composite
- Iterator
- State
- Decorator

## Build Locally

The project requires a C++11 compatible compiler.

Build the project with:


make
Run the main program with:

./taskforge

Run the demonstration main with:

make demo
./demo

Clean generated files with:

make clean

## Docker

Build the Docker image:

docker build -t taskforge .

Run TaskForge inside Docker:

docker run --rm taskforge

The Docker image contains:

g++
make
gdb
valgrind

so no project-specific development tools need to be installed directly on the host system.

Valgrind

Run Valgrind inside Docker:

docker run --rm taskforge \
  valgrind --leak-check=full --show-leak-kinds=all ./taskforge

The final implementation should report no definitely-lost memory.

GDB

Start GDB inside Docker with:

docker run --rm -it taskforge gdb ./taskforge

Example commands:

break ProductionManager::moveShot
run
print shot->getName()
print from->getName()
print to->getName()
next
continue
quit
UML Diagrams

The repository contains exported UML diagrams for:

Class Diagram
Object Diagram
State Diagram
Three Activity Diagrams
Executable

The final executable is named:

taskforge