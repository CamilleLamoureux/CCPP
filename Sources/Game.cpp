#include "../Headers/Game.h"

bool Game::check(string type, int value){

    if(type == "boite_vitesse") {
        if(value <= 6 && value > 0) {return true;} else {cout<< "Choisissez le nombre de vitesses de la boite de vitesses : " <<endl; return false;}
    }
    else if (type == "type_voiture") {
        if(value > 0 && value <= 3) {return true;} else {cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl; return false;}
    }
    else if (type == "vitesse_droit") {
        if(value <= 323 && value > 0) {return true;} else {cout  << "Vitesse dans les lignes droites : " ; return false;}
    }
    else if (type == "vitesse_virage") {
        if(value <= 323 && value > 0) {return true;} else {cout  << "Vitesse dans les virages : " ; return false;}
    }
    else if (type == "direction") {
        if(value > 0 && value <= 100) {return true;} else {cout  << "Parametrage de la direction : " ; return false;}
    }
    else if (type == "one_or_two") {
        if (value > 0 && value <=3) {return true;} else {cout<< "Sur quelle voiture ?" <<endl; return false; }
    }

    return false;
}

void Game::finDuJeu(bool alive1, bool alive2, int nombreTours, int butNombreTours){

    Display::consoleClear();

    if(nombreTours == butNombreTours){
        if(alive1 && alive2) {cout  << "Votre victoire est totale ! Vous avez reussi a maintenir vos deux voitures pendant " << nombreTours <<" tours !"  << endl;}
        else if(alive1 || alive2) {cout  << "Votre victoire est partielle ! Vous avez reussi a maintenir une voiture sur les deux pendant " << nombreTours <<" tours !"  << endl;}
    }
   else if(not alive1 && not alive2) {cout  << "Vous avez perdu... Vous avez tenu " << nombreTours << " tours ! Vous pouvez toujours retenter votre chance !"  << endl;}
}