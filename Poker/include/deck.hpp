#ifndef DECK_HPP
#define DECK_HPP
#include "card.hpp"

struct eval{
    int type;
    int hauteursuite;
    int couleur;
    int carre;
    int brelan;
    int paire1;
    int paire2;
    int hauteur;
};

class deck : public vector<card>{
    public :
    deck();
    deck(int a);//vide
    void print();
    void tri();//melange
    string strPrint();

    //combinaison
    bool QuinteFlush(struct eval * e);
    bool Carre(struct eval * e);
    bool Full(struct eval * e);
    bool Couleur(struct eval * e);
    bool Quinte(struct eval * e);
    bool Brelan(struct eval * e);
    bool DoublePaire(struct eval * e);
    bool Paire(struct eval * e);
    bool Hauteur(struct eval * e);
};

#endif