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

/* return type for event functions */
typedef enum {
    RET_EVENT_SUCCESS,
    RET_EVENT_FAIL
} EventsRet;

/**
 * @brief get the next event
 */
EventsRet event_next_event_get(Events *ev);

/**
 * @brief set the next event
 */
void event_set_next_event(Event event);