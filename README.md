# Flappy-Plus-Plus
This project is a recreation of the iconic Flappy Bird Game using the SFML and C++.

## Overview
### State Pattern
This project utilizes a simplified version of the [state pattern](https://refactoring.guru/design-patterns/state). 

Each state of the game is implemented as a septate class regarding the logic declared in the `GameState` interface. Each of the states implements following methods:
- `init`: initializes and creates a new state
- `handle_input`: handles the users input in regard to the current state
- `update`: updates all of the objects of the state, that can be seen on the screen, based on the previous user interactions and a point in time
- `render`: renders all of the drawable objects

The `Game` class servers the role of the context in this project. It holds all of the "global" variables, that are relevant for all of the game states (for instance `game_over` indicates if the current game has been lost or is still in progress). Moreover, the `Game` class holds of all of the textures and fonts used by the different states. Therefore, all of the textures and sprites are loaded only once and not on every state change. Additionally, the `Game` class provides the functionality to switch and interact with the states. Lastly, the `Game` class contains the main game loop.

The states are stored on a stack. This allows an easy switch between them by using the pop and push functionality. Moreover, this enables to "pause" the game by pushing a new state to the top of the stack without loosing the progress in the game itself. Most of the state transitions logic is contained inside of the states making it more flexible for the future development.

### Simple Newtonian Physics
The `Physics` class includes some simple logic to model the behavior of a physical object inside of the 2D world. The implementation relies on the basic Newtonian Laws of motion. Using the functionality of this class an object of a certain mass can be created. Afterwards a force can be applied to it, that will make it gain acceleration and velocity and, therefore, change its position.

In oder to prevent the object from gaining the velocity indecently it was clipped to some fixed value. 

The functionality of this class has been used in the `Bird` class in order to model a realistically looking falling of the bird. On the other hand, the `Pipe` class does not used the functionally of the `Physics` class, as the pipes do only need a constant speed to be managed by the program in order to be rendered correctly. Consequently, the used of the `Physics` class would be an overkill in this case.

Even thought, the full potential of the `Physics` class has been used in the ret of the project, it was still a gerate exercise in modelling the real life physics.

### Collision Detection
The collision detection has been implemented on top of the functionality provided by the SFML-Library, as it makes it possible to check, whether two rectangles overlap. Any collision of the bird with the frame of the window or with any of the pipes will cause the game over.

## Running the project

### Requirements
Please install the SFML-Library before building and running the project. The installation guide can be found on the [SFML-Website](https://www.sfml-dev.org/tutorials/3.0/getting-started/migrate/). For instance, mac users can install it easily with `brew` by running:
```
brew install sfml
```

### Building and Running using `make`
This project includes the 'Makefile' containing a set of instructions for building and running the game. In order to build and run one can just use:
```
make
```
The executable will be placed in the `./build/bin/main`.

### Building and running using `Cmake`
In order to build the project please run the following commands:
```
cmake -B build
cmake --build build
cp -r assets ~
```
After building the project it can be rund using the following command:
```
./build/bin/main
```
For wiping the assets please use the following:
```
rm -rf  ~/assets
```

## References
### SFML-Template
This project has been built on top ot the [SFML-Template](https://github.com/SFML/cmake-sfml-project). Please see instruction presented in the templates repository if any further questions arise.

### Asset pack by Kenney Vleugels
This project uses the assets kindly provided by by Kenney Vleugels (www.kenney.nl). Licenses can for all of the used assets packs can be found in the assets folder of this project.