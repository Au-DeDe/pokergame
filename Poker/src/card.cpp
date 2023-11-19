#include "card.hpp"

using namespace std;

card::card(int v, int c){
    value = v;
    color = c;
}

void card::print(){
   const char *symbols[4] = {"♥", "♦", "♣", "♠"} ; 
    string c_name[13] = {"2","3","4","5","6","7","8","9","T","J","Q","K","A"} ;
    cout << c_name[value-1] << "[" << symbols[color] << "] " ;
}

string card::strPrint(){
    const char *symbols[4] = {"♥", "♦", "♣", "♠"} ; 
    string c_name[13] = {"2","3","4","5","6","7","8","9","T","J","Q","K","A"} ;
    string s = c_name[value-1] + "[" + symbols[color] + "] " ;
    return s ; 
}

int card::getValue(){
    return value;
}

int card::getColor(){
    return color;
}