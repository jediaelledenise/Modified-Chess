/*
Jediaelle Denise De Castro, ID# 12308226
S12 CCDSTRU
 */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define ROWS 7
/* 1 2 3 4 5 6 7 */

#define COLS 5
/* 1 2 3 4 5 */

//FALSE = 0
//TRUE = 1
typedef char str[2]; // string input for prev and next

struct aTag{
    str Alpha[ROWS][COLS];
    int pieces;
};

struct bTag{
    str Beta[ROWS][COLS];
    int pieces;
};


struct MainTag{
    str main[ROWS][COLS]; // main board
    str free[ROWS][COLS];
    struct aTag a;
    struct bTag b;
    str S[ROWS][COLS];
    str prev;
    bool over;
    bool ok; // if valid ung turn
    bool aTurn; // Alpha's turn
};

struct MainTag board;

void initializeValues(){
    board.over = false;
    board.ok = false;
    board.aTurn = true;
}

void initializeBoard(){
    //initialize of table
    int i, j;
    char row = '1';
    char col = '1';
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            board.main[i][j][0] = row;
            board.main[i][j][1] = col;
            col++;
        }
        row++;
        col = '1';
    }
}

void initializeBoardS(){
    //initialize of table
    int i, j;
    char row = '1';
    char col = '1';
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if ((i+1)%2 == (j+1)%2){
                board.S[i][j][0] = row;
                board.S[i][j][1] = col;
            }
            col++;
        }
        row++;
        col = '1';
    }
}

void initializeAlphaBeta(){
    //initialize of table
    int i, j;
    char row = '1';
    char col = '1';
    board.a.pieces = 5;
    board.b.pieces = 5;
    
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if ( ((i+1)%2 == (j+1)%2) && (i==0 || i==1)){
                board.b.Beta[i][j][0] = row;
                board.b.Beta[i][j][1] = col;
            }
            
            col++;
        }
        row++;
        col = '1';
    }

    row = '1';
    col = '1';
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if ( ((i+1)%2 == (j+1)%2) && (i==5 || i==6)){
                board.a.Alpha[i][j][0] = row;
                board.a.Alpha[i][j][1] = col;
            }
            
            col++;
        }
        row++;
        col = '1';
    }
}

void FreeSpaces(){
    //initialize of free spaces table
    int i, j;
    char row = '1';
    char col = '1';
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
                board.free[i][j][0] = row;
                board.free[i][j][1] = col; 
            col++;
        }
        row++;
        col = '1';
    }

    row = '1';
    col = '1';
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if (board.a.Alpha[i][j][0] == board.free[i][j][0] && board.a.Alpha[i][j][1] ==board.free[i][j][1]/*((i+1)%2 == (j+1)%2) && (i==0 || i==1)*/){
                board.free[i][j][0] = 'E';
            }

            else if (board.b.Beta[i][j][0] ==board.free[i][j][0] && board.b.Beta[i][j][1] ==board.free[i][j][1]/*((i+1)%2 == (j+1)%2) && (i==5 || i==6)*/){
                board.free[i][j][0] = 'Y';
            }
            
            else{
                board.free[i][j][0] = row;
                board.free[i][j][1] = col;
            }
            
            col++;
        }
        row++;
        col = '1';
    }
}

