include "game_logic.h"
include "render.h"

/**
 * @brief render the game board
 * 
 * Below is the example of rendered 3x3 game board:
 * 
 *  X | O | X 
 * ---+---+---
 *    | O |   
 * ---+---+---
 *  O | X |   
 */
static void render_gameboard() {
    char board[BOARD_SIZE][BOARD_SIZE];

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

void render_overall_display() {
    int score[2];

    /* get current score */
    gamelogic_score_get(score);

    /* print score */
    printf("X   X        OOO \n");
    printf("  X   %d : %d O   O\n", score[0], score[1]);
    printf("X   X        OOO \n");

    /* render gameboard */
    render_gameboard();

    /* mention the player to play the current turn */
    printf("Current turn:  Player %c", player_current_turn);

    return;
}