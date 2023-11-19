#ifndef GAME_HPP
#define GAME_HPP
#include "player.hpp"

class game{
    private :
    vector<player> players;
    deck table = deck(0);//les cartes de la table
    deck d;//le paquet
    int size;//nombre de joueurs
    float pot;//somme sur la table

    // Affichage 

        string spacing() { return "                                       " ; }
        string minispacing() { return "                                  " ;}
        string printTopTable()    { return spacing() + "______________________________" ; }
        string printBottomTable() { return spacing() + "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾" ; }
        string printFold() { return "                  FOLD                 " ; }
        string emptyTable() { return "|                            |" ; }

        string printPot(int) ; 
        string printBet(int) ; 
        string printCheck(int) ; 
        string printRaise(int) ; 
        string printFollow(int) ; 
        string playerHand(int, int) ; 
        string playerStatus(int) ; 
        string cardOnTable() ; 

    public :
        game();//le jeu !
        void init();
        void printcredit();//affichage de fin
        void mise(int x, int b);//système de mise
        int checkmise(float m_min);
        void clearmise();
        void preflop();//main départ
        void flop();//le flop : 3 cartes sur la table
        void turn_river();//le turn et la river
        void manche(int x);//tour complet
        void clear();//nettoie pour la prochaine manche
        int combien();//nombre de joueur encore en jeu
        void plumer();//verifie si un joueur à plus d'argent
        void gagne(int i);//à modif
        void partie();
        void combinaison();
        void printTableInfos(int, int);
};

#endif