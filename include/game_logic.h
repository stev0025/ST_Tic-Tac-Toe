#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

/* board size */
#define BOARD_SIZE 3

/* Player turn */
typedef enum
{
  PLAYER_X,
  PLAYER_O,
  PLAYER_LAST
} Player;

/* Generic return type */
typedef enum
{
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
 * - Set current score to 0:0
 */
GameRet gamelogic_initialize_game();

/**
 * @brief terminate game
 */
GameRet gamelogic_terminate_game();

/**
 * @brief set game running flag
 */
GameRet gamelogic_game_running_set(bool running);

/**
 * @brief get game running flag
 */
GameRet gamelogic_game_running_get(bool *running);

/**
 * @brief get current Tic-Tac-Toe board
 */
char (*gamelogic_board_get(void))[BOARD_SIZE];

/**
 * @brief fill a cell in the Tic-Tac-Toe board
 */
void gamelogic_board_fill_cell(Player player, int row, int col);

/**
 * @brief valdiate the cell is empty
 */
bool gamelogic_board_validate_empty_cell(int row, int col);

/**
 * @brief check if there is already a winner
 *
 * Only check a 3x3 board
 */
Player gamelogic_board_check_win();

/**
 * @brief get score
 */
GameRet gamelogic_score_get(int *scores);

/**
 * @brief add a winning score
 */
GameRet gamelogic_score_add(Player player);

/**
 * @brief set player turn
 */
GameRet gamelogic_player_turn_set(Player player);

/**
 * @brief get player turn
 */
GameRet gamelogic_player_turn_get(Player *player);

/**
 * @brief Clear terminal
 */
void gamelogic_clear_terminal();

/**
 * @brief Clear input buffer before getting scanf
 */
void gamelogic_clear_ip_buffer();

#endif // GAME_LOGIC_H