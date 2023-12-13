# Text Adventure Game in C

A basic text adventure game implemented in C, featuring various files for different aspects of the game. This project represents a rudimentary form of a text-based interactive story.

## About

This text adventure game is a simple interactive story where the player can navigate through different rooms, interact with items, encounter monsters, and make choices to progress through the game. The implementation is kept intentionally basic to serve as a foundation for more advanced features and improvements.

## Files

- `command.c`: Contains functions related to processing player commands.
- `item.c` and `item.h`: Implementations and declarations for game items.
- `main.c` and `main.h`: The main program file and its header, responsible for initiating the game loop.
- `monster.c` and `monster.h`: Implementations and declarations for game monsters.
- `player.c` and `player.h`: Implementations and declarations for the player character.
- `room.c` and `room.h`: Implementations and declarations for game rooms.
- `userTypes.h`: Header file defining custom data types used across the program.

## Compilation

Compile the program using a C compiler. For example, using GCC:

```bash
gcc main.c command.c item.c monster.c player.c room.c -o text_adventure
