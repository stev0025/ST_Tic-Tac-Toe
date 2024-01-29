#ifndef EVENT_H
#define EVENT_H

/* list of events */
typedef enum {
  EVENT_START_PROGRAM,
  EVENT_START_GAME,
  EVENT_FIRST_PLAYER_ACTION,
  EVENT_PLAYER_FILLED_IN,
  EVENT_PLAYER_NEXT_TURN,
  EVENT_WINNER_ANNOUNCE,
  EVENT_END_GAME,
  EVENT_RESTART,
  EVENT_LAST
}Events;

/* string representation for enum Events */
#define STR_EVENT_START_PROGRAM "EVENT_START_PROGRAM"
#define STR_EVENT_START_GAME "EVENT_START_GAME"
#define STR_EVENT_FIRST_PLAYER_ACTION "EVENT_FIRST_PLAYER_ACTION"
#define STR_EVENT_PLAYER_FILLED_IN "EVENT_PLAYER_FILLED_IN"
#define STR_EVENT_PLAYER_NEXT_TURN "EVENT_PLAYER_NEXT_TURN"
#define STR_EVENT_WINNER_ANNOUNCE "EVENT_WINNER_ANNOUNCE"
#define STR_EVENT_END_GAME "EVENT_END_GAME"
#define STR_EVENT_RESTART "EVENT_RESTART"
#define STR_EVENT_LAST "EVENT_LAST"

/**
 * @brief get the next event
 */
GameRet event_next_event_get(Events *ev);

/**
 * @brief set the next event
 */
GameRet event_next_event_set(Events event);

#endif // EVENT_H