#include "Minesweeper.h"
#include "Gamerender.h"
#include<iostream>
#include<cmath>
#include <iomanip>
using namespace std;

void Gamerender::printreveal() const
{
    const int C1 = 4, C2 = 3;
    for (int r=0; r<game.getrow(); r++)
    {
        cout<<setw(C2)<<r<<"| ";
        for (int c=0; c<game.getcol(); c++)
        {
            cout << setw(C1)<< game.getreveal(r,c);
        }
        cout<<"|"<<endl;
    }
}

void Gamerender::print() const
{
    const int CELL = 4, C = 3;
    cout<<"   "<<0;
    for (int p=1; p<game.getcol(); p++)
    {
        cout <<setw(CELL) << p ;
    }
    cout<<endl<<"  ------------------------+"<<endl;
    for (int r=0; r<game.getrow(); r++)
    {
        cout<<r <<"| ";
        for (int c=0; c<game.getcol(); c++)
        {
            if (!game.reveal(r,c))
            {
                if(game.flag(r,c) == 1)
                {
                    if (c == 0) cout<<'F';
                    else cout<<setw(CELL) <<'F';
                }
                else
                {
                     if (c == 0) cout<<'#';
                    else cout<<setw(CELL) <<'#';
                }
            }
            else if(game.reveal(r,c)==1 && game.getboard(r,c) == 0)
            {
                    if (c == 0) cout<<' ';
                    else cout<<setw(CELL) <<' ';
            }
            else if(game.reveal(r,c) && game.getboard(r,c) == -1)
            {
                    if (c == 0) cout<<'F';
                    else cout<<setw(CELL) <<'*';
            }
            else if(game.getboard(r,c)!=-1 &&game.getreveal(r,c) == 1&&!game.flag(r,c))
            {
                    if (c == 0) cout<<game.getboard(r,c);
                    else cout<<setw(CELL) <<game.getboard(r,c);
            }
        }
        cout<<"|"<<endl;
    }


    /*for (int p=0; p<game.getrow(); p++)
    {
        cout <<setw(CELL) << p ;
    }
    cout<<endl<<"  ------------------------+"<<endl;
    for (int r=0; r<game.getrow(); r++)
    {
        cout<< setw(C) <<r <<'|';
        for (int c=0; c<game.getcol(); c++)
        {
            cout << setw(CELL) << game.getboard(r,c);
        }
        cout<<"|"<<endl;
    }*/
}

void Gamerender::printanswer() const
{
    cout <<endl<< "Now you can check your answer." <<endl;
    const int CELL = 4, C = 3;
    for (int p=0; p<game.getrow(); p++)
    {
        cout <<setw(CELL) << p ;
    }
    cout<<endl<<"  ------------------------+"<<endl;
    for (int r=0; r<game.getrow(); r++)
    {
        cout<< setw(C) <<r <<'|';
        for (int c=0; c<game.getcol(); c++)
        {
            if (game.getboard(r,c) == -1)
            {
                cout<<setw(CELL)<<"*";
            }
            else
            {
                cout<<setw(CELL)<<game.getboard(r,c);
            }
        }
        cout<<"|"<<endl;
    }
}
// 边距问题，无法取消插旗，可否连环作用
