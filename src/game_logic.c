#include <stdbool.h>
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

GameRet gamelogic_current_board_get(char **board) {
    // TBD;
    return RET_LAST;
}

GameRet gamelogic_score_get(int score[2]) {
    // TBD;
    return RET_LAST;
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

    ret = event_set_next_event(EVENT_START_PROGRAM);
    if (ret != RET_SUCCESS) {
        /* TBD: error catcher */
    };

    ret = sm_state_current_set(STATE_NONE);
    if (ret != RET_SUCCESS) {
        /* TBD: error catcher */
    };

    ret = gamelogic_player_turn_set(PLAYER_TURN_X);
    if (ret != RET_SUCCESS) {
        /* TBD: error catcher */
    };

    return RET_SUCCESS;
}

GameRet gamelogic_terminate_game() {
    /* TBD: return success for now */
    return RET_SUCCESS;
}