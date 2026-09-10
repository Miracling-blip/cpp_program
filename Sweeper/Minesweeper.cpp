#include<iostream>
#include "Minesweeper.h"
using namespace std;


Minesweeper::Minesweeper(int Rows, int Cols, int Mines):
    rows(Rows), cols(Cols), mines(Mines) //初始化构造
{
    for (int r=0; r<rows; r++)
    {
        for(int c=0; c<cols; c++)
        {
            revealed[r][c] = 0;
            board[r][c] = 0;
            flagged[r][c] = 0;
        }
    }
}

void Minesweeper::process(int Rows, int Cols, char OP)
{
    if(OP == 'f' || OP == 'F')
    {
        flagged[Rows][Cols] = 1;
        return;
    }
    else if(OP == 'c' || OP == 'C')
    {
        if(flagged[Rows][Cols] == 0)
        {
            cout << "illegal statics";
            return;
        }
        else
        {
            flagged[Rows][Cols] = 0;
        }
    }
    else if (board[Rows][Cols] == -1)
    {
        if (OP == 't' || OP == 'T')
        {
            isover = true;
            revealed[Rows][Cols] = 1;
            return;
        }
    }
    else
    {
        revealed[Rows][Cols] = 1;
        if (board[Rows][Cols] == 0)
        {
            expand(Rows, Cols);
        }
    }
}

void Minesweeper::expand(int row, int col)
{
    int direction1[3] = {-1, 0, 1}, direction2[3] = {-1, 0, 1};
    for (int i = 0; i<3 ;i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (direction1[i] + row < 0 || direction2[j] + col < 0)
            {
                continue;
            }
            else if (direction1[i] + row >= rows||direction2[j] + col >=cols)
            {
                continue;
            }
            else if (direction1[i] == 0&&direction2[j] == 0)
            {
                continue;
            }
            else
            {
                if (board[direction1[i] + row][direction2[j] + col] != -1&&revealed[direction1[i] + row][direction2[j] + col] == 0&&flagged[direction1[i] + row][direction2[j]+col]==0)
                {
                    revealed[direction1[i] + row][direction2[j] + col] = 1;
                    if(board[direction1[i] + row][direction2[j] + col] == 0)
                    {
                        expand(direction1[i] + row, direction2[j] + col);
                    }
                }
            }
        }
    }
}

bool Minesweeper::check(int Rows, int Cols, char OP, int jimmy)  // 检测输入的坐标是否合法
{
    if(Rows>rows-1 || Cols>cols-1)
    {
        return false;
    }
    else if(revealed[Rows][Cols] == 1)
    {
        return false;
    }
    else if(OP != 'f' && OP != 'F' && OP != 't' && OP != 'T' && OP != 'c' && OP != 'C')
    {
        return false;
    }
    else if (OP == 'c'||OP == 'C')
    {
        if (flagged[Rows][Cols] == 1)
        {
            return true;
        }
        else return false;
    }
    else
    {
        return true;
    }
}

void Minesweeper::setmines(int Nrow, int Ncol)
{
    int placed = 0;
    if (isplace)
    {
        return;
    }
    while(placed < mines)
    {
        int r = rand() % rows;
        int c = rand() % cols;
        if (r == Nrow && c == Ncol)
        {
            continue;
        }
        else if(board[r][c] == -1)
        {
            continue;
        }
        else if(abs(Nrow-r)<=1&&abs(Ncol-c)<=1) continue;
        else
        {
            board[r][c] = -1;
            placed++;
        }
    }
    isplace = true;
}

void Minesweeper::caculation(int Rows, int Cols)
{
    int direction1[3] = {-1, 0, 1}, direction2[3] = {-1, 0, 1}, m = 0;
    for (int i = 0; i<3 ;i++)
    {
        for (int j = 0; j<3; j++)
        {
            if (direction1[i] + Rows < 0 || direction2[j] + Cols < 0)
            {
                continue;
            }
            else if(direction1[i] + Rows>=rows||direction2[j] + Cols>=cols)
            {
                continue;
            }
            else
            {
                if (board[direction1[i] + Rows][direction2[j] + Cols] == -1)
                {
                    m++;
                }
            }
        }
    }
    board[Rows][Cols] = m;
}

void Minesweeper::checkv()
{
    bool bj = 0;
    for (int i = 0; i<rows; i++)
    {
        for (int j = 0; j<cols; j++)
        {
            if (revealed[i][j] == 0&&board[i][j] != -1)
            {
                bj = 1;
            }
        }
    }
    if (bj == 0)
    {
        isvector = true;
    }
    return;
}
