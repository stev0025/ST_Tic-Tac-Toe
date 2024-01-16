/* current state of the program */
static States sm_state;

/* state transition table, based on current state & incoming event */
SMRet sm_state_transition[STATE_LAST][EVENT_LAST] = {
    { // Current state: STATE_NONE
        STATE_INIT, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    },
    { // Current state: STATE_INIT
        STATE_X, // EVENT_START_PROGRAM
        STATE_EMPTY_BOARD, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    },
    { // Current state: STATE_EMPTY_BOARD
        STATE_X, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_PLAYER_TURN, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    },
    { // Current state: STATE_PLAYER_TURN
        STATE_X, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_CHECK_WIN, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    },
    { // Current state: STATE_CHECK_WIN
        STATE_X, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_PLAYER_TURN, // EVENT_PLAYER_NEXT_TURN
        STATE_END_GAME, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    },
    { // Current state: STATE_END_GAME
        STATE_X, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_EMPTY_BOARD  // EVENT_RESTART
    },
    { // Current state: STATE_ERROR
        STATE_X, // EVENT_START_PROGRAM
        STATE_X, // EVENT_START_GAME
        STATE_X, // EVENT_FIRST_PLAYER_ACTION
        STATE_X, // EVENT_PLAYER_FILLED_IN
        STATE_X, // EVENT_PLAYER_NEXT_TURN
        STATE_X, // EVENT_WINNER_ANNOUNCE
        STATE_X, // EVENT_END_GAME
        STATE_X  // EVENT_RESTART
    }
};

static SMRet sm_handle_init() {
    render_welcome_message();

    /* TBD: scanf for user input, then continue */
    return RET_SM_SUCCESS;
}

static SMRet sm_handle_empty_board() {

}

static SMRet sm_handle_player_turn() {

}

static SMRet sm_handle_check_win() {

}

static SMRet sm_handle_end_game() {

}

SMRet sm_handler(States state) {
    switch (state) {
        case STATE_INIT:
            return sm_handle_init();
            break;
        case STATE_EMPTY_BOARD:
            return sm_handle_init();
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
