#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"

int main() {
    bool running = true;
    Events next_event = EVENT_LAST;
    States next_state = STATE_LAST;
    GameRet ret = RET_SUCCESS;

    /* initialize games */
    gamelogic_initialize_game();
    /* TBD: error handling */

    while (running) {
        /* Get Next Event */
        ret = event_next_event_get(&next_event);
        if (ret != RET_SUCCESS) {
            /* TBD: error handling */
        }

        /* Get Next State */
        ret = sm_state_next_get(next_event, &next_state);
        if (ret != RET_SUCCESS) {
            /* TBD: error handling */
        }

        /* Handle the next State */
        ret = sm_handler(next_state);
        if (ret != RET_SUCCESS) {
            /* TBD: error handling */
        }

        /* Check if the game is still running */
        ret = gamelogic_is_game_running(&running);
        if (ret != RET_SUCCESS) {
            /* TBD: error handling */
        }
        
    }

    /* terminate the game */
    gamelogic_terminate_game();
    /* TBD: error handling */

    return 0;
}