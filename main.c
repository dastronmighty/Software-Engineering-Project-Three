#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/disksAndPlayers.h"
#include "lib/movelib.h"
#include "lib/playerio.h"

int main()
{
    //Variables declaration
    player player1, player2;
    disk board[SIZE][SIZE];

    initializePlayers(&player1, &player2);

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
        flipDisks(0,board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player1.points, &player2.points);
        player1.points++;
        play_able++;
      }

      amt_vald_mvs = findAllPos(board, player2, valid_moves);
      if (amt_vald_mvs != 0) {
        printGameState(board, player2, player1);
        move = readMoves(valid_moves, amt_vald_mvs);
        board[valid_moves[move-1].row][valid_moves[move-1].col].type = player2.type;
        flipDisks(1,board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player2.points, &player1.points);
        player2.points++;
        play_able++;
      }

      if (play_able == 0) {
        playing = 0;
      }

    } while(playing == 1);

    free (valid_moves);

    printf("\n");

    FILE *fl_ptr;
    int name_len;
    char score_str[3];

    if ( (fl_ptr = fopen("gameresults.txt", "a+") ) == NULL ) {

      printf("Error opening file to write to.\n");

    } else {

      name_len = strlen(player1.name);
      char *plyr_1 = malloc( (sizeof(char) * 22) + name_len);
      if (plyr_1 == NULL) {
        printf("Memory Error!\n");
      }else{
        strcpy(plyr_1, "Player1 ");
        strcat(plyr_1, player1.name);
        strcat(plyr_1, ", Points: ");
        sprintf(score_str, "%d", player1.points);
        strcat(plyr_1, score_str);
        strcat(plyr_1, "\n");
      }

      name_len = strlen(player2.name);
      char *plyr_2 = malloc( (sizeof(char) * 22) + name_len);
      if (plyr_2 == NULL) {
        printf("Memory Error\n");
      }else{
        strcpy(plyr_2, "Player1 ");
        strcat(plyr_2, player2.name);
        strcat(plyr_2, ", Points: ");
        sprintf(score_str, "%d", player2.points);
        strcat(plyr_2, score_str);
        strcat(plyr_2, "\n");
      }

      printf("%s", plyr_1);
      fwrite(plyr_1, strlen(plyr_1), 1, fl_ptr);
      printf("%s", plyr_2);
      fwrite(plyr_2, strlen(plyr_2), 1, fl_ptr);

      char *winner;

      if (player1.points > player2.points) {

        name_len = strlen(player1.name);
        winner = malloc( (sizeof(char) * 15) + name_len );

        if (winner == NULL) {
          printf("Memory Error\n");
        }else{
          strcpy(winner, "The winner is ");
          strcat(winner, player1.name);
          strcat(winner, "\n");
          printf("%s", winner);
          if ( fwrite(winner, strlen(winner), 1, fl_ptr) != 1 ) {
            printf("Write error!\n");
          }
        }

      }else if (player1.points < player2.points) {

        name_len = strlen(player1.name);
        winner = malloc( (sizeof(char) * 15) + name_len );

        if (winner == NULL) {
          printf("Memory Error\n");
        }else{
          strcpy(winner, "The winner is ");
          strcat(winner, player2.name);
          strcat(winner, "\n");
          printf("%s", winner);
          if ( fwrite(winner, strlen(winner), 1, fl_ptr) != 1) {
            printf("Error!\n");
          }
        }
      }else {
        name_len = 18;
        winner = malloc( (sizeof(char) * 15) + name_len );
        if (winner) {
          printf("Memory Error\n");
        }else{
          strcpy(winner, "The winner is ");
          strcat(winner, "no one, its a draw");
          strcat(winner, "\n");
          printf("%s", winner);
          if ( fwrite(winner, strlen(winner), 1, fl_ptr) != 1) {
            printf("Error!\n");
          }
        }
      }
    }

    fclose(fl_ptr);

    return 0;
}
