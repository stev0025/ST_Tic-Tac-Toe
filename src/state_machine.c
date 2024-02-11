#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
#include "logs.h"
#include "render.h"

/* current state of the program */
static States sm_state;

/* forward declaration */
static GameRet sm_handle_init();
static GameRet sm_handle_empty_board();
static GameRet sm_handle_player_turn();
static GameRet sm_handle_check_win();
static GameRet sm_handle_end_game();
static GameRet sm_handle_error();

/* state transition table, based on current state & incoming event */
States sm_state_transition[STATE_LAST][EVENT_LAST] = {
    { // Current state: STATE_NONE
        STATE_INIT, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    },
    { // Current state: STATE_INIT
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_EMPTY_BOARD, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    },
    { // Current state: STATE_EMPTY_BOARD
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_PLAYER_TURN, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    },
    { // Current state: STATE_PLAYER_TURN
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_CHECK_WIN, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    },
    { // Current state: STATE_CHECK_WIN
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_PLAYER_TURN, // EVENT_PLAYER_NEXT_TURN
        STATE_END_GAME, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    },
    { // Current state: STATE_END_GAME
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_EMPTY_BOARD  // EVENT_RESTART
    },
    { // Current state: STATE_ERROR
        STATE_LAST, // EVENT_START_PROGRAM
        STATE_LAST, // EVENT_START_GAME
        STATE_LAST, // EVENT_FIRST_PLAYER_ACTION
        STATE_LAST, // EVENT_PLAYER_FILLED_IN
        STATE_LAST, // EVENT_PLAYER_NEXT_TURN
        STATE_LAST, // EVENT_WINNER_ANNOUNCE
        STATE_LAST, // EVENT_END_GAME
        STATE_LAST  // EVENT_RESTART
    }
};

GameRet sm_handler() {
    switch (sm_state) {
        case STATE_INIT:
            return sm_handle_init();
            break;
        case STATE_EMPTY_BOARD:
            return sm_handle_empty_board();
            break;
        case STATE_PLAYER_TURN:
            return sm_handle_player_turn();
            break;
        case STATE_CHECK_WIN:
            return sm_handle_check_win();
            break;
        case STATE_END_GAME:
            return sm_handle_end_game();
            break;
        default:
            log_message(LOG_ERROR, "sm_handler(): hit non-functioning state: %s", log_enum_to_str_states(sm_state));
            return sm_handle_error();
    }
}

GameRet sm_state_next_get(Events ev) {
    log_message(LOG_DEBUG, "sm_state_next_get(): current state: %s", log_enum_to_str_states(sm_state));
    log_message(LOG_DEBUG, "sm_state_next_get(): current event: %s", log_enum_to_str_events(ev));

    /* Transition to next state */
    sm_state = sm_state_transition[sm_state][ev];

    log_message(LOG_DEBUG, "sm_state_next_get(): next state   : %s", log_enum_to_str_states(sm_state));

    return RET_SUCCESS;
}

GameRet sm_state_current_get(States *current_state) {
    *current_state = sm_state;
    return RET_SUCCESS;
}

GameRet sm_state_current_set(States state) {
    sm_state = state;
    return RET_SUCCESS;
}

static GameRet sm_handle_init() {
    GameRet ret = RET_LAST;
    char user_in;

    log_message(LOG_DEBUG, "sm_handle_init(): enter");

    /* clear terminal */
    gamelogic_clear_terminal();

    /* print out welcome message that prompt user input*/
    render_welcome_message();

    /* wait for any input before continuing */
    scanf("%c", &user_in);

    /* Set next event to EVENT_START_GAME */
    ret = event_next_event_set(EVENT_START_GAME);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "failed sm_handle_init():event_next_event_set()");
        return ret;
    }

    return RET_SUCCESS;
}

static GameRet sm_handle_empty_board() {
    GameRet ret = RET_LAST;

    log_message(LOG_DEBUG, "sm_handle_empty_board(): enter");

    /* clear terminal and render empty gameboard */
    gamelogic_clear_terminal();
    ret = render_gameboard();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed sm_handle_empty_board():render_gameboard()");
        return ret;
    };

    /* wait 2 second for aestethic */
    sleep(2);

    /* Set next event to EVENT_FIRST_PLAYER_ACTION */
    ret = event_next_event_set(EVENT_FIRST_PLAYER_ACTION);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "failed sm_handle_empty_board():event_next_event_set()");
        return ret;
    }

    return RET_SUCCESS;
}

