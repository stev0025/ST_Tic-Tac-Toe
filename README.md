# Tic-Tac-Toe Game in C

## Table of Contents
1. [Introduction](#introduction)
2. [Installation](#installation)
3. [How to Play](#how-to-play)
4. [Features](#features)
5. [State Machine](#state-machine)
6. [Code Structure](#code-structure)
7. [Architecture](#architecture)

## Introduction
A simple Tic-Tac-Toe game implemented in C language.
The game allows 2 players to take turns and compete againts each other in classic Tic-Tac-Toe.
Both players play in the same device.

## Installation
TBD

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

## State Machine
### List of States
#### Initialization
TBD
#### Player X's Turn
TBD
#### Player O's Turn
TBD
#### Check Win
TBD
#### End Game
TBD
#### Restart
TBD

### Transitions
#### Initialization -> Player X's Turn
#### Player X's Turn -> Check Win
#### Player O's Turn -> Check Win
#### Check Win -> Player O's Turn
#### Check Win -> Player X's Turn
#### Check Win -> Check Draw
#### Check Win -> End Game
#### Check Draw -> End Game
#### End Game -> Restart
#### Restart -> Initialization

## Code Structure
ST_Tic-Tac-Toe
|-- src/
|   |-- main.c
|   |-- state_machine.c
|   |-- game_logic.c
|   |-- render.c
|   |-- user_input.c
|-- include/
|   |-- state_machine.h
|   |-- game_logic.h
|   |-- render.h
|   |-- user_input.h

## Architecture
TBD, likely Event-Driven State Machine Architecture