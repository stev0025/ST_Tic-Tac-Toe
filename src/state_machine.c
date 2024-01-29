#include <stdbool.h>
#include <stdio.h>
#include "game_logic.h"
#include "logs.h"
#include "event.h"
#include "state_machine.h"
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
            log_message(LOG_ERROR, "sm_handler(): hit non-functioning state: %d", sm_state);
            return sm_handle_error();
    }
}

GameRet sm_state_next_get(Events ev) {
    log_message(LOG_DEBUG, "sm_state_next_get(): current state: %d", sm_state);
    log_message(LOG_DEBUG, "sm_state_next_get(): current event: %d", ev);

    /* Transition to next state */
    sm_state = sm_state_transition[sm_state][ev];

    log_message(LOG_DEBUG, "sm_state_next_get(): next state: %d", sm_state);

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

    /* clear terminal */
    gamelogic_clear_terminal();

    /* render overall empty gameboard */
    ret = render_gameboard();
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "Failed sm_handle_empty_board():render_gameboard()");
        return ret;
    };

    /* Set next event to EVENT_FIRST_PLAYER_ACTION */
    ret = event_next_event_set(EVENT_FIRST_PLAYER_ACTION);
    if (ret != RET_SUCCESS) {
        log_message(LOG_ERROR, "failed sm_handle_empty_board():event_next_event_set()");
        return ret;
    }

    return RET_SUCCESS;
}

static GameRet sm_handle_player_turn() {
    log_message(LOG_DEBUG, "sm_handle_player_turn(): enter");

    /* TBD */
    return RET_SUCCESS;
}

static GameRet sm_handle_check_win() {
    log_message(LOG_DEBUG, "sm_handle_check_win(): enter");

    /* TBD */
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