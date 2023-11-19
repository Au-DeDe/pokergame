#include "game.hpp"

#include <stdexcept>
#include <limits>

void clear_ignore(){
    std::cin.clear(); //clear bad input flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
}

game::game(){
}

void game::init(){
    int c = 1000;//credit arbitraire
    pot = 0;
    int nb = 0 ;
    
    while((std::cout << "Entrez le nombre de joueurs (2 à 6) : ") && (!(std::cin >> nb) || (nb < 2) || (nb > 6))){
        std::cin.clear(); //clear bad input flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
        std::cout << "Invalid input; please re-enter.\n";
    }
    std::cin.clear(); //clear bad input flag
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input

    // Permet de vider le tampon entièrement. 
    for(int i=0; i<nb; i++){
        player p(c);
        players.push_back(p);
    }
    size = nb;

    cout << "Initializing..." <<  endl;
    sleep(1) ; 
    cout << "..." << endl ; 
}

void game::printcredit(){
    for(int i=0; i<size; i++)
        if(players[i].getP() == 1)
            cout << "Joueur "<< i+1 << " : " << players[i].getCredit() << " credits" << endl;
    cout << endl;
}

void game::preflop(){
    //2 cartes par joueur puis affichage
    for(int i=0; i<size; i++){
        if(players[i].getP() == 1){
            for(int j=0; j<2; j++)
                players[i].newc(d);
            //cout << "Joueur " << i+1 << " : ";
            //(players[i].getMain()).print();
            //cout << endl;
        }
    }
    cout << endl;
}

void game::flop(){
    for(int i=0; i<3; i++){
        table.push_back(d[0]);
        d.erase(d.begin());
    }
    cout << endl;
    cout << endl;
}

void game::turn_river(){
    table.push_back(d[0]);
    d.erase(d.begin());
    cout << endl;
    cout << endl;
}

int game::checkmise(float m_min){
   int vm = 0;
   int vc = 0;
   for(int i=0; i<size; i++){
        if(players[i].getMise() == m_min || players[i].getM()==0 || players[i].getCredit()==0)
            vm++;
         if(players[i].getMise() == -1 || players[i].getM()==0)//A regler
            vc++;
   }
   if(vm==size || vc==size)
        return 1;
    else
        return 0;
}

void game::clearmise(){
    for(int i=0; i<size; i++){
        if(players[i].getMise() > 0)
            players[i].setMiseT(players[i].getMiseT() + players[i].getMise());
        players[i].setMise(0);
    }
}

