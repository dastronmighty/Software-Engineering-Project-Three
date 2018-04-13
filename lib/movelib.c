#include <stdlib.h>
#include <stdio.h>

#include "disksAndPlayers.h"
#include "movelib.h"

void flipWhich(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score){
  if (cur_disk.type == WHITE){
    flipBlackDisks(cur_disk, board, arr, disk_arr_len, cur_score, opp_score);
  }else{
    flipWhiteDisks(cur_disk, board, arr, disk_arr_len, cur_score, opp_score);
  }
}

void flipDisks(disk cur_disk, disk board[SIZE][SIZE], int *cur_score, int *opp_score)
{
  /*
   go through the board and break it up into a series of arrays.
   for each of the smaller arrays we pass them to a function that checks which
   colours to flip.
  */
  int i, j, x, y;
  disk temp;
  disk arr[SIZE];

  //all the rows in the board
  for (i = 0; i < 8; i++)
  {
    flipWhich(cur_disk, board, board[i], 8, cur_score, opp_score);
  }

  //all the columns in the array
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      arr[j] = board[j][i];
    }
    flipWhich(cur_disk, board, arr, 8, cur_score, opp_score);
  }

  /*-------------------------------DIAGONALS----------------------------------*/
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
    flipWhich(cur_disk, board, arr, num_in_arr, cur_score, opp_score);
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
    flipWhich(cur_disk, board, arr, num_in_arr, cur_score, opp_score);
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
    flipWhich(cur_disk, board, arr, num_in_arr, cur_score, opp_score);
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
    flipWhich(cur_disk, board, arr, num_in_arr, cur_score, opp_score);
  }
  /*-------------------------------DIAGONALS----------------------------------*/

  //from top left to bottom right
  y = 0;
  for (i = 0; i < 8; i++)
  {
    x = i;
    arr[i] = board[x][y];
    y++;
  }
  flipWhich(cur_disk, board, arr, 8, cur_score, opp_score);

  //from bottom left to top right
  y = 7;
  for (i = 0; i < 8; i++)
  {
    x = i;
    arr[i] = board[y][i];
    y--;
  }
  flipWhich(cur_disk, board, arr, 8, cur_score, opp_score);
}

int findAllPos(disk board [SIZE][SIZE], player cur, position *pos_arr)
{
  int moves_found = 0;
  int i, j, x, y;
  disk temp;
  disk arr[SIZE];

  //all the rows in the board
  for (i = 0; i < 8; i++)
  {
    moves_found += searchPositions(board[i], 8, cur, pos_arr, moves_found);
  }

  // all the columns
  for (i = 0; i < 8; i++)
  {
    for (j = 0; j < 8; j++)
    {
      arr[j] = board[j][i];
    }
    moves_found += searchPositions(arr, 8, cur, pos_arr, moves_found);
  }

  /*-------------------------------DIAGONALS----------------------------------*/
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
  /*-------------------------------DIAGONALS----------------------------------*/

  //from top left to bottom right
  y = 0;
  for (i = 0; i < 8; i++)
  {
    x = i;
    arr[i] = board[x][y];
    y++;
  }
  moves_found += searchPositions(arr, 8, cur, pos_arr, moves_found);

  //from botttom left to top right
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
  for (i = 0; i < disk_arr_len; i++)// loop through array
  {
    if (arr[i].type == check.type) //if the current players disk is encountered
    {
      //check if there is a move to the left of the disk
      moves_found += searchLeft(arr, i, check, pos_arr, pos_arr_len);
      //check if there is a move to the right of the disk
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


    //check if the disk we're on is the same as the current one.
    if (temp1.type == check.type)
    {
      break;
    }

    //check if the current is blank and the last one was white
    if (temp1.type == NONE)  //if the current is empty
    {
      if (temp2.type != NONE && temp2.type != check.type) //if the one before was the opposite colour
      {
        /*
          check if the empty cell is already in the move array and if it isnt
          add 1 to the current amount of moves and add one to moves found
        */
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

    //check if the disk we're on is the same as the current one.
    if (temp1.type == check.type)
    {
      break;
    }

    if (temp1.type == NONE) //if the current is empty
    {
      if (temp2.type != NONE && temp2.type != check.type) //if the one before was the opposite colour
      {
        if (addToValidPos(pos_arr, temp1.pos ,cur_amt_mvs) == 1)
        /*
          check if the empty cell is already in the move array and if it isnt
          add 1 to the current amount of moves and add one to moves found
        */
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
  for (i = 0; i < len; i++) //loop through array
  {
    //if new position is already in array.
    if (arr[i].row == put_in.row && arr[i].col == put_in.col)
    {
      isIn++;
    }
  }
  if (isIn == 0) //if new position wasnt in array
  {
    arr = (position *) realloc(arr, len+1); //resize array adding 1 position
    arr[len] = put_in; //insert position to the end of the array.
    return 1;
  }
  return 0;
}
