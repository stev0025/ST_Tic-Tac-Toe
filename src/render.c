#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "game_logic.h"
#include "event.h"
#include "state_machine.h"
#include "render.h"
#include "logs.h"

/**
 * @brief center text by adding padding based on total width
 */
static void render_center_text(char *text, int totalWidth)
{
  int len = strlen(text);
  int padding = (totalWidth - len) / 2;
  for (int i = 0; i < padding; i++)
  {
    putchar(' ');
  }
  printf("%s\n", text);
}

/**
 * @brief render the board
 *
 * Below is the example of rendered 3x3 game board:
 *
 *  X | O | X
 * ---+---+---
 *    | O |
 * ---+---+---
 *  O | X |
 */
static GameRet render_gameboard_board()
{
  GameRet ret = RET_SUCCESS;

  /* get current Tic-Tac-Toe board */
  char(*board)[BOARD_SIZE] = gamelogic_board_get();

  /* draw board */
  for (int row = 0; row < BOARD_SIZE; row++)
  {
    printf("   ");
    for (int col = 0; col < BOARD_SIZE; col++)
    {
      printf(" %c ", board[row][col]);
      if (col < 2)
      {
        printf("|");
      }
    }

    printf("\n");
    printf("   ");
    if (row < 2)
    {
      printf("---+---+---\n");
    }
  }
  printf("\n");

  return RET_SUCCESS;
}

GameRet render_gameboard()
{
  GameRet ret = RET_SUCCESS;
  int score[2];
  PlayerTurn player;

  /* get current score */
  ret = gamelogic_score_get(score);
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR, "Failed render_gameboard():gamelogic_score_get()");
    return ret;
  }

  /* print score */
  printf("X   X        OOO \n");
  printf("  X   %d : %d O   O\n", score[0], score[1]);
  printf("X   X        OOO \n");
  printf("\n");

  /* render gameboard */
  ret = render_gameboard_board();
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR,
                "Failed render_gameboard():render_gameboard_board()");
    return ret;
  }

  /* mention the player to play the current turn */
  ret = gamelogic_player_turn_get(&player);
  if (ret != RET_SUCCESS)
  {
    log_message(LOG_ERROR,
                "Failed render_gameboard():gamelogic_player_turn_get()");
    return ret;
  }
  printf("Current turn: %c Player\n", player == PLAYER_TURN_X ? 'X' : 'O');

  return RET_SUCCESS;
}

void render_welcome_message()
{
  int max_width = 79;

  /* displaying welcome message */
  render_center_text("Welcome to Tic-Tac-Toe!", max_width);
  printf("\n");
  render_center_text("This is a 2-player turn-based game.", max_width);
  render_center_text(
      "Each player will take turns to place either 'X' or 'O' on the board.",
      max_width);
  printf("\n");

  /* wait before asking for user input */
  sleep(2);

  /* displaying message to ask user input */
  render_center_text("Please click any button to continue", max_width);

  return;
}