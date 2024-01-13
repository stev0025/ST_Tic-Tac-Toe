/* list of states */
typedef enum {
  STATE_NONE,
  STATE_INIT,
  STATE_EMPTY_BOARD,
  STATE_PLAYER_X_TURN,
  STATE_PLAYER_O_TURN,
  STATE_CHECK_WIN,
  STATE_END_GAME
} States;

/* return type for state machine functions */
typedef enum {
    RET_SM_SUCCESS,
    RET_SM_FAIL
} SMRet;

/**
 * @brief TBD
 * 
 * TBD: explain
 * 
 * @param TBD
 */
EventsRet sm_handler(state);

/**
 * @brief Get the next state based on the event
 */
EventsRet sm_state_next_get();

/**
 * @brief Get the current state
 */
EventsRet sm_state_current_get();