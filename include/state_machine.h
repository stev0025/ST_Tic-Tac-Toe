#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

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

/* string representation for enum States */
#define STR_STATE_NONE "STATE_NONE"
#define STR_STATE_INIT "STATE_INIT"
#define STR_STATE_EMPTY_BOARD "STATE_EMPTY_BOARD"
#define STR_STATE_PLAYER_TURN "STATE_PLAYER_TURN"
#define STR_STATE_CHECK_WIN "STATE_CHECK_WIN"
#define STR_STATE_END_GAME "STATE_END_GAME"
#define STR_STATE_ERROR "STATE_ERROR"
#define STR_STATE_LAST "STATE_LAST"

/**
 * @brief Handle the current state
 * 
 * @param TBD
 */
GameRet sm_handler();

/**
 * @brief Get the next state based on the event
 */
GameRet sm_state_next_get(Events ev);

/**
 * @brief Get the current state
 */
GameRet sm_state_current_get(States *current_state);

/**
 * @brief Set the current state
 */
GameRet sm_state_current_set(States state);

#endif // STATE_MACHINE_H