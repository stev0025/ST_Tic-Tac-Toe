/* list of states */
typedef enum {
  STATE_NONE,
  STATE_INIT,
  STATE_PLAYER_X_TURN,
  STATE_PLAYER_O_TURN,
  STATE_CHECK_WIN,
  STATE_END_GAME
} StateMachineStates;

/**
 * @brief TBD
 * 
 * TBD: explain
 * 
 * @param TBD
 */
void statemachine_handler(event);

/**
 * @brief 
 */
StateMachineStates statemachine_game_state_get();