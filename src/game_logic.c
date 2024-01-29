#include <stdbool.h>
#include <stdlib.h>
#include "logs.h"
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"

/* Scores for players X and Y */
static int gamelogic_score[2];

/* Current player turn */
PlayerTurn player_turn = PLAYER_LAST;

/* TicTacToe board */
char gamelogic_current_board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

char (*gamelogic_current_board_get(void))[BOARD_SIZE] {
    return gamelogic_current_board;
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

GameRet gamelogic_is_game_running(bool *running) {
    /* TBD: return running for now */
    *running = true;
    return RET_SUCCESS;
}

GameRet gamelogic_initialize_game() {
    GameRet ret = RET_LAST;

    log_init();

    log_message(LOG_INFO, "Starting game initialization.");

    ret = event_set_next_event(EVENT_START_PROGRAM);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed event_set_next_event()");
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