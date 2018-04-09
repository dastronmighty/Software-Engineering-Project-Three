#include "playerio.h"

#include <stdio.h>
#include "disksAndPlayers.h"

int readMoves(position *pos_arr, int pos_arr_len){
  int move = 0;

  do {
    printf("The moves available are: \n");
    printMoves(pos_arr, pos_arr_len);
    printf("please enter a move number to place a piece there: ");
    scanf("%d", &move);
  } while(move < 1 || move > pos_arr_len);

  printf("placing a piece at row %d, col %d\n", pos_arr[move-1].row+1, pos_arr[move-1].col+1);

  return move;

}

void printMoves(position *pos_arr, int pos_arr_len){
  int i;
  for (i = 0; i < pos_arr_len; i++) {
    printf("MOVE %d: row %d, col %d\n", i+1, pos_arr[i].row+1, pos_arr[i].col+1);
  }
}


void printGameState(disk board[SIZE][SIZE], player cur, player opp){
  printf("%s: %d | %s: %d\n", cur.name, cur.points, opp.name, opp.points);
  printBoard(board);
  if (cur.type == WHITE) {
    printf("It is %s's (0) Turn\n", cur.name);
  }else{
    printf("It is %s's (1) Turn\n", cur.name);
  }
}
