#include <stdbool.h>
#include <stdlib.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
#include "logs.h"

/* Variable to control the loop's execution */
bool run_loop = true;

/* Scores for players X and Y */
static int gamelogic_score[2];

/* Current player turn */
PlayerTurn player_turn = PLAYER_LAST;

/* TicTacToe board */
char gamelogic_board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char (*gamelogic_board_get(void))[BOARD_SIZE] {
    return gamelogic_board;
}

void gamelogic_board_fill_cell(PlayerTurn player, int row, int col) {
    /* TBD: use switch-case for variable answer */
    char answer = (player == PLAYER_TURN_X ? 'X' : 'O');

    /* TBD: input validation for row & col */

    gamelogic_board[row][col] = answer;

    return;
}

char gamelogic_board_check_win() {
    // Check horizontal and vertical lines
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0];
        }
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i];
        }
    }

    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        return board[0][2];
    }

    // No winner
    return ' ';
}

GameRet gamelogic_score_get(int *scores) {
    scores[0] = gamelogic_score[0];
    scores[1] = gamelogic_score[1];
    return RET_SUCCESS;
}

GameRet gamelogic_player_turn_set(PlayerTurn player) {
    player_turn = player;
    return RET_SUCCESS;
}

GameRet gamelogic_player_turn_get(PlayerTurn *player) {
    *player = player_turn;
    return RET_SUCCESS;
}

GameRet gamelogic_game_running_set(bool running) {
    run_loop = running;

    return RET_SUCCESS;
}

GameRet gamelogic_game_running_get(bool *running) {
    *running = run_loop;

    return RET_SUCCESS;
}

GameRet gamelogic_initialize_game() {
    GameRet ret = RET_LAST;

    log_init();

    log_message(LOG_INFO, "Starting game initialization.");

    ret = event_next_event_set(EVENT_START_PROGRAM);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed event_next_event_set()");
        return RET_GL_FAIL;
    };

    ret = sm_state_current_set(STATE_NONE);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed sm_state_current_set()");
        return RET_GL_FAIL;
    };

    ret = gamelogic_player_turn_set(PLAYER_TURN_X);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed gamelogic_player_turn_set()");
        return RET_GL_FAIL;
    };

    gamelogic_score[0] = 0;
    gamelogic_score[1] = 0;

    return RET_SUCCESS;
}

GameRet gamelogic_terminate_game() {
    log_message(LOG_INFO, "Starting game termination.");

    /* TBD: return success for now */
    return RET_SUCCESS;
}

void gamelogic_clear_terminal() {
#ifdef LINUX
    system("clear");
#else
    /* untested */
    system("cls");
#endif
}