static GameRet sm_handle_player_turn() {
    GameRet ret = RET_LAST;
    PlayerTurn player;

    log_message(LOG_DEBUG, "sm_handle_player_turn(): enter");

    /* loop until the player input correct box */
    while (true) {
        int row = 0;
        int col = 0;

        /* clear terminal and render gameboard */
        gamelogic_clear_terminal();
        ret = render_gameboard();
        if (ret != RET_SUCCESS) {
            log_message(LOG_ERROR, "Failed sm_handle_player_turn():render_gameboard()");
            return ret;
        };

        /* Get current player turn */
        ret = gamelogic_player_turn_get(&player);
        if (ret != RET_SUCCESS) {
            log_message(LOG_ERROR, "Failed sm_handle_player_turn():gamelogic_player_turn_get()");
            return ret;
        }

        /* Get the player's input for the box to be filled in */
        printf("Please fill in the row (0 to 2):");
        scanf("%d", &row);
        printf("Please fill in the col (0 to 2):");
        scanf("%d", &col);

        /* validate the user input */
        if (row < 0 && row > 2 && col < 0 && col > 2) {
            /* user filled wrongly. loop again */
            printf("Wrong input");
            sleep(2);
            continue;
        }
        /* TBD: Check if the cell is already occupied */

        /* fill in the cell */
        gamelogic_board_fill_cell(player, row, col);

        /* exit the loop */
        break;
    }

    /* clear terminal and render the new gameboard */
    gamelogic_clear_terminal();
    ret = render_gameboard();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed sm_handle_player_turn():render_gameboard()");
        return ret;
    };

    /* Set next event to EVENT_PLAYER_FILLED_IN */
    ret = event_next_event_set(EVENT_PLAYER_FILLED_IN);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "failed sm_handle_player_turn():event_next_event_set()");
        return ret;
    }

    return RET_SUCCESS;
}

static GameRet sm_handle_check_win() {
    GameRet ret = RET_LAST;
    bool found_winner = false;

    log_message(LOG_DEBUG, "sm_handle_check_win(): enter");

    /* 1. check if the winner is decided */
    char winner = gamelogic_board_check_win();
    if (winner != ' ') {
        found_winner = true;
    }

    if (found_winner) {
        /* 2.1. winner is found. End the game */
        log_message(LOG_DEBUG, "sm_handle_check_win(): winner is found: %c", winner);

        /* Set next event to EVENT_WINNER_ANNOUNCE */
        ret = event_next_event_set(EVENT_WINNER_ANNOUNCE);
        if (ret != RET_SUCCESS) {
            log_message(LOG_ERROR, "failed sm_handle_check_win():event_next_event_set()");
            return ret;
        }
    } else {
        /* 2.2. winner is not yet decided. continue to the next turn */
        log_message(LOG_DEBUG, "sm_handle_check_win(): continue to the next player");

        /* set the next player */
        PlayerTurn player;
        gamelogic_player_turn_get(&player);
        gamelogic_player_turn_set(player ^ 1); // Note: between 0 ('X') or 1 ('O')

        /* Set next event to EVENT_PLAYER_NEXT_TURN */
        ret = event_next_event_set(EVENT_PLAYER_NEXT_TURN);
        if (ret != RET_SUCCESS) {
            log_message(LOG_ERROR, "failed sm_handle_check_win():event_next_event_set()");
            return ret;
        }
    }

    return RET_SUCCESS;
}

static GameRet sm_handle_end_game() {
    log_message(LOG_DEBUG, "sm_handle_end_game(): enter");

    /* TBD */
    return RET_SUCCESS;
}

/**
 * @brief handler for error or non-functioning states
 */
static GameRet sm_handle_error() {
    log_message(LOG_DEBUG, "sm_handle_error(): enter");

    /* stop main loop runner */
    gamelogic_game_running_set(false);

    return RET_SUCCESS;
}