void game::mise(int x, int b){
    float m_min = 20;//mise minimale
    float m;//mise
    char c;//choix
    int vc = 0;//verifcheck
    int v1 ; // Verif while
    int vm = 0;//verifmise
    int i = x;//compteur
    int j;//indice joueur
    j = i%size ; 
    while(vm==0){
        j = i%size;
        if(players[j].getM() == 1){
            if(players[j].getCredit() == 0)
                cout << "Joueur " << j+1 << " est tapis" << endl;
            else if(b == 2){
                b--;
                vc = 1;
                pot += 10;
                players[j].setMise(10);
                players[j].setCredit(players[j].getCredit() - 10);
                //cout << "Joueur " << j+1 << " paie la Small Blind : 10 $" << endl;
                players[j].setStatus(-1) ; 
                //cout << endl;
            }
            else if(b == 1){
                b--;
                pot += 20;
                players[j].setMise(20);
                players[j].setCredit(players[j].getCredit() - 20);
                //cout << "Joueur " << j+1 << " paie la Big Blind : 20 $" << endl;
                players[j].setStatus(-1) ; 
                //cout << endl;
                
            }
            else{
                c = 0;
                v1 = 0;
                sleep(1);
                printf("\033[2J\033[H");
                cout << "Credit du Joueur " << j+1 << " : " << players[j].getCredit() << endl ;  
                printTableInfos(players.size(),j+1) ; 
                while(v1==0){
                    if(vc==0){
                        while ((cout << "Joueur " << j+1 << " choisissez une action :\n(B)    Bet.     \n(C)    Check.  \n(F)    Fold. \nChoix :  ") && (!(cin >> c) || (c != 'B' && c != 'C' && c != 'F'))) {
                                clear_ignore() ; 
                                cout << "Invalid input; please re-enter.\n";
                        }
                        clear_ignore() ;
                        if(c=='B'){ // BET.
                            vc = 1;
                            m = 0;
                            while((cout << "Votre mise doit être comprise entre " << m_min << " et " << players[j].getCredit() << ".\nMise : ") && (!(cin >> m) || (m < m_min) || (m > players[j].getCredit()))){
                                    clear_ignore() ; 
                                    cout << "Invalid input; please re-enter.\n";
                            }
                            clear_ignore() ; 
                            pot += m;
                            players[j].setMise(m);
                            players[j].setCredit(players[j].getCredit() - m);
                            m_min = m;
                            cout << "Le joueur " << j+1 << " mise " << m << " crédits." << endl;
                            players[j].setStatus(3) ; 
                            cout << endl;
                            v1 = 1;
                        }
                        else if ( c == 'C'){ // Check. 
                        players[j].setMise(-1);
                        cout << "Le joueur " << j+1 << " check." << endl;
                        players[j].setStatus(1) ; 
                        cout << endl;
                            v1 = 1;              
                    }
                        else { // Fold. 
                            players[j].setM(0);
                            cout << "Le joueur " << j+1 << " se couche." << endl;
                            players[j].setStatus(0) ; 
                            cout << endl;
                        v1 = 1;
                        }
                    }
                    else{
                        while ((cout << "Joueur " << j+1 << " choississez une action : \n(R)    Renchérir. \n(S)    Suivre. \n(F)    Fold. \nChoix :  ") && (!(cin >> c) || (c != 'R' && c != 'S' && c != 'F'))) {
                            clear_ignore() ; 
                            cout << "Invalid input; please re-enter.\n";
                        }
                        clear_ignore() ;
                        if(c=='R'){ // RENCHERIR.
                            m = 0;
                            if(players[j].getMise() == -1)
                                players[j].setMise(0);
                            while((cout << "Votre mise doit être comprise entre " << m_min << " et " << players[j].getCredit() << ".\nMise : ")
                            && (!(cin >> m) || (m < m_min) || (m > players[j].getCredit()))){
                                clear_ignore() ; 
                                cout << "Invalid input; please re-enter.\n";
                            }
                            clear_ignore() ; 
                            pot += m;
                            players[j].setMise(players[j].getMise() + m);
                            players[j].setCredit(players[j].getCredit() - m);
                            m_min = players[j].getMise();
                            cout << "Le joueur " << j+1 << " renchérit de " << m << " crédits." << endl;
                            players[j].setStatus(2) ; 
                            cout << endl;
                            v1 = 1;
                        }

                        else if ( c == 'S'){ // Suivre. 
                        if(players[j].getMise() == -1)
                                players[j].setMise(0);
                        if(players[j].getCredit() - (m_min - players[j].getMise()) < 0){
                            pot += players[j].getCredit();
                            cout << "Le joueur " << j+1 << " suit en tapie." << endl;
                            cout << endl;
                            players[j].setMise(players[j].getMise() + players[j].getCredit());
                            players[j].setCredit(0);
                        }
                        else{
                            pot += m_min - players[j].getMise();
                            players[j].setCredit(players[j].getCredit() - (m_min - players[j].getMise()));
                            cout << "Le joueur " << j+1 << " suit." << endl;
                            cout << endl;
                            players[j].setMise(m_min);
                        }
                        players[j].setStatus(4);
                            cout << endl;   
                                v1 = 1;
                            }
                        else { // Fold. 
                        players[j].setM(0);
                        cout << "Le joueur " << j+1 << " se couche." << endl;
                        players[j].setStatus(0) ; 
                        cout << endl;
                            v1 = 1;
                    }
                    }
                }
            }
        }
        vm = checkmise(m_min);
        if(combien()!=8)
            vm = 1;
        i++;
    }
    clearmise();
}

void game::manche(int x){
    plumer();
    d = deck();
    d.tri();
    preflop();
    mise(x, 2);
    if(combien()==8){
        flop();
        mise(x, 0);
        if(combien()==8){
            turn_river();
            mise(x, 0);
            if(combien()==8){
                turn_river();
                mise(x, 0);
                if(combien()==8){
                    combinaison();
                }
                else
                    gagne(combien());
            }
            else
                gagne(combien());
        }
        else
            gagne(combien());
    }
    else
        gagne(combien());

    // Affichage debug
    // cout << "Pot : " << pot << endl;
    // for(int i=0; i<size; i++){
    //     if(players[i].getP() == 1)
    //         cout << "Joueur " << i+1 << ": " << players[i].getMiseT() << endl;
    // }
    
    for(int i=0; i<size; i++)
        if(players[i].getP() == 1)
            players[i].setM(1);
    clear();
}

