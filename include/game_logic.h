#define BOARD_SIZE 3

/**
 * @brief initialize game
 */
void gamelogic_initialize_game();

/**
 * @brief terminate game
 */
void gamelogic_terminate_game();

/**
 * @brief check if game is still running
 */
void gamelogic_is_game_running();

/**
 * @brief get current Tic-Tac-Toe board
 */
void gamelogic_current_board_get(char board[BOARD_SIZE][BOARD_SIZE]);

/**
 * @brief get current score
 */
void gamelogic_score_get(int score[2]);