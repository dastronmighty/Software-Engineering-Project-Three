#ifndef PLAYERIO_H_
#define PLAYERIO_H_

#include "disksAndPlayers.h"

void printGameState(disk board[SIZE][SIZE], player cur, player opp);

int readMoves(position *pos_arr, int pos_arr_len);

void printMoves(position *pos_arr, int pos_arr_len);

#endif
