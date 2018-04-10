#include <stdlib.h>
#include <stdio.h>
 
#include "disksAndPlayers.h"
#include "movelib.h"
 
int findAllPos(disk board [SIZE][SIZE], player cur, position *pos_arr) 
{
  int moves_found = 0;
  int i, j, x, y;
  disk temp;
  disk arr[SIZE];
  //run rows
  for (i = 0; i < 8; i++) 
  {
    moves_found += searchPositions(board[i], 8, cur, pos_arr, moves_found);
  }
 
  // run columns
  for (i = 0; i < 8; i++) 
  {
    for (j = 0; j < 8; j++) 
    {
      arr[j] = board[j][i];
    }
    moves_found += searchPositions(arr, 8, cur, pos_arr, moves_found);
  }
 
  //run diagonals
  int num_in_arr;
  for (i = 1; i < 6; i++) 
  {
    num_in_arr = 0;
    x = 0, y = i;
    temp = board[x][y];
    while (y < 8)
    {
      arr[num_in_arr] = temp;
      x++;
      y++;
      num_in_arr++;
      temp = board[x][y];
    }
    moves_found += searchPositions(arr, num_in_arr, cur, pos_arr, moves_found);
  }
 
  for (i = 1; i < 6; i++) 
  {
    num_in_arr = 0;
    x = i, y = 0;
    temp = board[x][y];
    while (x < 8)
    {
      arr[num_in_arr] = temp;
      x++;
      y++;
      num_in_arr++;
      temp = board[x][y];
    }
    moves_found += searchPositions(arr, num_in_arr, cur, pos_arr, moves_found);
  }
 
  for (i = 2; i < 7; i++) 
  {
    num_in_arr = 0;
    x = i, y = 0;
    temp = board[x][y];
    while (x >= 0)
    {
      arr[num_in_arr] = temp;
      x--;
      y++;
      num_in_arr++;
      temp = board[x][y];
    }
    moves_found += searchPositions(arr, num_in_arr, cur, pos_arr, moves_found);
  }
 
  for (i = 1; i < 6; i++) 
  {
    num_in_arr = 0;
    x = i, y = 7;
    temp = board[x][y];
    while (x < 8)
    {
      arr[num_in_arr] = temp;
      x++;
      y--;
      num_in_arr++;
      temp = board[x][y];
    }
    moves_found += searchPositions(arr, num_in_arr, cur, pos_arr, moves_found);
  }
 
  y = 0;
  for (i = 0; i < 8; i++)
  {
    x = i;
    arr[i] = board[x][y];
    y++;
  }
  moves_found += searchPositions(arr, 8, cur, pos_arr, moves_found);
 
  y = 7;
  for (i = 0; i < 8; i++)
  {
    x = i;
    arr[i] = board[y][i];
    y--;
  }
  moves_found += searchPositions(arr, 8, cur, pos_arr, moves_found);
 
 
  return moves_found;
}
 
int searchPositions(disk arr[], int disk_arr_len, player check, position *pos_arr, int pos_arr_len) 
{
  unsigned int i;
  int moves_found = 0;
  for (i = 0; i < disk_arr_len; i++) 
  {
    if (arr[i].type == check.type) 
    {
      moves_found += searchLeft(arr, i, check, pos_arr, pos_arr_len);
      moves_found += searchRight(arr, disk_arr_len, i, check, pos_arr, pos_arr_len+moves_found);
    }
  }
  return moves_found;
}
 
int searchLeft(disk arr[], int cur, player check, position *pos_arr, int pos_arr_len) 
{
  disk temp1, temp2;
  int i, moves_found = 0, cur_amt_mvs = pos_arr_len;
  //loop through array going down or 'left'
  for (i = cur; i > 0; i--) 
  {
    temp1 = arr[i - 1];
    temp2 = arr[i];
 
 
    //check if directly next is the same
    if (temp1.type == check.type) 
    {
      break;
    }
 
    //check if the current is blank and the last one was white
    if (temp1.type == NONE) 
    {
      if (temp2.type != NONE && temp2.type != check.type) 
      {
        if (addToValidPos(pos_arr, temp1.pos ,cur_amt_mvs) == 1) 
        {
          moves_found++;
          cur_amt_mvs++;
          break;
        }
      }
      else
      {
        break;
      }
    }
 
  }
  return moves_found;
}
 
int searchRight(disk arr[], int disk_arr_len, int cur, player check, position *pos_arr, int pos_arr_len) 
{
  disk temp1, temp2;
  int i, moves_found = 0, cur_amt_mvs = pos_arr_len;
 
  for (i = cur; i < disk_arr_len-1; i++) 
  {
    temp1 = arr[i + 1];
    temp2 = arr[i];
 
    if (temp1.type == check.type) 
    {
      break;
    }
 
    if (temp1.type == NONE) 
    {
      if (temp2.type != NONE && temp2.type != check.type)
      {
        if (addToValidPos(pos_arr, temp1.pos ,cur_amt_mvs) == 1) 
        {
          moves_found++;
          cur_amt_mvs++;
          break;
        }
      }
      else
      {
        break;
      }
    }
 
  }
  return moves_found;
}
 
int addToValidPos(position *arr, position put_in, int len)
{
  int i, isIn = 0;
  for (i = 0; i < len; i++) 
  {
    if (arr[i].row == put_in.row && arr[i].col == put_in.col) 
    {
      isIn++;
    }
  }
  if (isIn == 0) 
  {
    arr = (position *) realloc(arr, len+1);
    arr[len] = put_in;
    return 1;
  }
  return 0;
}