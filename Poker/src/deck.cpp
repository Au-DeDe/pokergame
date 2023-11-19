#include "deck.hpp"

deck::deck(){
    for(int j=0; j<4; j++){
        for(int k=1; k<14; k++)
            (*this).push_back({k,j});
    }
}

deck::deck(int a){
    //rien, un deck vide
}

void deck::print(){
    for(card i : *this)
        i.print();
}

void deck::tri(){
    deck tri(0);
    int t = (*this).size();
    for(int i=0; i<t; i++){
        int c = rand()%(t-i);
        tri.push_back((*this)[c]);
        (*this).erase((*this).begin()+c);
    }
    (*this) = tri;
}

string deck::strPrint(){
    string s = "" ;  
    for(card i : *this)
        s+= i.strPrint();
    return s ; 
}

bool deck::QuinteFlush(struct eval * e){//A MODIF
     int vq;
    //int rec;//a ajouter si ya une paire->.
    for(int j=0; j<3; j++){
        vq = 0;
        for(int i=0; i<4; i++){
            if((*this)[j+i].getValue() == (*this)[j+i+1].getValue()+1 && (*this)[j+i].getColor() == (*this)[j+i+1].getColor())
                vq++;
            else
                break;
        }
        if(vq==4){
            e->type = 8;
            e->hauteursuite = (*this)[j].getValue();
            return true;
        }
    }
    if((*this)[0].getValue()==13){//cas special A2345
        if((*this)[6].getValue() == 1 && (*this)[5].getValue() == 2 && (*this)[4].getValue() == 3 && (*this)[3].getValue() == 4){
            if((*this)[6].getColor() == (*this)[5].getColor() && (*this)[5].getColor() == (*this)[4].getColor() && (*this)[4].getValue() == (*this)[3].getColor() && (*this)[3].getColor() == (*this)[0].getColor()){
                e->type = 8;
                e->hauteursuite = 4;
                return true;
            }
        }
    }
    return false;
}

bool deck::Carre(struct eval * e){
    for(int j=0; j<4; j++){
        if((*this)[j].getValue()==(*this)[j+1].getValue() && (*this)[j+1].getValue()==(*this)[j+2].getValue() && (*this)[j+2].getValue()==(*this)[j+3].getValue()){
            e->type = 7;
            e->carre = (*this)[j].getValue();
            return true;
        }
    }
    return false;
}

bool deck::Full(struct eval * e){
    for(int j=0; j<5; j++){
        if((*this)[j].getValue()==(*this)[j+1].getValue() && (*this)[j+1].getValue()==(*this)[j+2].getValue()){
            for(int k=0; k<6; k++){
                if((*this)[j].getValue()!=(*this)[k].getValue() && (*this)[k].getValue()==(*this)[k+1].getValue()){
                    e->type = 6;
                    e->brelan = (*this)[j].getValue();
                    e->paire1 = (*this)[k].getValue();
                    return true;
                }
            }
        }
    }
    return false;
}

bool deck::Couleur(struct eval * e){
    int vc;
    for(int k=0; k<4; k++){
        vc = 0;
        for(int j=0; j<7; j++){
            if((*this)[j].getColor()==k){
                vc++;
                if(vc>=5){
                    e->type = 5;
                    e->couleur = k;
                    return true;
                }
            }
        }
    }
    return false;
}

bool deck::Quinte(struct eval * e){//A MODIF
    int vq;
    //int rec;//a ajouter si ya une paire->.
    for(int j=0; j<3; j++){
        vq = 0;
        for(int i=0; i<4; i++){
            if((*this)[j+i].getValue() == (*this)[j+i+1].getValue()+1)
                vq++;
            else
                break;
        }
        if(vq==4){
            e->type = 4;
            e->hauteursuite = (*this)[j].getValue();
            return true;
        }
    }
    if((*this)[0].getValue()==13){//cas special A2345
        if((*this)[6].getValue() == 1 && (*this)[5].getValue() == 2 && (*this)[4].getValue() == 3 && (*this)[3].getValue() == 4){
            e->type = 4;
            e->hauteursuite = 4;
            return true;
        }
    }
    return false;
}

bool deck::Brelan(struct eval * e){
    for(int j=0; j<5; j++){
        if((*this)[j].getValue()==(*this)[j+1].getValue() && (*this)[j+1].getValue()==(*this)[j+2].getValue()){
            e->type = 3;
            e->brelan = (*this)[j].getValue();
            return true;
        }
    }
    return false;
}

bool deck::DoublePaire(struct eval * e){
    for(int j=0; j<6; j++){
        if((*this)[j].getValue()==(*this)[j+1].getValue()){
            for(int k=0; k<6; k++){
                if((*this)[j].getValue()!=(*this)[k].getValue() && (*this)[k].getValue()==(*this)[k+1].getValue()){
                    e->type = 2;
                    e->paire1 = (*this)[j].getValue();
                    e->paire2 = (*this)[j=k].getValue();
                    return true;
                }
            }
        }
    }
    return false;
}

bool deck::Paire(struct eval * e){
    for(int j=0; j<6; j++){
        if((*this)[j].getValue()==(*this)[j+1].getValue()){
            e->type = 1;
            e->paire1 = (*this)[j].getValue();
            return true;
        }
    }
    return false;
}

bool deck::Hauteur(struct eval * e){
    e->type = 0;
    e->hauteur = (*this)[0].getValue();
    return true;
}