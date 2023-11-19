#ifndef CARD_HPP
#define CARD_HPP
#include <iostream>
#include <iomanip>
#include <vector>
#include <time.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std ; 

class card{
    private :
    int value; //1 à 13
    int color; //1 à 4

    public :
    card(int v, int c);
    void print();
    string strPrint() ; 
    int getValue();
    int getColor();
};

#endif