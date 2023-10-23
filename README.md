# Bug's Life


Welcome to **Bug's Life**, an exciting C++ game with a graphical user interface (GUI) where bugs of different sizes compete for survival in a grid. In this game, bugs eat each other based on their sizes, and each bug has unique abilities.

## Gameplay

### Bug Types

1. **Hopper Bug**: The Hopper Bug can jump one space at a time.

2. **Crawler Bug**: The Crawler Bug can move one block in either x or y direction.

3. **Super Bug**: You can manually control the Super Bug. 

4. **Smart Bug**: The Smart Bug is intelligent and capable of analyzing the playfield. It always aims to hunt down the smallest bug. It takes the shortest path to reach its target, which may include diagonal movement.

### Eating Mechanism

- Bugs eat each other based on their sizes. A bug can eat another bug if its size is larger.

### Game Progress

- The game keeps track of all bug interactions, kills, and the overall progress of the game.
![image](https://github.com/gursimar03/Bugs-Life/assets/49545220/ceeac9a6-8cce-494e-8c07-6b3db8a86225)

### Game Completion

- After the game is finished, all the game statistics, including kills and bug sizes, are stored in a text file for your reference.

## How to Play

1. Clone this repository to your local machine.

   ```bash
   git clone https://github.com/gursimar03/Bugs-lLfe.git
