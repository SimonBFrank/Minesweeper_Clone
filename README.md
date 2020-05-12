# Minesweeper_Clone

This is a C++ Minesweeper clone using SFML.  To run this program, you must first install SFML and then run main.cpp.  

## Functionality

### When a space is revealed:
* If it’s a mine, the game ends 
* If it’s not a mine, it shows the number of mines adjacent to that space (anywhere from 0 to 8, with 0 just showing as an empty space)
* If a space has no adjacent mines, all non-mine spaces adjacent to it are also revealed
* When all of the non-mine spaces have been revealed, the player wins!
### Other features:
* Flags: Right-clicking a space puts a flag on that space, marking it as a possible mine. Flagged spaces cannot be revealed (with left-clicks or as a result of adjacent spaces being revealed), but another right-click will remove the flag.
* Mine Counter: Tracks the number of mines that are on the board. Every time the player places a flag, the counter goes down by one. Every time they remove a flag, the counter goes up by one. The mine counter CAN go negative!
* Restart Button: The smiley face centered at the top or bottom of the window lets you restart a new board with everything reset and mines randomized
### Non-standard features for your version of this project
* Debug Button: Clicking this button will toggle the visibility of the mines on the board.
* Test Buttons #1-3: Clicking on these loads a file with a specific board layout. 

## Required libraries

### SFML

The library that you will be using in this project is SFML—Simple Fast Multimedia Library.  To get started with SFML, visit this site:

* https://www.sfml-dev.org/download/sfml/2.5.1/

You want to download the appropriate version for the IDE/compiler that you are using. If you are using something that isn’t listed there, it is HIGHLY RECOMMENDED that you install and use one of the recommended tools. On Windows that would be Visual Studio, XCode on MacOS, etc. The links on that page are for already-compiled versions of the library which will work “out of the box” with the appropriate compiler.

## File Descriptions

### /boards/

Holds all the .brd (.txt) files used for the test boards.  They are just rows and columns of 1s and 0s, where 0 represents a space where a bomb does not exist and 1 represents a space where a bomb is supposed to be placed.

### /images/

Contains all the .png files for the sprite images.  

### Board.cpp / Board.h

Defines the **Board** obect, all the function protypes, and its constructor.  The board is intialized at the beginning of the game and tiles are placed on top of it.  It uses its own functions to update the board based on the user actions

### Tile.cpp / Tile.h

Defines the **Tile** object and its constructor.  These are used to make the images, like the bombs, number, etc., appear.

### main.cpp

Driving code of the program and determines the rules of the game.

## Author

* Simon Frank
* linkedin.com/in/simon-frank/
* github.com/SimonBFrank/