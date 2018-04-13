#ifndef PLAYERIO_H_
#define PLAYERIO_H_

#include "disksAndPlayers.h"

/*print the board and botht the players current score*/
void printGameState(disk board[SIZE][SIZE], player cur, player opp);

/*take in the players input*/
int readMoves(position *pos_arr, int pos_arr_len);

/*print the available moves*/
void printMoves(position *pos_arr, int pos_arr_len);

#endif
