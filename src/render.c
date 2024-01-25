#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "game_logic.h"
#include "render.h"

/**
 * @brief center text by adding padding based on total width
 */
static void render_center_text(char* text, int totalWidth) {
    int len = strlen(text);
    int padding = (totalWidth - len) / 2;
    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    printf("%s\n", text);
}

/**
 * @brief render the board
 * 
 * Below is the example of rendered 3x3 game board:
 * 
 *  X | O | X 
 * ---+---+---
 *    | O |   
 * ---+---+---
 *  O | X |   
 */
static void render_gameboard_board() {
    char **board;

    /* get current Tic-Tac-Toe board */
    gamelogic_current_board_get(board);

    /* draw board */
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            printf(" %c ", board[row][col]);
            if (col < 2) {
                printf("|");
            }
        }
        printf("\n");
        if (row < 2) {
            printf("---+---+---\n");
        }
    }
}

void render_gameboard() {
    int score[2];
    PlayerTurn player;

    /* get current score */
    gamelogic_score_get(score);

    /* print score */
    printf("X   X        OOO \n");
    printf("  X   %d : %d O   O\n", score[0], score[1]);
    printf("X   X        OOO \n");

    /* render gameboard */
    render_gameboard();

    /* mention the player to play the current turn */
    gamelogic_player_turn_get(&player);
    printf("Current turn:  Player %c", player);

    return;
}

void render_welcome_message() {
    int max_width = 79;

    /* displaying welcome message */
    render_center_text("Welcome to Tic-Tac-Toe!", max_width);
    printf("\n");
    render_center_text("This is a 2-player turn-based game.", max_width);
    render_center_text("Each player will take turns to place either 'X' or 'O' on the board.", max_width);
    printf("\n");

    /* wait before asking for user input */
    sleep(2);

    /* displaying message to ask user input */
    render_center_text("Please click any button to continue", max_width);

    return;
}