#pragma once
#include<iostream>
using namespace std;

class Minesweeper
{
public:
    void print() const;
    Minesweeper(int Rows, int Cols, int Mines);
    void process(int Rows, int Cols, char OP);
    void expand(int row, int col);
    bool check(int Rows, int Cols, char OP, int jimmy);
    void setmines(int Nrow, int Ncol);
    void caculation(int Rows, int Cols);
    void checkv();
    bool detectvector();

    int getrow() const
    {
        return rows;
    }
    int getcol() const
    {
        return cols;
    }
    bool reveal(int rs, int cs) const
    {
        if (revealed[rs][cs] == 0) return 0;
        else return 1;
    }
    int getboard(int rs, int cs) const
    {
        return board[rs][cs];
    }
    bool flag(int Rows,int Cols) const
    {
        return flagged[Rows][Cols];
    }
    bool getvector()
    {
        return isvector;
    }
    bool getover()
    {
        return isover;
    }
    int getreveal(int r1,int c1) const
    {
        return revealed[r1][c1];
    }
private:
    int board[30][30], h[3] = {1,-1,0};
    bool revealed[30][30], flagged[30][30];
    int rows, cols, mines;
    bool isvector = false, isover = false, isplace = false;
};
