#ifndef MOVELIB_H_
#define MOVELIB_H_

#include "disksAndPlayers.h"

int searchPositions(disk arr[], int disk_arr_len, player check, position *pos_arr, int pos_arr_len);

int searchLeft(disk arr[], int cur, player check, position *pos_arr, int pos_arr_len);

int searchRight(disk arr[],int disk_arr_len, int cur, player check, position *pos_arr, int pos_arr_len);

int addToValidPos(position *arr, position put_in, int len);

int findAllPos(disk board [SIZE][SIZE], player cur, position *pos_arr);

void flipDisks(int to_flip, disk cur_disk, disk board[SIZE][SIZE], int *cur_score, int *opp_score);

#endif