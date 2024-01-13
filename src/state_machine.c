/* current state of the game */
static States game_state;



SMRet sm_handler(States state) {
    switch (state) {
        case STATE_INIT:
            return sm_handle_init();
            break;
        /* TBD: continue other states */
        default:
            /* default statements */
    }
}

SMRet sm_handle_init() {

}

SMRet sm_handle_player_x() {

}

SMRet sm_handle_player_o() {

}

SMRet sm_handle_check_win() {

}

SMRet sm_handle_end_game() {

}