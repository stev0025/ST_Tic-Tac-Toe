#include <stdbool.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"

/* next event to be consumed */
static Events next_event;

GameRet event_next_event_get(Events *ev)
{
  *ev = next_event;

  return RET_SUCCESS;
}

GameRet event_next_event_set(Events event)
{
  next_event = event;

  return RET_SUCCESS;
}