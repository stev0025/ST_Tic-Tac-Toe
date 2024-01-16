/* next event to be consumed */
static Events next_event;

EventsRet event_next_event_get(Events *ev) {
  ev = next_event;

  return RET_EVENT_SUCCESS;
}

void event_set_next_event(Event event) {
  next_event = event;
}