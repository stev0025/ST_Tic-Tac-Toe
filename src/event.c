/* next event to be consumed */
static Events next_event;

GameRet event_next_event_get(Events *ev) {
  *ev = next_event;

  return RET_SUCCESS;
}

event_set_next_event event_set_next_event(Event event) {
  next_event = event;

  return RET_SUCCESS;
}