void game::plumer(){
    for(int i=0; i<size; i++){
        if(players[i].getCredit() < 20 && players[i].getP()==1){
            cout << "Le joueur " << i+1 << " n'a pas assez pour continuer" << endl;
            players[i].setP(0);
            players[i].setM(0);
            players[i].setStatus(-10) ; 
        }
    }
}

void game::combinaison(){
    struct eval combi_eval[size];
    vector<deck> combi;
    for(int i=0; i<size; i++){
        combi_eval[i].type = -1;
        deck d = deck(0);
        if(players[i].getP()==1){
            d = players[i].getMain();
            for(int j=0; j<5; j++)
                d.push_back(table[j]);
            sort(d.begin(), d.end(), [](card a, card b) {return a.getValue() > b.getValue();});
        }
        combi.push_back(d);
    }

    int g = 0;//gagnant
    int v;
    for(int i=0; i<size; i++){
        v=0;
        if(players[i].getM()==1){
            if(v==0){
                if(combi[i].QuinteFlush(&combi_eval[i])){
                    // cout << "quinte flush" << combi_eval[i].hauteursuite << combi_eval[i].couleur << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].Carre(&combi_eval[i])){
                    // cout << "carre" << combi_eval[i].carre << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].Full(&combi_eval[i])){
                    // cout << "Full" << combi_eval[i].brelan << combi_eval[i].paire1 << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].Couleur(&combi_eval[i])){
                    // cout << "couleur : '" << combi_eval[i].couleur << "'" << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].Quinte(&combi_eval[i])){
                    // cout << "quinte" << combi_eval[i].hauteursuite << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].Brelan(&combi_eval[i])){
                    // cout << "brelan" << combi_eval[i].brelan << endl;
                    v = 1;
                }
            }

            if(v==0){
                if(combi[i].DoublePaire(&combi_eval[i])){
                    // cout << "double paire" << combi_eval[i].paire1 << combi_eval[i].paire2 << endl;
                    v = 1;
                }
            }
            
            if(v==0){
                if(combi[i].Paire(&combi_eval[i])){
                    // cout << "paire" << combi_eval[i].paire1 << endl;
                    v = 1;
                }
            }

            if(v==0){
                deck d = players[i].getMain();
                sort(d.begin(), d.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                if(d.Hauteur(&combi_eval[i])){
                    // cout << "hauteur" << combi_eval[i].hauteur << endl;
                    v = 1;
                }
            }

            // combi[i].print();
            // cout << end;
        }
    }
    for(int j=1; j<size; j++){
        if(combi_eval[j].type > combi_eval[g].type)
            g = j;
        else if(combi_eval[j].type == combi_eval[g].type){
            if(combi_eval[j].type == 0){
                if(combi_eval[j].hauteur > combi_eval[g].hauteur)
                    g = j;
            }
            else if(combi_eval[j].type == 1){
                if(combi_eval[j].paire1 > combi_eval[g].paire1)
                    g = j;
                else if(combi_eval[j].paire1 == combi_eval[g].paire1){
                    int zj, zg;
                    int hj = combi_eval[j].paire1;
                    int hg = combi_eval[g].paire1;
                    deck dj = players[j].getMain();
                    deck dg = players[g].getMain();
                    sort(dj.begin(), dj.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    sort(dg.begin(), dg.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    zj = 0;
                    zg = 0;
                    while(hj == combi_eval[j].paire1 && zj < 3){
                        if(dj[zj].getValue()!=hj){
                            hj = dj[zj].getValue();
                        }
                        else
                            zj++;
                        if(zj == 3)
                            hj = 0;
                    }
                    while(hg == combi_eval[g].paire1 && zg < 3){
                        if(dj[zg].getValue()!=hj){
                            hg = dg[zg].getValue();
                        }
                        else
                            zg++;
                        if(zg == 3)
                            hg = 0;
                    }
                    if(hj > hg)
                        g = j;
                }
            }
            else if(combi_eval[j].type == 2){
                if(combi_eval[j].paire1 > combi_eval[g].paire1)
                    g = j;
                else if(combi_eval[j].paire1 == combi_eval[g].paire1){
                    if(combi_eval[j].paire2 > combi_eval[g].paire2)
                        g = j;
                }
            }
            else if(combi_eval[j].type == 3){
                if(combi_eval[j].brelan > combi_eval[g].brelan)
                    g = j;
                else if(combi_eval[j].brelan == combi_eval[g].brelan){
                    int zj, zg;
                    int hj = combi_eval[j].brelan;
                    int hg = combi_eval[g].brelan;
                    deck dj = players[j].getMain();
                    deck dg = players[g].getMain();
                    sort(dj.begin(), dj.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    sort(dg.begin(), dg.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    zj = 0;
                    zg = 0;
                    while(hj == combi_eval[j].brelan && zj < 3){
                        if(dj[zj].getValue()!=hj){
                            hj = dj[zj].getValue();
                        }
                        else
                            zj++;
                        if(zj == 3)
                            hj = 0;
                    }
                    while(hg == combi_eval[g].brelan && zg < 3){
                        if(dj[zg].getValue()!=hj){
                            hg = dg[zg].getValue();
                        }
                        else
                            zg++;
                        if(zg == 3)
                            hg = 0;
                    }
                    if(hj > hg)
                        g = j;
                }
            }
            else if(combi_eval[j].type == 4){
                if(combi_eval[j].hauteursuite > combi_eval[g].hauteursuite)
                    g = j;
            }
            else if(combi_eval[j].type == 5){
                ;
            }
            else if(combi_eval[j].type == 6){
                if(combi_eval[j].brelan > combi_eval[g].brelan)
                    g = j;
                else if(combi_eval[j].brelan == combi_eval[g].brelan){
                    if(combi_eval[j].paire1 > combi_eval[g].paire1)
                        g = j;
                }
            }
            else if(combi_eval[j].type == 7){
                if(combi_eval[j].carre > combi_eval[g].carre)
                    g = j;
                else if(combi_eval[j].carre == combi_eval[g].carre){
                    int zj, zg;
                    int hj = combi_eval[j].carre;
                    int hg = combi_eval[g].carre;
                    deck dj = players[j].getMain();
                    deck dg = players[g].getMain();
                    sort(dj.begin(), dj.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    sort(dg.begin(), dg.end(), [](card a, card b) {return a.getValue() > b.getValue();});
                    zj = 0;
                    zg = 0;
                    while(hj == combi_eval[j].carre && zj < 3){
                        if(dj[zj].getValue()!=hj){
                            hj = dj[zj].getValue();
                        }
                        else
                            zj++;
                        if(zj == 3)
                            hj = 0;
                    }
                    while(hg == combi_eval[g].carre && zg < 3){
                        if(dj[zg].getValue()!=hj){
                            hg = dg[zg].getValue();
                        }
                        else
                            zg++;
                        if(zg == 3)
                            hg = 0;
                    }
                    if(hj > hg)
                        g = j;
                }
            }
            else if(combi_eval[j].type == 8){
                if(combi_eval[j].hauteursuite > combi_eval[g].hauteursuite)
                    g = j;
            }
        }
    }
    cout << endl;
    gagne(g);
}

int game::combien(){
    int indice;
    int nb = 0;
    for(int i=0; i<size; i++){
        if(players[i].getM() == 1){
            nb++;
            indice = i;
        }
    }
    if(nb == 1)
        return indice;
    else
        return 8;
}

void game::gagne(int i){
    cout << endl;
    int jm = 0;
    for(int j=0; j<size; j++)
        if(players[j].getM() == 1)
            jm++;
    int maxrecup = players[i].getMiseT() * jm;
    if(pot > maxrecup){
        players[i].setCredit(players[i].getCredit() + maxrecup);
        cout << "Joueur " << i+1 << " gagne et récupère " << maxrecup << " biftons !!" << endl;
    }
    else{
        players[i].setCredit(players[i].getCredit() + pot);
        cout << "Joueur " << i+1 << " gagne et récupère " << pot << " biftons !!" << endl;
    }
    (players[i].getMain()).print();
    cout << endl;
    sleep(3);
}

void game::clear(){
    pot = 0;
    table.clear();
    for(int i=0; i<size; i++){
        players[i].clearMain();
        players[i].setMiseT(0);
        players[i].setStatus(-2) ; 
    }
}

void game::partie(){
    int i=0;
    cout << "La partie de Poker va commencer !" << endl;
    srand (time(NULL));
    init();
    while(combien() == 8){
        manche(i);
        i++;
    }
}

// Méthodes d'affichage. 

string game::printPot(int bet){
    string s ;  
    if(bet < 10){
        s = "|         POT : " + to_string(bet) + " $          |" ;
    }
    if(bet >= 10  && bet < 100){
        s = "|         POT : " + to_string(bet) + " $         |"  ; 
    }
    if(bet >= 100 && bet < 1000){
        s = "|        POT : " + to_string(bet) + " $         |"  ; 
    }
    if (bet >=1000){
        s = "|        POT : " + to_string(bet) + " $        |"  ; 
    }
    return s ; 
}

string game::printBet(int bet){
    string s ; 
    if(bet >= 0 && bet < 10){
        s = "                BET : " + to_string(bet) + " $               " ;
    }
    if(bet >= 10  &&bet < 100){
        s = "                BET : " + to_string(bet) + " $             " ;
    }
    if(bet >= 100 && bet < 1000){
        s = "               BET : " + to_string(bet) + " $             " ;
    }
    if (bet >=1000){
        s = "               BET : " + to_string(bet) + " $              " ;
    }
    return s ; 
}

string game::printCheck(int bet){
    string s ; 
    if(bet >= 0 && bet < 10){
        s = "              CHECK : " + to_string(bet) + " $              " ;
    }
    if(bet >= 10  && bet < 100){
        s = "              CHECK : " + to_string(bet) + " $             " ;
    }
    if(bet >= 100 && bet < 1000){
        s = "              CHECK : " + to_string(bet) + " $            " ;
    }
    if (bet >=1000){
        s = "             CHECK : " + to_string(bet) + " $            " ;
    }
    return s ; 
}

string game::printFollow(int bet){
    string s ; 
    if(bet >= 0 && bet < 10){
        s = "             FOLLOW : " + to_string(bet) + " $              " ;
    }
    if(bet >= 10  && bet < 100){
        s = "             FOLLOW : " + to_string(bet) + " $             " ;
    }
    if(bet >= 100 && bet < 1000){
        s = "             FOLLOW : " + to_string(bet) + " $            " ;
    }
    if (bet >=1000){
        s = "            FOLLOW : " + to_string(bet) + " $            " ;
    }
    return s ; 
}

string game::printRaise(int bet){
    string s ; 
    if(bet >= 0 && bet < 10){
        s = "               RAISE : " + to_string(bet) + " $             " ;
    }
    if(bet >= 10  && bet < 100){
        s = "               RAISE : " + to_string(bet) + " $            " ;
    }
    if(bet >= 100 && bet < 1000){
        s = "              RAISE : " + to_string(bet) + " $            " ;
    }
    if (bet >=1000){
        s = "             RAISE : " + to_string(bet) + " $            " ;
    }
    return s ; 
}

string game::playerHand(int auth, int id){
    string pHand ; 
    if(auth != id)
        pHand =  "          Player " + to_string(id+1) + " : ?[?] ?[?]         " ; 
    else{
        pHand = players[auth].playerHand(id) ; 
    }
    return pHand ; 
}

string game::playerStatus(int id){
    string pS ; 

    int i = players[id].getStatus() ; 
    int miseTemp = players[id].getMiseInt() ; 
    int mise = players[id].getMiseTInt() ; 

    if( mise < miseTemp){
        mise = miseTemp ; 
    }
    switch(i) {
        case -10 : 
    pS = "             PLUS UN ROND              " ; 
        break ; 
        case -2 : 
    pS = "               WAITING                 " ; 
        break ; 

        case -1 : 
    pS = "              BLIND : " + to_string(mise) + " $             " ;
        break ; 
        case 0 :
    pS = printFold() ; 
        break ; 

        case 1 :
    pS = printCheck(mise) ; 
        break ; 
    
        case 2 : 
    pS = printRaise(mise) ; 
        break ; 
        
        case 3 : 
    pS = printBet(mise) ; 
        break ; 

        case 4 : 
    pS = printFollow(mise) ; 
        break ; 
    }

    return pS ; 
}

string game::cardOnTable(){
    // 4 Case :  0 Card, 3 Cards, 4 Cards and 5 on table. 
    string s ; 

    if(table.size() == 0){
        s = "|  ?[?] ?[?] ?[?] ?[?] ?[?]  |" ; 
    }
    else if (table.size() == 3)
        s = "|  " + table.strPrint() + "?[?] ?[?]  |" ; 
    else if (table.size() == 4)
        s = "|  " + table.strPrint() + "?[?]  |" ;
    else 
        s = "|  " + table.strPrint() + " |" ;
    return s ; 
}

void game::printTableInfos(int nb_player, int auth) {
    float betage = pot ;  
    auth -=1 ; 
    int j ; 
    switch( nb_player ){
        case 2 :
            cout << endl << printTopTable() << endl ;  
            for(j = 0 ; j < 9 ; j++){
                if( j==3 ){
                    cout << spacing() <<  cardOnTable() << endl ; 
                }
                else if ( j==4 ){
                    cout << playerHand(auth,0) << emptyTable() << playerHand(auth,1) << endl ;  
                }
                else if ( j==5 ){
                    cout << playerStatus(0) << printPot(betage)  << playerStatus(1) <<  endl ; 
                }
                else{
                    cout << spacing() <<  emptyTable() << endl ; 
                }
            }
            cout << printBottomTable() << endl ; 
        break ; 

        case 3 :
            cout << endl << minispacing() << playerHand(auth,1) << endl << minispacing() << playerStatus(1) << endl << printTopTable() << endl ;  

            for(j = 0 ; j < 9 ; j++){
                if( j==3 ){
                    cout << spacing() <<  cardOnTable() << endl ; 
                }
                else if ( j==4 ){
                    cout << playerHand(auth,0) << emptyTable() << playerHand(auth,2) << endl ;  
                }
                else if ( j==5 ){
                    cout << playerStatus(0) << printPot(betage)  << playerStatus(2) <<  endl ; 
                }
                else{
                    cout << spacing() <<  emptyTable() << endl ; 
                }
            }
            cout << printBottomTable() << endl ; 
        break ; 
    
        case 4 :
            cout << endl << minispacing() << playerHand(auth,1) << endl << minispacing() << playerStatus(1) << endl << printTopTable() << endl ;  
            for(j = 0 ; j < 9 ; j++){
                if( j==3 ){
                    cout << spacing() <<  cardOnTable() << endl ; 
                }
                else if ( j==4 ){
                    cout << playerHand(auth,0) << emptyTable() << playerHand(auth,2) << endl ;  
                }
                else if ( j==5 ){
                    cout << playerStatus(0) << printPot(betage)  << playerStatus(2) <<  endl ; 
                }
                else{
                    cout << spacing() <<  emptyTable() << endl ; 
                }
            }
            cout << printBottomTable() << endl << minispacing() << playerHand(auth,3)<< endl << minispacing() << playerStatus(3) << endl ;  
        break ; 
        
        case 5 : 
            cout << endl << minispacing() << playerHand(auth,1) << endl << minispacing() << playerStatus(1) << endl << printTopTable() << endl ;  
            for(j = 0 ; j < 9 ; j++){
                if( j==3 ){
                    cout << playerStatus(0) <<  cardOnTable() << endl ; 
                }
                else if ( j==4 ){
                    cout << spacing() << emptyTable() << playerHand(auth,2) << endl ;  
                }
                else if ( j==5 ){
                    cout << spacing() << printPot(betage)  << playerStatus(2) << endl ; 
                }
                else{
                    if( j==2 ){
                        cout << playerHand(auth,0) << emptyTable() << endl ;   
                    }
                    else if(j ==6){
                        cout << playerHand(auth,4) << emptyTable() << endl ;   
                    }
                    else if(j == 7){
                        cout << playerStatus(4) << emptyTable() << endl ; 
                    }
                    else{
                    cout << spacing() <<  emptyTable() << endl ; 
                    }
                }
            }
            cout << printBottomTable() << endl << minispacing() << playerHand(auth,3)<< endl << minispacing() << playerStatus(3) << endl ; 
        break ; 

        case 6 : 
            cout << endl << minispacing() << playerHand(auth,1) << endl << minispacing() << playerStatus(1) << endl << printTopTable() << endl ;  
            for(j = 0 ; j < 9 ; j++){
                if( j==3 ){
                    cout << playerStatus(0) <<  cardOnTable() << playerStatus(2) << endl ; 
                }
                else if ( j==5 ){
                    cout << spacing() << printPot(betage)  << endl ; 
                }
                else{
                    if( j==2 ){
                        cout << playerHand(auth,0) << emptyTable()  << playerHand(auth,2) << endl ;   
                    }
                    else if(j ==6){
                        cout << playerHand(auth,5) << emptyTable() << playerHand(auth,3) << endl ;   
                    }
                    else if(j == 7){
                        cout << playerStatus(5) << emptyTable() << playerStatus(3) << endl ; 
                    }
                    else{
                    cout << spacing() <<  emptyTable() << endl ; 
                    }
                }
            }
            cout << printBottomTable() << endl << minispacing() << playerHand(auth,4)<< endl << minispacing() << playerStatus(4) << endl ;  
        break ; 
    }
}
    