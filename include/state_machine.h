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
 * @brief transitions from current to new states
 * 
 * TBD: explain
 * 
 * @param TBD
 */
void statemachine_transition(current_state);

/**
 * @brief 
 */
StateMachineStates statemachine_game_state_get();