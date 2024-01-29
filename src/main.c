#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
#include "logs.h"

int main() {
    bool running = true;
    Events next_event = EVENT_LAST;
    GameRet ret = RET_SUCCESS;
    int i = 1; // loop count

    /* initialize games */
    ret = gamelogic_initialize_game();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed gamelogic_initialize_game()");
        return 0;
    }

    while (running) {
        log_message(LOG_DEBUG, "main(): loop: %d", i);

        /* Get Next Event */
        ret = event_next_event_get(&next_event);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed event_next_event_get()");
        }

        /* Get to the Next State */
        ret = sm_state_next_get(next_event);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed sm_state_next_get()");
        }

        /* Handle the State */
        ret = sm_handler();
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed sm_handler()");
        }

        /* Check if the game is still running */
        ret = gamelogic_game_running_get(&running);
        if (ret != RET_SUCCESS) {
            log_message(LOG_WARN, "Failed gamelogic_game_running_get()");
        }

        /* DEBUG: increment loop count */
        i++;
    }

    log_message(LOG_INFO, "Exiting game loop.");

    /* terminate the game */
    ret = gamelogic_terminate_game();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed gamelogic_terminate_game()");
    }

    return 0;
}