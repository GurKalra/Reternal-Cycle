# Reternal Cycle

Reternal Cycle is a text-based adventure game inspired by *Returnal*. It features an immersive world where players explore procedurally generated rooms, interact with items, and engage in combat. The game is written in C and focuses on dynamic room allocation, an inventory system, and an upcoming weapon combat mechanic.

## Features
- **Exploration**: Navigate interconnected rooms with unique descriptions and items.
- **Inventory System**: Pick up, use, and drop items dynamically.
- **Procedural Room Generation** *(Upcoming)*: Rooms will be generated dynamically to enhance replayability.
- **Weapon Combat System** *(Upcoming)*: Players will engage in battles using a variety of weapons.
- **Dynamic Memory Management** *(Upcoming)*: Efficient handling of room and item allocation for scalability.

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/GurKalra/Reternal-Cycle.git
   ```
2. Navigate to the project folder:
   ```sh
   cd Reternal-Cycle
   ```
3. Compile the game using GCC:
   ```sh
   gcc -o reternal_cycle main.c
   ```
4. Run the game:
   ```sh
   ./reternal_cycle
   ```

## How to Play
- Move between rooms using:
  ```
  go north
  go south
  go east
  go west
  ```
- Pick up items:
  ```
  pickup [item name]
  ```
- Drop items:
  ```
  drop [item number]
  ```
- Use items:
  ```
  use [item name]
  ```
- View inventory:
  ```
  inventory
  ```
- Quit the game:
  ```
  quit
  ```

## Future Plans
- Implement procedural room generation for unique gameplay experiences.
- Introduce a combat system with different weapons and enemy encounters.
- Improve memory management to support dynamic room allocation.

## Contributions
Contributions are welcome! Feel free to fork the repository and submit pull requests.

## License
This project is licensed under the MIT License.

---
