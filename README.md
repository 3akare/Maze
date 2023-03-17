# OpenGL 3D Maze Game
## Introduction
The OpenGL 3D Maze Game is an exciting and challenging game built using OpenGL. It offers a unique and immersive experience to players who enjoy solving puzzles and exploring labyrinthine worlds.

The game is played using the W, A, S, and D keys on the keyboard. These keys allow the player to navigate the maze and interact with various objects. The game also has different versions, each with its own unique features and improvements.

## Compilation

The code was compiled using gcc and the following flags.

`-Wall -Werror -Wextra -pedantic`

To run the game, visit [Version 3](./Version-3/)

Then, run in your teminal

`./a.out`

**Note: This is for MacOS Only**

## Playing the Game
Once you've compiled the code, you can run the game by typing `./a.out` into your terminal or by dragging and dropping the a.out file onto the terminal icon.

Once the game starts, you can use the following keys to navigate the maze:

- W: Move forward
- A: Rotate towards the left
- D: Rotate towards the right
- S: Move backward
- E: Open doors (in version 3, doors will not open if the player doesn't possess a key)

## Folders
The game contains six folders, each with its own specific functionality:

<b> Starting-SDL: </b> This folder contains the initial steps taken with the SDL library, such as installation, initializing SDL, and setting up a window.

<b>Starting_SDL_With_OpenGl:</b> This folder explores another library that could make the game faster and more efficient. It compares the SDL and OpenGL libraries.

<b>Version-1:</b> This is the first version of the game's raycaster. It's a bit laggy, but it works. It contains a makefile used to compile the source code.

<b>Version-2:</b> This version includes new features such as collision detection, wall, door, ceiling, floor, and window textures. It improves upon the previous version by providing a more realistic environment.

<b>Version-3:</b> This is the current version of the game, and it includes even better textures, a lose and win state, and an enemy sprite. In this version, the player must navigate through the maze while avoiding the enemy to win.

## Author
This game was created by David Bakare. David is a skilled game developer with experience in building exciting games using various programming languages and libraries.

## Acknowledgments
3dSage was a significant source of inspiration for this game. The creator of 3dSage provides useful resources and tutorials for game developers, and their content was instrumental in the development of this game.

## License
This project is licensed under the MIT License. You are free to modify and distribute the game, as long as you give proper credit to the author. The game is open-source, and you are encouraged to contribute to its development by visiting the GitHub repository and submitting pull requests.