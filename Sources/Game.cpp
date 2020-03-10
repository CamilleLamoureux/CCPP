#include "../Headers/Game.h"

bool Game::check(string type, int value){

    if(type == "boite_vitesse") {
        if(value <= 6 && value > 0) {return true;} else {cout<< "Choisissez le nombre de vitesses de la boite de vitesses : " <<endl; return false;}
    }
    else if (type == "type_voiture") {
        if(value > 0 && value <= 3) {return true;} else {cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl; return false;}
    }
    else if (type == "vitesse_droit") {
        if(value <= 323 && value > 0) {return true;} else {cout << Display::magenta << "Vitesse dans les lignes droites : " << Display::close; return false;}
    }
    else if (type == "vitesse_virage") {
        if(value <= 323 && value > 0) {return true;} else {cout << Display::magenta << "Vitesse dans les virages : " << Display::close; return false;}
    }
    else if (type == "direction") {
        if(value > 0 && value <= 100) {return true;} else {cout << Display::magenta << "Paramétrage de la direction : " << Display::close; return false;}
    }
    else if (type == "one_or_two") {
        if (value > 0 && value <=3) {return true;} else {cout<< "Sur quelle voiture ?" <<endl; return false; }
    }

    return false;
}

void Game::finDuJeu(bool alive1, bool alive2, int nombreTours){

    Display::consoleClear();

    if(alive1 && alive2 && nombreTours >= butNombreTours) {cout << Display::green << "Votre victoire est totale ! Vous avez réussit à maintenair vos deux voitures pendant " << butNombreTours <<" tours !" << Display::close << endl;}
    else if((alive1 || alive2) && nombreTours >= 50) {cout << Display::green << "Votre victoire est partielle ! Vous avez réussit à maintenir vos une voiture sur les deux pendant " << butNombreTours <<" tours !" << Display::close << endl;}
    else if((not alive1 && not alive2) && nombreTours >= 50) {cout << Display::red << "Vous avez perdu... Vous avez tenu " << nombreTours << " tours ! Vous pouvez toujours retenter votre chance !" << Display::close << endl;}
}