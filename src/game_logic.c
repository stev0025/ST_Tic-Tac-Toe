#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
#include "logs.h"

/* Variable to control the loop's execution */
bool run_loop = true;

/* Scores for players X and O */
static int gamelogic_score[2];

/* Current player turn */
Player player_turn = PLAYER_LAST;

/* TicTacToe board */
char gamelogic_board[BOARD_SIZE][BOARD_SIZE] = {{' ', ' ', ' '},
                                                {' ', ' ', ' '},
                                                {' ', ' ', ' '}};

char (*gamelogic_board_get(void))[BOARD_SIZE] { return gamelogic_board; }

void gamelogic_board_fill_cell(Player player, int row, int col)
{
  /* TBD: use switch-case for variable answer */
  char answer = (player == PLAYER_X ? 'X' : 'O');

  gamelogic_board[row][col] = answer;

  return;
}

bool gamelogic_board_validate_empty_cell(int row, int col)
{
  if (gamelogic_board[row][col] == ' ')
  {
    return true;
  }
  else
  {
    return false;
  }
}

Player gamelogic_board_check_win()
{
  Player winner = PLAYER_LAST;
  char winner_symbol = ' '; // No winner as default

  /* Check horizontal and vertical lines */
  for (int i = 0; i < 3; i++)
  {
    if (gamelogic_board[i][0] == gamelogic_board[i][1] &&
        gamelogic_board[i][1] == gamelogic_board[i][2] &&
        gamelogic_board[i][0] != ' ')
    {
      winner_symbol = gamelogic_board[i][0];
      break;
    }
    if (gamelogic_board[0][i] == gamelogic_board[1][i] &&
        gamelogic_board[1][i] == gamelogic_board[2][i] &&
        gamelogic_board[0][i] != ' ')
    {
      winner_symbol = gamelogic_board[0][i];
      break;
    }
  }

  /* Check diagonals */
  if (gamelogic_board[0][0] == gamelogic_board[1][1] &&
      gamelogic_board[1][1] == gamelogic_board[2][2] &&
      gamelogic_board[0][0] != ' ')
  {
    winner_symbol = gamelogic_board[0][0];
  }
  else if (gamelogic_board[0][2] == gamelogic_board[1][1] &&
           gamelogic_board[1][1] == gamelogic_board[2][0] &&
           gamelogic_board[0][2] != ' ')
  {
    winner_symbol = gamelogic_board[0][2];
  }

  /* return winner player, or no winner */
  if (winner_symbol == 'X')
  {
    winner = PLAYER_X;
  }
  else if (winner_symbol == 'O')
  {
    winner = PLAYER_O;
  }
  return winner;
}

GameRet gamelogic_score_get(int *scores)
{
  scores[0] = gamelogic_score[0];
  scores[1] = gamelogic_score[1];
  return RET_SUCCESS;
}

GameRet gamelogic_score_add(Player player)
{
  gamelogic_score[player]++;
  return RET_SUCCESS;
}

GameRet gamelogic_player_turn_set(Player player)
{
  player_turn = player;
  return RET_SUCCESS;
}

GameRet gamelogic_player_turn_get(Player *player)
{
  *player = player_turn;
  return RET_SUCCESS;
}

GameRet gamelogic_game_running_set(bool running)
{
  run_loop = running;

  return RET_SUCCESS;
}

GameRet gamelogic_game_running_get(bool *running)
{
  *running = run_loop;

  return RET_SUCCESS;
}

GameRet gamelogic_initialize_game()
{
  GameRet ret = RET_LAST;

  log_init();

  log_message(LOG_INFO, "Starting game initialization.");

  ret = event_next_event_set(EVENT_START_PROGRAM);
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR, "Failed event_next_event_set()");
    return RET_GL_FAIL;
  };

  ret = sm_state_current_set(STATE_NONE);
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR, "Failed sm_state_current_set()");
    return RET_GL_FAIL;
  };

  ret = gamelogic_player_turn_set(PLAYER_X);
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR, "Failed gamelogic_player_turn_set()");
    return RET_GL_FAIL;
  };

  gamelogic_score[0] = 0;
  gamelogic_score[1] = 0;

  return RET_SUCCESS;
}

GameRet gamelogic_terminate_game()
{
  log_message(LOG_INFO, "Starting game termination.");

  /* TBD: return success for now */
  return RET_SUCCESS;
}

void gamelogic_clear_terminal()
{
#ifdef LINUX
  system("clear");
#else
  /* untested */
  system("cls");
#endif
}

void gamelogic_clear_ip_buffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}