#include <stdio.h>
#include <stdlib.h>

#include "lib/disksAndPlayers.h"
#include "lib/movelib.h"
#include "lib/playerio.h"

int main()
{
    // Variables declaration
    // player player1, player2;
    disk board[SIZE][SIZE];

    // initializePlayers(&player1, &player2);
    player player1 = {"eoghan", WHITE, 2};
    player player2 = {"sam", BLACK, 2};
    printf("\n");

    initializeBoard(board);

    int playing = 1; //game is in play

    int move;
    int amt_vald_mvs = 0;
    position *valid_moves = (position *) calloc( sizeof(position), amt_vald_mvs);

    do {

      int play_able = 0;

      amt_vald_mvs = findAllPos(board, player1, valid_moves);
      if (amt_vald_mvs != 0) {
        printGameState(board, player1, player2);
        move = readMoves(valid_moves, amt_vald_mvs);
        board[valid_moves[move-1].row][valid_moves[move-1].col].type = player1.type;
        flipDisks(1,board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player1.points, &player2.points);
        player1.points++;
        play_able++;
      }

      amt_vald_mvs = findAllPos(board, player2, valid_moves);
      if (amt_vald_mvs != 0) {
        printGameState(board, player2, player1);
        move = readMoves(valid_moves, amt_vald_mvs);
        board[valid_moves[move-1].row][valid_moves[move-1].col].type = player2.type;
        flipDisks(0,board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player2.points, &player1.points);
        player2.points++;
        play_able++;
      }

      if (play_able == 0) {
        playing = 0;
      }

    } while(playing == 1);

    free (valid_moves);

    printf("The final score is: \n");
    printf("%s: %d | %s: %d\n", player1.name, player1.points, player2.name, player2.points);
    if (player1.points > player2.points) {
      printf("%s WON!\n", player1.name);
    }else if (player1.points < player2.points) {
      printf("%s WON!\n", player2.name);
    }else {
      printf("It was a draw!\n");
    }

    return 0;
}
