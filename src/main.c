#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    bool running = true;
    Events next_event = EVENT_START;
    States next_state = STATE_START;
    SMRet ret_sm = RET_SM_SUCCESS;
    EventsRet ret_event = RET_EVENT_SUCCESS;

    /* initialize games */
    gamelogic_initialize_game();
    /* TBD: error handling */

    while (running) {
        /* Get Next Event */
        ret_event = event_next_event_get(&next_event);
        if (ret_event != RET_EVENT_SUCCESS) {
          /* TBD: error handling */
        }

        /* Get Next State */
        ret_sm = sm_state_next_get(next_event, &next_state);
        if (ret_sm != RET_SM_SUCCESS) {
          /* TBD: error handling */
        }

        /* Handle the next State */
        ret_sm = sm_handler(next_state);
        if (ret_sm != RET_SM_SUCCESS) {
          /* TBD: error handling */
        }

        /* Check if the game is still running */
        gamelogic_is_game_running(&running);
        /* TBD: error handling */
    }

    /* terminate the game */
    gamelogic_terminate_game();
    /* TBD: error handling */

    return 0;
}