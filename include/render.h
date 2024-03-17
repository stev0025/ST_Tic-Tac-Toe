#ifndef RENDER_H
#define RENDER_H

/**
 * @brief render the whole display of the game board
 *
 * Below is the example of rendered 3x3 game board:
 * X   X        OOO
 *   X   3 : 2 O   O
 * X   X        OOO
 *
 *     X | O | X
 *    ---+---+---
 *       | O |
 *    ---+---+---
 *     O | X |
 *
 * Current turn: Player X
 */
GameRet render_gameboard();

/**
 * @brief render the welcome message
 */
void render_welcome_message();

#endif // RENDER_H