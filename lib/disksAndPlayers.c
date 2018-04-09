#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "disksAndPlayers.h"
 
 
void initializePlayers(player *player1, player *player2){
    int nameSize;
    // Insert player 1
    printf("Player 1 please insert your name:   \n");
    fgets(player1 -> name, 20, stdin);
    nameSize = strlen(player1 -> name);
    player1 -> name[nameSize -1] = '\0';
 
    // Assign colours and points to player 1
    player1 -> type = BLACK;
    player1 -> points = 2;
 
    // Insert player 2
    printf("Player 2 please insert your name:   \n");
    fgets(player2 -> name, 20, stdin);
    nameSize = strlen(player2 -> name);
    player2 -> name[nameSize -1] = '\0';
 
    // Assign colours and points to player 2
    player2 -> type = WHITE;
    player2 -> points = 2;
 
}
 
void initializeBoard(disk board [SIZE][SIZE]){
 int i, j;
 //board initialization
    for(i=0; i< SIZE; i++){
        for(j=0;j<SIZE; j++){
            if(i==3){
                if(j==3)
                    board[i][j].type = WHITE;
                else{
                    if(j==4)
                        board[i][j].type = BLACK;
                    else
                        board[i][j].type = NONE;
                    }
                }
            else {
                if(i==4){
                    if(j == 3)
                        board[i][j].type = BLACK;
                    else {
                        if(j == 4)
                        board[i][j].type = WHITE;
                        else
                            board[i][j].type = NONE;
                        }
                    }
                else
                    board[i][j].type = NONE;
            }
              board[i][j].pos.row = i;
              board[i][j].pos.col = j;
 
            }
        }
    }
 
 
void printBoard(disk board[SIZE][SIZE]){
    int i,j;
    j = 0;
    printf("    ");
    for(i=0; i< SIZE; i++){
        printf("%d   ",i+1);
    }
    for(i=0; i< SIZE; i++){
        printf("\n%d | ", i+1);
        for(j=0;j<SIZE; j++){
            switch(board[i][j].type){
                case BLACK:
                    printf("1 | ");
                    break;
                case WHITE:
                    printf("0 | ");
                    break;
                case NONE:
                    printf("x | ");
                    break;
                default:
                    break;
            }
        }
    }
    printf("\n");
}
 
 
void flipDisksWhite(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score){
  int i, j, k, is_in = 0;
 
  for (i = 0; i < disk_arr_len; i++)
  {
    if (arr[i].pos.row == cur_disk.pos.row && arr[i].pos.col == cur_disk.pos.col)
    {
        is_in = 1;
    }
  }
 
  if (is_in == 1) 
  {
    for (i = 0; i < disk_arr_len; i++)
    {
      if (arr[i].type == BLACK)
      {
        for (j = i+1; j < disk_arr_len; j++) 
        {
 
          if (arr[j].type == NONE)
          {
            break;
          }
 
          if (arr[j].type == BLACK) 
          {
            for (k = i+1; k <= j-1; k++)
            {
              printf("flipping disk at row%d col%d\n", arr[k].pos.row+1, arr[k].pos.row+1);
              *cur_score = *cur_score + 1;
              *opp_score = *opp_score - 1;
              board[arr[k].pos.row][arr[k].pos.col].type = BLACK;
            }
            break;
          }
 
        }
      }
    }
  }
 
}
 
void flipDisksBlack(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score)
{
  int i, j, k, is_in = 0;
 
  for (i = 0; i < disk_arr_len; i++)
  {
    if (arr[i].pos.row == cur_disk.pos.row && arr[i].pos.col == cur_disk.pos.col)
    {
      is_in = 1;
    }
  }
 
  if (is_in == 1) 
  {
    for (i = 0; i < disk_arr_len; i++) 
    {
      if (arr[i].type == WHITE) 
      {
        for (j = i+1; j < disk_arr_len; j++) 
        {
          if (arr[j].type == NONE)
          {
            break;
          }
          if (arr[j].type == WHITE) 
          {
            for (k = i+1; k <= j-1; k++) 
            {
              printf("flipping disk at row%d col%d\n", arr[k].pos.row+1, arr[k].pos.row+1);
              *cur_score = *cur_score + 1;
              *opp_score = *opp_score - 1;
              board[arr[k].pos.row][arr[k].pos.col].type = WHITE;
            }
            break;
          } 
        }
      }
    }
  }
}