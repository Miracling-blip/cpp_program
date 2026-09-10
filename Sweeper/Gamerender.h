#pragma once
#include "Minesweeper.h"
#include<iostream>
using namespace std;

class Gamerender
{
public:
    void print() const;
    void printreveal() const;
    void printanswer() const;
    bool check;
    Gamerender(const Minesweeper& g) :game(g)
    {
        // 这里的g是构造函数的形式参数，实际应该是主函数中传过来的mycore
    }
private:
    const Minesweeper& game;
};
