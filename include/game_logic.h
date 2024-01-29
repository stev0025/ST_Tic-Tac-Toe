#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

/* board size */
#define BOARD_SIZE 3

/* Player turn */
typedef enum {
    PLAYER_TURN_X,
    PLAYER_TURN_O,
    PLAYER_LAST
} PlayerTurn;

/* Generic return type */
typedef enum {
    RET_SUCCESS,
    RET_EVENT_FAIL,
    RET_SM_FAIL,
    RET_GL_FAIL,
    RET_REND_FAIL,
    RET_LAST
} GameRet;

/**
 * @brief initialize game
 *
 * - Initialize log file
 * - Set next event into EVENT_START_PROGRAM
 * - Set current state into STATE_NONE
 * - Set current player turn to be player X
 */
GameRet gamelogic_initialize_game();

/**
 * @brief terminate game
 */
GameRet gamelogic_terminate_game();

/**
 * @brief check if game is still running
 */
GameRet gamelogic_is_game_running(bool *running);

/**
 * @brief get current Tic-Tac-Toe board
 */
GameRet gamelogic_current_board_get(char **board);

/**
 * @brief get current score
 */
GameRet gamelogic_score_get(int score[2]);

/**
 * @brief get current player turn
 */
GameRet gamelogic_player_turn_get(PlayerTurn *player);

#endif // GAME_LOGIC_H