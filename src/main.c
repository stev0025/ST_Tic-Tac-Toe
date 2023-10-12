#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  /* initialize the game */
  gamelogic_initialize_game();

  /* loop through states */
  while(true) {
    userinput_process_user_input();
    statemachine_transition();

  }

  /* terminate the game */
  gamelogic_terminate_game();

  return 0;
}
