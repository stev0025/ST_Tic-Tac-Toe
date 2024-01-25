#include "game_logic.h"
#include "event.h"
#include "state_machine.h"

/* current state of the program */
static States sm_state;

/* forward declaration */
static GameRet sm_handle_init();
static GameRet sm_handle_empty_board();
static GameRet sm_handle_player_turn();
static GameRet sm_handle_check_win();
static GameRet sm_handle_end_game();

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

GameRet sm_handler(States state) {
    switch (state) {
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
            /* TBD: print error, then return fail */
    }
}

GameRet sm_state_next_get(Events ev, States *next_state) {
    /* TBD: use sm_state_transition() to get the next state */
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
    render_welcome_message();

    /* TBD: scanf for user input, then continue */
    return RET_SUCCESS;
}

static GameRet sm_handle_empty_board() {

}

static GameRet sm_handle_player_turn() {

}

static GameRet sm_handle_check_win() {

}

static GameRet sm_handle_end_game() {

}
