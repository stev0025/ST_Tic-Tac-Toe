/* list of events */
typedef enum {
  EVENT_NONE,
  EVENT_START_GAME,
  EVENT_FIRST_PLAYER_ACTION,
  EVENT_PLAYER_FILLED_IN,
  EVENT_PLAYER_NEXT_TURN,
  EVENT_WINNER_ANNOUNCE,
  EVENT_END_GAME,
  EVENT_RESTART
}Events;

/* return type for event functions */
typedef enum {
    RET_EVENT_SUCCESS,
    RET_EVENT_FAIL
} EventsRet;