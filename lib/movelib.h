#ifndef MOVELIB_H_
#define MOVELIB_H_

#include "disksAndPlayers.h"

/*check which colour disks need to be flipped*/
void flipWhich(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score);

/*look for a disk in an array */
int searchPositions(disk arr[], int disk_arr_len, player check, position *pos_arr, int pos_arr_len);

/*search everything left of a selected disk in an array*/
int searchLeft(disk arr[], int cur, player check, position *pos_arr, int pos_arr_len);

/*search everything right of a selected disk in an array*/
int searchRight(disk arr[],int disk_arr_len, int cur, player check, position *pos_arr, int pos_arr_len);

/*check and add a position to the valid moves array*/
int addToValidPos(position *arr, position put_in, int len);

/*break the board into 38 different 1d arrays and call searching methods on each array*/
int findAllPos(disk board [SIZE][SIZE], player cur, position *pos_arr);

/*break the board into 38 different 1d arrays and flip disks where necessary*/
void flipDisks(disk cur_disk, disk board[SIZE][SIZE], int *cur_score, int *opp_score);

#endif
