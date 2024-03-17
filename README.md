# Tic-Tac-Toe Game in C

A simple Tic-Tac-Toe game implemented in C language.\
The game allows 2 players to take turns and compete againt each other in classic Tic-Tac-Toe.

## Installation
1. Build the code by executing `make`
2. Launch the game by executing `./launch_game.sh`

## Development
### Docker Container
A Dockerfile is provided for development environment\
To use the container, please modify the [VARIABLE] as needed:
1. cd [PROJECT_DIRECTORY]/ST_Tic-Tac-Toe
2. docker build -t [USERNAME]/dev-env-tictactoe:latest .
3. docker run -it --name tictactoe_container [IMAGENAME]:[VERSION] /bin/sh

### CI/CD
GitHub Actions is utilized for CI/CD.\
Jobs:
1. linting:
    - Description: formats the C code according to guidelines
    - Trigger: triggered on each push to the repository
    - Command: lints yourself before pushing to the repository: `find . -iname *.c -o -iname *.h | xargs clang-format -i -style=file`
2. compile-and-build:
    - Description: compiles the code and builds the project artifacts
    - Trigger: triggered on each push to the repository
3. test:
    - Description: runs various tests to ensure code functionality
    - Trigger: triggered on each push to the repository

## Features
### Board Representation
A 3x3 grid to represent the game board.
Cells can be occupied by "X", "O", or be empty.

### 2 Player Game
2 players: one is "X", the other is "O".
The game starts with player 'X', and they take turns.

## Architecture: Single-Threaded Event-Driven State Machine architecture
This game is built on single-threaded, Event-Driven, State Machine architecture.
- Single-Threaded: The entire game runs on a single thread.
- Event-Driven: The program operates by reacting to events.
- State Machine: The game maintains a state. It transitions between various states based on the events it processes.

The program is designed to wait for an event at the end of each state handler, as it maintains a consistent and responsive game experience. 

## State Machine and Events
### List of States
#### Initialization
The initial state when the game first launches.
In this state, the game displays a welcome message and a brief introduction to the game.
After displaying the welcome message and introduction for a few seconds, the game prompts the player to input any button in order to continue. This message serves to engage the player and signals that the game is ready to proceed upon their input.

#### Empty Board
This state displays the current scores.
Then, it displays the empty game board & current scores.

#### Player Turn
Allow either Player X or Player O to interact with the game board by choosing a row & column to place their 'X' or 'O' marker.
Update the game board by placing the marker in the chosen row & column.

#### Check Win
Assess the current game board.
It could determine if there is a winner or if a draw condition has been met after a player's turn.
It could invite the next player to play.

#### End Game
Conclude the game by displaying the result, whether it's a win for a player or a draw.
Ask players if they want to play another round or exit the game.

#### Error
An error state occurs when an unexpected event happens.

### List of Events
- Start Program
- Start Game
- First Player Action
- Player Filled In
- Player Next Turn
- Winner Announce
- End Game
- Restart

### Transitions between states
```
None            --StartProgram     --> Initialization
Initialization  --StartGame        --> Empty Board
Empty Board     --FirstPlayerAction--> Player Turn
Player Turn     --PlayerFilledIn   --> Check Win
Check Win       --PlayerNextTurn   --> Player Turn
Check Win       --WinnerAnnounce   --> End Game
End Game        --EndGame          --> End Program
End Game        --Restart          --> Empty Board
```

## Code Structure
```
ST_Tic-Tac-Toe
|-- .github/workflows/ci-pipeline.yml
|-- include/
|   |-- event.h
|   |-- game_logic.h
|   |-- logs.h
|   |-- state_machine.h
|   |-- render.h
|   |-- state_machine.h
|-- src/
|   |-- event.c
|   |-- game_logic.c
|   |-- logs.c
|   |-- main.c
|   |-- render.c
|   |-- state_machine.c
|-- README.md
```

