#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "logs.h"
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"

int main() {
    bool running = true;
    Events next_event = EVENT_LAST;
    States next_state = STATE_LAST;
    GameRet ret = RET_SUCCESS;

    /* initialize games */
    ret = gamelogic_initialize_game();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed gamelogic_initialize_game()");
        return 0;
    }

    while (running) {
        /* Get Next Event */
        ret = event_next_event_get(&next_event);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed event_next_event_get()");
        }

        /* Get Next State */
        ret = sm_state_next_get(next_event, &next_state);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed sm_state_next_get()");
        }

        /* Handle the next State */
        ret = sm_handler(next_state);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed sm_handler()");
        }

        /* Check if the game is still running */
        // ret = gamelogic_is_game_running(&running);
        // if (ret != RET_SUCCESS) {
        //     log_message(LOG_WARN, "Failed gamelogic_is_game_running()");
        // }
        running = false; // TBD: just stop it for testing
    }

    log_message(LOG_INFO, "Exiting game loop.");

    /* terminate the game */
    ret = gamelogic_terminate_game();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed gamelogic_terminate_game()");
    }

    return 0;
}