#include "player.hpp"

float player::getCredit(){
    return (*this).credit;
}

float player::getMise(){
    return (*this).mise;
}

int player::getMiseTInt(){
    return (*this).misetotale ; 
}

int player::getMiseInt(){
    return (*this).mise ; 
}

float player::getMiseT(){
    return (*this).misetotale;
}

int player::getP(){
    return (*this).p;
}

int player::getM(){
    return (*this).m;
}

void player::setCredit(float c){
    (*this).credit = c;
}

void player::setMise(float m){
    (*this).mise = m;
}

void player::setMiseT(float m){
    (*this).misetotale = m;
}

void player::setP(int p){
    (*this).p = p;
}

void player::setM(int m){
    (*this).m = m;
}

deck player::getMain(){
    return (*this).main;
}

string player::playerHand(int id){
    string s = "          Player " + to_string(id+1) + " : " + main.strPrint() + "        " ; 
    return s ; 
}

int player::getStatus() const {
    return status ; 
}

void player::setStatus(int s) {
    status = s ; 
}

void player::clearMain(){
    ((*this).main).clear();
}

player::player(float c){
    credit = c;
    mise = 0;
    misetotale = 0;
    p = 1;
    m = 1;
}

void player::newc(deck &d){
    ((*this).main).push_back(d[0]);
    d.erase(d.begin());
}

void player::again(){
    if((*this).credit<10){//fauché
        (*this).p = 0;
        cout << " vous n'avez plus assez de credit :(" << endl;
    }
    else{
        char c;
        while(c != 'y' && c != 'n'){
            cout << " il vous reste " << (*this).credit << " credit.\nVoulez vous continuer ? (y/n) : ";
            cin >> c;
            if(c == 'y'){
                (*this).m = 1;
            }
            if(c == 'n')
                (*this).p = 0;
        }
    }
}

void player::sortMain(){
}