void displayBoardS(){
    int i, j;
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            printf("(%c,%c)\t", board.S[i][j][0], board.S[i][j][1]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayAlpha(){
    int i, j;
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            printf("(%c,%c)\t", board.a.Alpha[i][j][0], board.a.Alpha[i][j][1]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayBeta(){
    int i, j;
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            printf("(%c,%c)\t", board.b.Beta[i][j][0], board.b.Beta[i][j][1]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayBoard(){
    int i, j;
    printf("\t 1     2     3     4     5\n\n");
    for (i=0; i<ROWS; i++){
        printf("%d\t", i+1);
        for (j=0; j<COLS; j++){
            if (board.free[i][j][0] == 'E'){
                printf(" %c  | ", board.free[i][j][0]);
            }
            else if (board.free[i][j][0] == 'Y'){
                printf(" %c  | ", board.free[i][j][0]);
            }
            else{
                printf("%c,%c | ", board.free[i][j][0], board.free[i][j][1]);
            }
        }
        printf("\n");
        printf("\t-----------------------------");
        printf("\n");
    }
    printf("\n");
}

int isPrevAlpha(str prev){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(prev[0] == board.a.Alpha[i][j][0] && prev[1] == board.a.Alpha[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

int isPrevBeta(str prev){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(prev[0] == board.b.Beta[i][j][0] && prev[1] == board.b.Beta[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

int isNextFree(str next){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(next[0] == board.free[i][j][0] && next[1] == board.free[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

int isNextAlpha(str next){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(next[0] == board.a.Alpha[i][j][0] && next[1] == board.a.Alpha[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

int isNextBeta(str next){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(next[0] == board.b.Beta[i][j][0] && next[1] == board.b.Beta[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

int isNextS(str next){
    int result = 0;
    int i, j;
    for(i=0; i<ROWS; i++){
        for(j=0; j<COLS; j++){
            if(next[0] == board.S[i][j][0] && next[1] == board.S[i][j][1]){
                result = 1;
                j = j+COLS;
                i = i+ROWS;
            }
        }
    }
    return result;
}

void NextPlayerMove(str prev, str next){
    int i, j, k=0;
    int a,b,c,d;
    a = prev[0];
    b = prev[1];
    c = next[0];
    d = next[1];

    if (board.aTurn && isPrevAlpha(prev)==1 && a==c+1 && (d==b || d==b+1 || b==d+1)){
        board.ok = !board.ok;
    }

    else if (!board.aTurn && isPrevBeta(prev)==1 && c==a+1 && (d==b || d==b+1 || b==d+1)){
        board.ok = !board.ok;
    }

    if (board.ok && board.aTurn && isNextFree(next) == 1){
        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.a.Alpha[i][j][0] == prev[0] && board.a.Alpha[i][j][1] == prev[1]){
                    board.a.Alpha[i][j][0] = '\0';
                    board.a.Alpha[i][j][1] = '\0';
                }
                if (i+49 == c && j+49 == d){
                    board.a.Alpha[i][j][0] = next[0];
                    board.a.Alpha[i][j][1] = next[1];
                }
            }
        }  
        board.aTurn = !board.aTurn;
        board.ok = !board.ok;
    }

    else if (board.ok && !board.aTurn && isNextFree(next) == 1){
        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.b.Beta[i][j][0] == prev[0] && board.b.Beta[i][j][1] == prev[1]){
                    board.b.Beta[i][j][0] = '\0';
                    board.b.Beta[i][j][1] = '\0';
                }
                if (i+49 == c && j+49 == d){
                    board.b.Beta[i][j][0] = next[0];
                    board.b.Beta[i][j][1] = next[1];
                }
            }
        }  
        board.aTurn = !board.aTurn;
        board.ok = !board.ok;
    }


    if (board.ok && board.aTurn && isNextBeta(next) == 1 && isNextS(next)==0){
        board.ok = !board.ok;
        printf("Invalid next position, please choose another piece or next move");
    }
    else if (board.ok && board.aTurn && isNextBeta(next) == 1 && isNextS(next)==1){
        printf("Player Alpha(E) eat Player Beta(Y)\n");
        board.b.pieces--;
        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.b.Beta[i][j][0] == next[0] && board.b.Beta[i][j][1] == next[1]){
                    board.b.Beta[i][j][0] = '\0';
                    board.b.Beta[i][j][1] = '\0';
                }
            }
        }  

        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.a.Alpha[i][j][0] == prev[0] && board.a.Alpha[i][j][1] == prev[1]){
                    board.a.Alpha[i][j][0] = '\0';
                    board.a.Alpha[i][j][1] = '\0';
                }

                if (i+49 == c && j+49 == d){
                    board.a.Alpha[i][j][0] = next[0];
                    board.a.Alpha[i][j][1] = next[1];
                }
            }
        }  
        board.aTurn = !board.aTurn;
        board.ok = !board.ok;
    }

    if (board.ok && !board.aTurn && isNextAlpha(next) == 1 && isNextS(next)==0){
        board.ok = !board.ok;
        printf("Invalid next position, please choose another piece or next move");
    }
    else if (board.ok && !board.aTurn && isNextAlpha(next) == 1 && isNextS(next)==1){
        printf("Player Beta(Y) eat Player Alpha(E)\n");
        board.a.pieces--;
        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.a.Alpha[i][j][0] == next[0] && board.a.Alpha[i][j][1] == next[1]){
                    board.a.Alpha[i][j][0] = '\0';
                    board.a.Alpha[i][j][1] = '\0';
                }
            }
        }  
        for (i=0; i<ROWS; i++){
            for (j=0; j<COLS; j++){
                if (board.b.Beta[i][j][0] == prev[0] && board.b.Beta[i][j][1] == prev[1]){
                    board.b.Beta[i][j][0] = '\0';
                    board.b.Beta[i][j][1] = '\0';
                }
                if (i+49 == c && j+49 == d){
                    board.b.Beta[i][j][0] = next[0];
                    board.b.Beta[i][j][1] = next[1];
                }
            }
        }  
        board.aTurn = !board.aTurn;
        board.ok = !board.ok;
    }
}


int gameOver2(){
    int i, j;
    int result;
    int A = board.a.pieces;
    int B = board.b.pieces;
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if ( ((i+1)%2 == (j+1)%2) && (i==0 || i==1)){
                if (board.a.Alpha[i][j][0] != '\0') //if space for beta is occupied by alpha
                    A--;
     
            }            
        }
    }
    for (i=0; i<ROWS; i++){
        for (j=0; j<COLS; j++){
            if ( ((i+1)%2 == (j+1)%2) && (i==5 || i==6)){
                if (board.b.Beta[i][j][0] != '\0') //if space for alpha is occupied by Beta
                    B--;
     
            }            
        }
    }
    if(A == 0) // if Alpha occupied all initialized Beta spaces
        result = 1;
    else if (B==0) // if Beta occupied all initialized Alpha spaces
        result = 2;

    return result;
}

int GameOver(){
    int i, j;
    int result=0;
    if (gameOver2() == 2 || board.a.pieces==0){
        printf("Beta Wins");
        result = 1;
    }
    else if (gameOver2() == 1 || board.b.pieces == 0){
        printf("Alpha Wins");
        result = 1;
    }
    return result;
}

int main(){
    str next;
    str prev = "\0";
    //int choice = 0; for exit choice

    initializeBoard();
    initializeValues();
    initializeBoardS();
    initializeAlphaBeta();

    FreeSpaces();
    displayBoard();
    while (GameOver()!=1 /*&& choice == 0*/){
        if (board.aTurn){
            printf("Player Alpha(E)\n");
            printf("Enter piece to move(format: 00): ");
            scanf(" %[^\n]s", board.prev);

            printf("Enter move: ");
            scanf(" %[^\n]s", next);
        }
        else if (!board.aTurn){
            printf("Player Beta(Y)\n");
            printf("Enter piece to move(format: 00): ");
            scanf(" %[^\n]s", board.prev);

            printf("Enter move: ");
            scanf(" %[^\n]s", next);
        }
        NextPlayerMove(board.prev, next);
        FreeSpaces();
        displayBoard();
    
        //printf("Exit? press 1: ");
        //scanf("%d", &choice);
    }

    return 0;
}
