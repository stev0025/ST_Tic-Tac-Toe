# Tic-Tac-Toe Game in C

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [How to Play](#how-to-play)
4. [Features](#features)
5. [State Machine](#state-machine)
6. [Code Structure](#code-structure)
7. [Architecture](#architecture)
8. [Action Items](#action-items)

## Introduction
A simple Tic-Tac-Toe game implemented in C language.
The game allows 2 players to take turns and compete againts each other in classic Tic-Tac-Toe.
Both players play in the same device.

## Installation
TBD: Please explain thoroughly
make
make clean

## How to Play
TBD

## Features
### Board Representation
Game board and ruler.
A 3x3 grid to represent the game board.
A ruler on the perimeter of the board. The ruler indicates the row & column.
Cells can be occupied by "X", "O", or be empty.

### Player Turn
2 players: one is "X", the other is "O".
The game start with player "X", and they take turns.

### User Input
Allows player to select a cell to place their symbol by inputting the coordinates in text.
Player cannot input illegal or occupied cells.

### Game Status
TBD

### Winning Conditions
TBD

### Draw Condition
TBD

### Restart Option
TBD

## Architecture: Single-Threaded Event-Driven State Machine architecture
This Tic-Tac-Toe game is built on single-threaded, Event-Driven, State Machine architecture.
This architecture combines the simplicity of single-thread programming, responsiveness of event-driven programming with the clarity and organization of a state machine.

Single-Threaded: The entire game runs on a single thread.
Event-Driven: The program operates by reacting to events.
State Machine: The game maintains a state. It transitions between various states based on the events it processes.

the program is designed to wait for an event at the end of each state handler, as it maintains a consistent and responsive game experience. 

### Benefits of Choosen Architecture
Clarity and Organization: By structuring the game around distinct states, the code becomes more organized and easier to manage.

Ease of Debugging: This clear separation makes debugging simpler, as issues can often be isolated within specific states or transitions. It also allows for easier maintenance and potential expansion of the game, as new states or events can be added with minimal impact on existing code.

Scalability: It also allows for potential expansion of the game, as new states or events can be added with minimal impact on existing code.

Responsive User Experience: It ensures that the game responds promptly and efficiently to user inputs and other events, leading to a responsive and engaging user experience.

Predictable Behavior: The state machine approach provides a clear and predictable flow of the game, which is crucial for both the players and developers. It helps in understanding how the game will behave in different scenarios.

## State Machine and Events
### List of States
#### Initialization
The initial state when the game first launches.
In this state, the game displays a welcome message and a brief introduction to the game.
After displaying the welcome message and introduction for a few seconds, The game prompts the player to input any button in order to continue. This message serves to engage the player and signals that the game is ready to proceed upon their input.

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
An error state when unexpected event occurs.

### List of Events
#### Start Program

#### Start Game
The "Start Game" event is marking the transition from the initialization phase to the actual start of the game. This event is designed to occur at the end of the Initialization State.

User Input: The "Start Game" event is triggered by any user input, such as a mouse click or a keypress. This design choice ensures that the game progresses at the player's pace, allowing them to start the game when they are ready.

#### First Player Action
The "First Player Action" event marks that we have given enough time to the users to understand the situation in "Empty Board" state. This event is triggered by timer.

#### Player Filled In

#### Player Next Turn

#### Winner Announce

#### End Game

#### Restart

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
|-- include/
|   |-- event.h
|   |-- game_logic.h
|   |-- logs.h
|   |-- state_machine.h
|   |-- render.h
|   |-- state_machine.h
|   |-- user_input.h
|-- src/
|   |-- event.c
|   |-- game_logic.c
|   |-- logs.c
|   |-- main.c
|   |-- render.c
|   |-- state_machine.c
|   |-- user_input.c
|-- README.md
```

## Action Items
- change the StateMachine diagram in README
- fill in the state machine handlers
- create the display inside render files
- create user input validation
- create logs