#ifndef DISKAANDPLAYERS_H_
#define DISKAANDPLAYERS_H_

#define SIZE 8

enum colour{
    WHITE,
    BLACK,
    NONE
};

typedef struct position{
    int row;
    int col;
} position;

typedef struct disk{
    enum colour type;
    position pos;
} disk;

typedef struct player{
    char name[20];
    enum colour type;
    int points;
} player;

void initializePlayers(player *player1, player *player2);

void initializeBoard(disk board[SIZE][SIZE]);

void printBoard(disk board [SIZE][SIZE]);

//flip white disks inbetween two black disks in the passed in arr
void flipWhiteDisks(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score);

//flip black disks inbetween two white disks in the passed in arr
void flipBlackDisks(disk cur_disk, disk board[SIZE][SIZE], disk arr[], int disk_arr_len, int *cur_score, int *opp_score);

#endif
