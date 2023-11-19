#ifndef PLAYER_HPP
#define PLAYER_HPP
#include "deck.hpp"

class player{
    private :
    float credit;
    float mise;//mise
    float misetotale;//mise totale d'une manche
    int p;//0 ou 1 si encore dans partie
    int m;//0 ou 1 si encore dans manche
    int status = -2 ; // -2 = WAIT ; -1 = BIND ;  0 = FOLD ; 1 = CHECK ; 2 = RAISE ; 3 = BET ; 4 = FOLLOW
    deck main = deck(0);//vide

    public :
    player(float c);
    // int val();//valeur de sa main
    void newc(deck &d);//nouvelle carte
    void again();//continuer à jouer ?

    //gérer les attributs privés
    float getCredit();
    float getMise();
    float getMiseT();
    int getMiseTInt() ; 
    int getMiseInt() ; 
    int getP();
    int getM();
    void setP(int p);
    void setM(int m);
    void setCredit(float c);
    void setMise(float m);
    void setMiseT(float mt);
    deck getMain();
    string playerHand(int) ; 
    int getStatus() const ; 
    void setStatus(int) ; 
    void clearMain();
    void sortMain();
};

#endif