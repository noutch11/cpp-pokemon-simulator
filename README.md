# C++ Pokémon Battle Simulator

A robust, text-based monster-collection and battle engine built to demonstrate core **Object-Oriented Programming (OOP)** principles, efficient **Data Structure** management, and **File I/O** in C++.

## Key Features
* **Dynamic Team Management:** Implemented logic to manage a 4-Pokemon team, including automated systems to evaluate and replace members based on Combat Power (CP) stats.
* **Procedural Content Generation:** Utilized probability-based searching to encounter "Common," "Uncommon," and "Ultra Rare" entities from a master list of 151 unique creatures.
* **Persistent Data Loading:** Engineered a file-parsing engine to load entity data from external text files into internal master arrays.
* **State-Based Gameplay:** Comprehensive main menu system allowing users to search, train, display stats, and battle against randomized opponents.

## Technical Engineering Highlights
* **Object-Oriented Architecture:** Designed the `Pokemon` class to encapsulate core attributes like CP, Rarity, and Index Numbers, utilizing overloaded constructors for flexible object creation.
* **Strategic Logic:** Implemented a "Training" system that allows users to increase an entity's CP, capped by the individual maximum value found in the master PokeDex.
* **Algorithmic Probability:** Developed a rarity-weighted search algorithm using random number generation to determine successful encounters based on user-selected rarity levels.
* **Clean Code & Standards:** Adheres to industry standards with a strict separation of header (`.h`) and implementation (`.cpp`) files, including header guards and constants to prevent the use of magic numbers.

## Project Structure
* **`Pokemon.h / .cpp`**: Defines the core entity, its attributes, and growth logic.
* **`Game.h / .cpp`**: The primary engine managing game states, file parsing, and team logic.
* **`proj2.cpp`**: The entry point provided to seed the random number generator and initialize the core game loop.
* **`makefile`**: Automated build script with `clean`, `run`, and `submit` targets.
