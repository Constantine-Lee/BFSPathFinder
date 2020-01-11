// Include files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
// Definitions
#define BOARDSIZE 8
#define MINES_NUMBER 8
#define TRUE 1
#define FALSE 0
struct board {
    char board[100];
};
// Function prototypes



/*** To check whether the game win or not ***/
int check_win(int *total_arrivePtr, int *resultPtr,int total_step)
{
    if(*resultPtr)
        {
        /*** minus *total_arrivePtr by one if step on a city ***/
        *total_arrivePtr -=1;
        }
    else if(*total_arrivePtr == 0)
        {
        /*** Execute the statement to inform the user the game has complete and return TRUE ***/
         printf("Total %d steps has been taken =\n\n", total_step);
        printf("\nCongratulation, you have complete the game !!!\n");
        return TRUE;
        }
    /*** Execute the statement to inform the user the game has not yet complete and return FALSE ***/
    printf("Total %d steps has been taken(Total City left to be discovered = %d)\n\n", total_step, *total_arrivePtr);
    return FALSE ;
}

/*** To update the board according to user command ***/
void update_gboard(struct board ai_board[BOARDSIZE][BOARDSIZE],int rowPtr,int colPtr)
{
    int i, j;

    /*** print the column number ***/
    for(i = 0; i < BOARDSIZE; i++){printf(" %d\t",i);}printf("\n\n");

    /*** print the gameboard ***/
    for(i = 0; i < BOARDSIZE; i++)
        {
        for(j = 0; j < BOARDSIZE; j++)
            {
                if((i==rowPtr)&&(j==colPtr))
                    {
                    /*** convert all passed location to "." ***/
                    strcpy(ai_board[i][j].board,".");
                    /*** use | | to indicate the current position ***/
                    printf("|%s|\t", ai_board[i][j].board);
                    }
                else
                    {
                    /*** print the rest board ***/
                    printf(" %s\t",  ai_board[i][j].board);
                    }
            }printf("%d\n\n", i);
        }Sleep(1000);
}
/**********************************************
 * Now is the time for user interactive gameplay
 **********************************************/
void play(struct board ai_board[BOARDSIZE][BOARDSIZE], int total_step, int *total_arrivePtr, int *resultPtr)
{
     int j = 0 , rowPtr = 0,colPtr = 0, distance[20][20], store_col[100][100], store_row[100][100],check_row, check_col;
    /*** Ask the user to enter starting point ***/
    printf("Enter starting point:\n");
    printf("Enter row:");
        scanf("%d", &rowPtr);
    printf("Enter column:");
        scanf("%d", &colPtr);
    while(1)
    {
    j++;
    int temp_col = 100, temp_row = 100, min_distance = 70;
    for(int z = 0; z<20; z++)
    {
        for(int y = 0; y<20; y++)
        {
            distance[z][y] = 80;
        }
    }
    for(check_row = rowPtr + j; check_row>=(rowPtr-j); check_row--)
    {
        for(check_col = colPtr - j; check_col<=(colPtr+j); check_col++)
        {

            if(0<=check_row&&check_row<=7&&0<=check_col&&check_col<=7)
            {

                if((strcmp(ai_board[check_row][check_col].board, ".")==1))
                    {
                    distance[check_row][check_col] = abs(check_row-rowPtr)+abs(check_col-colPtr);
                    store_col[check_row][check_col] = check_col;
                    store_row[check_row][check_col] = check_row;
                    }
            }
        }
    }
    for(check_row = rowPtr + j; check_row>=(rowPtr-j); check_row--)
    {
        for(check_col = colPtr - j; check_col<=(colPtr+j); check_col++)
        {

            if(0<=check_row&&check_row<=7&&0<=check_col&&check_col<=7)
            {

            if(min_distance>distance[check_row][check_col])
            {
                min_distance = distance[check_row][check_col];
                temp_col = store_col[check_row][check_col];
                temp_row = store_row[check_row][check_col];
            }
            }

        }
    }
    if(min_distance<0)
        {break;}
    while(1)
    {
    if(temp_col!=100)
    {
        if((temp_col-colPtr)>0)
        {

            ++colPtr;
            update_gboard(ai_board,rowPtr,colPtr);
        }else if((temp_col-colPtr)<0)
        {

            --colPtr;
            update_gboard(ai_board,rowPtr,colPtr);
        }else if((temp_row-rowPtr)>0)
        {

            ++rowPtr;
            update_gboard(ai_board,rowPtr,colPtr);
        }else if((temp_row-rowPtr)<0)
        {

            --rowPtr;
            update_gboard(ai_board,rowPtr,colPtr);
        }
        else if((temp_col==colPtr)&&(temp_row==rowPtr))
        {

            j = 0;

            break;
        }
    }else
    {
        break;
    }
    }
    }
}
/**********************************************
 *Initialize the gameboard
 **********************************************/
void initialize_gboard(struct board ai_board[BOARDSIZE][BOARDSIZE])
{
    int i, j; char c[1];
/*** First let all the board element to be "." ***/
         for(i = 0; i < BOARDSIZE; i++)
            {
            for(j = 0; j < BOARDSIZE; j++)
                {
                strcpy(ai_board[i][j].board,".");
                }
            }
        // Seed srand() with time()
        srand(time(NULL));
 /*** Second, place random * in the board ***/
        for(j = 0, c[0] = 'A' ; j < MINES_NUMBER; j++, ++c[0])
            {
            int random = rand() % (BOARDSIZE);
            strcpy(ai_board[random][j].board, c);
            }
/*** Third, print the column numbers. ***/
        for(i = 0; i < BOARDSIZE; i++)
            {
            printf(" %d\t",i);
            }printf("\n\n");
/*** Fourth, print the actual board with row number ***/
        for(i = 0; i < BOARDSIZE; i++)
            {
            for(j = 0; j < BOARDSIZE; j++)
                {
                printf(" %s\t",  ai_board[i][j].board);
                }printf("%d\n\n", i);
            }
}

/*** Start the game after welcome message ***/
 int start_game()
 {
    struct board ai_board[BOARDSIZE][BOARDSIZE];
    int total_step = 0, total_arrive = 8, result = 0;
/*** call initialize_gboard ***/
    initialize_gboard(ai_board);
/*** call play ***/
    play(ai_board, total_step,&total_arrive, &result);
    return 0;
}

/**********************************************
 * Main function. Handles gameplay.
 **********************************************/
int main()
{
    start_game();
    return 0;
}
