static Events next_event = VENT_NONE;

Event event_get_next_event() {
  return next_event;
}

void event_set_next_event(Event event) {
  next_event = event;
}