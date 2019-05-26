#include "ai.h"

int ai::evaluate(int* b)
{

    for (int row = 0; row<3; row++)
    {
        if (b[row*3+0]==b[row*3+1] &&
            b[row*3+1]==b[row*3+2])
        {
            if (b[row*3]==1)
                return +10;
            else if (b[row*3]==-1)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (b[col]==b[col+3] &&
            b[col+3]==b[col+6])
        {
            if (b[col]==1)
                return +10;

            else if (b[col]==-1)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (b[0]==b[4] && b[4]==b[8])
    {
        if (b[0]==1)
            return +10;
        else if (b[0]==-1)
            return -10;
    }

    if (b[2]==b[4] && b[4]==b[6])
    {
        if (b[2]==1)
            return +10;
        else if (b[2]==-1)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int ai::minmax(int* board, int depth, bool max){
    int best=0;

    int score = evaluate(board);
    if(score == 10) return score;
    if(score == -10) return score;
    int result=0;
    int tmp;
    if(max){
        best = -100;
        for(int row =0;row<3;++row){
            for(int column=0;column<3;++column){
                if(board[row*3+column] == 0){
                    board[row*3+column]=1;

                    tmp = minmax(board,depth+1,!max);
                    if(tmp>best){
                        best = tmp;
                        if(depth==0){
                            result = row*3+column;
                        }
                    }
                    board[row*3+column]=0;
                }
            }
        }
        if(best==-100)best =0;//draw
    } else {
        best = 100;
        for(int row =0;row<3;++row){
            for(int column=0;column<3;++column){
                if(board[row*3+column] == 0){
                    board[row*3+column]=-1;
                    tmp = minmax(board,depth+1,!max);
                    if(tmp<best){
                        best = tmp;
                        if(depth==0){
                            result = row*3+column;
                        }
                    }
                    board[row*3+column]=0;
                }
            }
        }
        if(best==100)best =0;//draw
    }
    if(depth==0){
        best = result;
    }

    return best;
}
