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

    initializePlayers(&player1, &player2); //set up the players

    initializeBoard(board); //set up the board

    int playing = 1; //game is in play

    int move; //the move the player has chosen.
    int amt_vald_mvs = 0; //the amount of valid moves a player has

    /*create a dynamic array of positions to store the moves a player can make
    it changes every turn.*/
    position *valid_moves = malloc(amt_vald_mvs);

    do { //play

      int play_able = 0; //variable to check whether a player can make a move or not.

      amt_vald_mvs = findAllPos(board, player1, valid_moves); //find all the moves player 1 can make

      if (amt_vald_mvs != 0) {
        printGameState(board, player1, player2); //show the current board and scores

        /*show the available moves and return which move the player selected*/
        move = readMoves(valid_moves, amt_vald_mvs);

        board[valid_moves[move-1].row][valid_moves[move-1].col].type = player1.type; //place disk

        //flip all the disks in line with the placed disk.
        flipDisks(board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player1.points, &player2.points);

        player1.points++; //add one to the players points
        play_able++; //make sure play is able
      }

      amt_vald_mvs = findAllPos(board, player2, valid_moves); //find all the moves player 2 can make
      if (amt_vald_mvs != 0) {

        printGameState(board, player2, player1); //show the current board and scores

        /*show the available moves and return which move the player selected*/
        move = readMoves(valid_moves, amt_vald_mvs);

        board[valid_moves[move-1].row][valid_moves[move-1].col].type = player2.type; //place disk

        //flip all the disks in line with the placed disk.
        flipDisks(board[valid_moves[move-1].row][valid_moves[move-1].col], board, &player2.points, &player1.points);

        player2.points++; //add one to players points
        play_able++; //make sure play is able
      }

      if (play_able == 0) { //check if a finishing state has been reached
        playing = 0; //stop playing
      }

    } while(playing == 1);

    free (valid_moves); //free the allocated memory.

    printf("\n");

    FILE *fl_ptr; //pointer to file
    int name_len; //length of the name
    char score_str[3]; //the score

    if ( (fl_ptr = fopen("gameresults.txt", "a+") ) == NULL ) { //check if file opened up properly

      printf("Error opening file to write to.\n");

    } else {

      name_len = strlen(player1.name); //length of player1's name
      char *plyr_1 = malloc( (sizeof(char) * 22) + name_len); //allocate space

      if (plyr_1 == NULL) {
        printf("Memory Error!\n");
      }else{
        //make a string of format
        //Player1 <player_name>, points: <points_player1>
        strcpy(plyr_1, "Player1 ");
        strcat(plyr_1, player1.name);
        strcat(plyr_1, ", Points: ");
        sprintf(score_str, "%d", player1.points);
        strcat(plyr_1, score_str);
        strcat(plyr_1, "\n");
      }

      name_len = strlen(player2.name); //length of player2's name
      char *plyr_2 = malloc( (sizeof(char) * 22) + name_len); //allocate space

      if (plyr_2 == NULL) {
        printf("Memory Error\n");
      }else{
        //make a string of format
        //Player2 <player_name>, points: <points_player2>
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

      /*
        the following creates a string in the format of:
        The winner is <name_of_winning_player>
        it also prints this string to the console and writes it to a file
      */

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

    fclose(fl_ptr); //close the file

    return (0);
}
