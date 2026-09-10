#include<iostream>
#include "Gamerender.h"
#include "Minesweeper.h"
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
    cout<<"Welcome To The Minesweeper!"<<endl<<"The rules are as follows:
        "<<endl;
    cout<<"When required to 'type in your operation',you have to type two number and an character."<<endl;
    cout<<"The two number represent the point you want to operate."<<endl<<"As for the character,'T/t'represent 'dig','F/f'represent 'set flag'.while 'C/c'represent 'cancel the flag'"<<endl;
    cout<<endl<<"May you have a good time!"<<endl<<endl;
    srand((unsigned int)time(0));

    int row(0), col(0), mine(0);
    bool bg = 0, firstflag = 0;
    cout<<"Please type in the rows,cols and the number of the mines:";
    while(bg == 0)
    {
        cin >> row >> col >>mine;
        if (row <= 3 || col <= 3)
        {
            cout << "Please type in a bigger place!"<<endl;
        }
        else if (mine >= row * col)
        {
            cout<< "Too more mines!"<<endl;
        }
        else
        {
            bg = 1;
        }
    }

    Minesweeper mycore(row, col, mine);
    Gamerender render(mycore);
    render.print();

    int il = 0, jl=0;
    while(!mycore.getover() && !mycore.getvector())
    {
        cout << "Please type in your operation:" << endl;
        int nrow(0), ncol(0);
        char op;
        cin>>nrow>>ncol>>op;
        cout << endl;

        if (op == 't'||op == 'T')
        {
            il++;
        }
        if (il == 1)
        {
            mycore.setmines(nrow, ncol);
        }

        if(op == 't'||op == 'T')
        {
            jl++;
        }
        if (!mycore.check(nrow, ncol, op, jl))
        {
            cout<<"illegal statics!"<<endl;
            continue;
        }
        else
        {
            if(jl == 1)
            {
                for (int w=0; w<row; w++)
                {
                    for (int e=0; e<col; e++)
                    {
                        if(mycore.getboard(w, e) == 0)
                        {
                            mycore.caculation(w, e);
                        }
                    }
                }
            }
            mycore.process(nrow, ncol, op);
            mycore.checkv();
        }
        if (mycore.getover())
        {
            cout << endl<<"BOMB.How pity!"<<endl;
            render.printanswer();
            exit(0);
        }
        else if(mycore.getvector() == true)
        {
            cout<<endl<<"Congratulations!You win!"<<endl;
            render.print();
            exit(0);
        }

        render.print();
        //exit(0);
    }
    return 0;
}
