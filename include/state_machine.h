/* list of states */
typedef enum {
  STATE_NONE,
  STATE_INIT,
  STATE_EMPTY_BOARD,
  STATE_PLAYER_TURN,
  STATE_CHECK_WIN,
  STATE_END_GAME,
  STATE_ERROR,
  STATE_LAST
} States;

/**
 * @brief TBD
 * 
 * TBD: explain
 * 
 * @param TBD
 */
GameRet sm_handler(States state);

/**
 * @brief Get the next state based on the event
 */
GameRet sm_state_next_get(Events ev, States *next_state);

/**
 * @brief Get the current state
 */
GameRet sm_state_current_get(States *current_state);

/**
 * @brief Set the current state
 */
GameRet sm_state_current_set(States state);