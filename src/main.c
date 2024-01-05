#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  /* initialize the game */
  gamelogic_initialize_game();

  while(true) {
    // Wait for an event
    userinput_process_user_input();
    // how if we create 'event' instead of 'user_input'?
    // because 'event' encapsulates 'user_input', we can have much more flexible events that happened!

    statemachine_handler(event);

  }

  /* terminate the game */
  gamelogic_terminate_game();

  return 0;
}
