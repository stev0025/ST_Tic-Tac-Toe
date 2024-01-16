/* current state of the game */
static States game_state;

SMRet sm_handler(States state) {
    switch (state) {
        case STATE_INIT:
            return sm_handle_init();
            break;
        case STATE_EMPTY_BOARD:
            return sm_handle_init();
            break;
        case STATE_PLAYER_X_TURN:
            return sm_handle_player_x();
            break;
        case STATE_PLAYER_O_TURN:
            return sm_handle_player_o();
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

SMRet sm_handle_init() {

}

SMRet sm_handle_empty_board() {

}

SMRet sm_handle_player_x() {

}

SMRet sm_handle_player_o() {

}

SMRet sm_handle_check_win() {

}

SMRet sm_handle_end_game() {

}