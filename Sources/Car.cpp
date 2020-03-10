#include "../Headers/Car.h"

void Car::creationVoiture(string nom, int boiteVitesse, int type) {
    nombreVitesses = boiteVitesse;
    nomVoiture = nom;

    switch (type) {
        case 1 :
            propulsion = true;
            typeVoiture = "propulsion";
            break;
        case 2 :
            traction = true;
            typeVoiture = "traction";
            break;
        case 3 :
            quatreRouesMotrices = true;
            typeVoiture = "quatre roues motrices";
            break;
    }
}

void Car::update() {

    // Pneus & vitesse

    // TRACTION
    if (traction) {
        usurePneusArriere += 5;
        if (pressionPneusAvant < 20){ // pas assez gonfle
            usurePneusAvant += 20;
        }
        else if (pressionPneusAvant > 90) { // trop gonfle
            if (vitesseVirage > 300){
                accident = true;
            }
            else if (vitesseVirage > 220){
                accident = true;
            }
        }
        else {
            usurePneusAvant += 10;
        }

        if (vitesseVirage >= 200) {accident = true;}
    }

    // PROPULSION
    else if (propulsion){
        usurePneusAvant += 5;
        if (pressionPneusArriere < 20){ // pas assez gonfle
            usurePneusArriere += 20;
        }
        else if (pressionPneusArriere > 90) { // trop gonfle
            if (vitesseVirage > 300){
                accident = true;
            }
            else if (vitesseVirage > 250){
                accident = true;
            }
        }
        else {
            usurePneusArriere += 10;
        }
        
        if (vitesseVirage >= 250) {accident = true;}
    }

    // 4X4
    else if (quatreRouesMotrices) {
        if (pressionPneusArriere < 20 ){ // pas assez gonfle
            usurePneusArriere += 15;
        }
        else if (pressionPneusArriere > 90) { // trop gonfle
            if (vitesseVirage > 300){
                accident = true;
            }
            else if (vitesseVirage > 250){
                accident = true;
            }
        }
        else {
            usurePneusArriere += 7;
        }
        
        if (pressionPneusAvant < 20){ // pas assez gonfle
            usurePneusAvant += 15;
        }
        else if (pressionPneusAvant > 90) { // trop gonfle
            if (vitesseVirage > 300){
                accident = true;
            }
            else if (vitesseVirage > 250){
                accident = true;
            }
        }
        else {
            usurePneusAvant += 7;
        }

        if (vitesseVirage >= 250) {accident = true;}
    }

    pressionPneusArriere -= 2;
    pressionPneusAvant -= 2;

    // Freins
    if (freinage > 300) {
        usureFreins += 50;
    }
    else if (freinage > 200){
        usureFreins += 20;
    }
    else if (freinage > 100) {
        usureFreins += 10;
    }


    // Moteur
    if (temperatureMoteur > 60) {
        temperatureMoteur += 1;
    }
    else if (temperatureMoteur > 40){
        temperatureMoteur += 3;
    }
    else if (temperatureMoteur > 30){
        temperatureMoteur += 5;
    }
    else if (temperatureMoteur > 20){
        temperatureMoteur += 7;
    }
    else if (temperatureMoteur <= 20){
        temperatureMoteur += 10;
    }

    //
    if (vitesseDroit > 50 ? nombreVitesses == 1 : nombreVitesses == 1 && vitesseVirage > 50) { accident = true; }

    // Si la vitesse et le rapport sont biens parametres
    if ((nombreVitesses == 1 && (vitesseVirage < 10 || vitesseDroit < 10)) ||
        (nombreVitesses == 2 && ((vitesseDroit >= 10 || vitesseVirage >= 10) && (vitesseVirage < 70|| vitesseDroit < 70))) ||
        (nombreVitesses == 3 && ((vitesseDroit >= 70 || vitesseVirage >= 70) && (vitesseVirage < 100|| vitesseDroit < 100))) ||
        (nombreVitesses == 4 && ((vitesseDroit >= 100 || vitesseVirage >= 100) && (vitesseVirage < 190|| vitesseDroit < 190))) ||
        (nombreVitesses == 5 && ((vitesseDroit >= 190 || vitesseVirage >= 190) && (vitesseVirage < 240|| vitesseDroit < 240))) ||
        (nombreVitesses == 6 && ((vitesseDroit >= 240 || vitesseVirage >= 240) && (vitesseVirage <= 323 || vitesseDroit <= 323)))
        ){indiceConso = 0.5;}

    else if (nombreVitesses == 1){
        if (vitesseVirage > 15 || vitesseDroit > 15) {indiceConso = 1;}
        else if(vitesseVirage > 25 || vitesseDroit > 25) {accident = true;}
    }
    else if (nombreVitesses == 2){
        if (vitesseDroit > 80 || vitesseVirage > 80) {indiceConso = 1;}
        else if(vitesseVirage > 90 || vitesseDroit > 90) {accident = true;}
    }
    else if (nombreVitesses == 3) {
        if (vitesseVirage > 110 || vitesseDroit > 110) {indiceConso = 1;}
        else if (vitesseVirage > 120 || vitesseDroit > 120) {accident = true;}
    }
    else if (nombreVitesses == 4) {
        if (vitesseDroit > 190 || vitesseVirage > 190) {indiceConso = 1;}
        else if(vitesseVirage > 200 || vitesseDroit > 200) {accident = true;}
    }
    else if (nombreVitesses == 5) {
        if (vitesseVirage > 240 || vitesseDroit > 240) {indiceConso = 1;}
        else if (vitesseVirage > 250 || vitesseDroit > 250) {accident = true;}
    }

    // Essence
    float poidsTotal = poidsVoiture + 0.755*(niveauEssence*120)/100; // poids de la voiture + niveau d'niveauEssence * poids de l'niveauEssence (0.755kg/L)
    float consoEssence = (Circuit::tailleTour*0.45)*indiceConso + poidsTotal*0.01;
    niveauEssence -= consoEssence;

    // Mise a 0 des valeurs negatives pour ne pas avoir d'erreur d'affichage
    if (temperatureMoteur < 0) {temperatureMoteur = 0;}
    if (pressionPneusArriere < 0) {pressionPneusArriere = 0;}
    if (pressionPneusAvant < 0) {pressionPneusAvant = 0;}
    if (usurePneusAvant < 0) {usurePneusAvant = 0;}
    if (usurePneusArriere < 0) {usurePneusArriere = 0;}
    if (usureFreins < 0) {usureFreins = 0;}
    if (niveauEssence < 0) {niveauEssence = 0;}
    if (temperatureMoteur < 0) {temperatureMoteur = 0;}

    // Mise a 100 des valeurs superieures a 100 pour ne pas avoir d'erreur d'affichage
    if (temperatureMoteur > 100) {temperatureMoteur = 100;}
    if (pressionPneusArriere > 100) {pressionPneusArriere = 100;}
    if (pressionPneusAvant > 100) {pressionPneusAvant = 100;}
    if (usurePneusAvant > 100) {usurePneusAvant = 100;}
    if (usurePneusArriere > 100) {usurePneusArriere = 100;}
    if (usureFreins > 100) {usureFreins = 100;}
    if (niveauEssence > 100) {niveauEssence = 100;}
    if (temperatureMoteur > 100) {temperatureMoteur = 100;}
}

void Car::ajustement(){
    int aChanger;

    cout  << "\n == AJUSTEMENT DE " << nomVoiture << " =="  << endl;
    cout<< "0. Exit \n 1. Faire le plein d'essence "
           "\n 2. Faire refroidir le moteur (-50%)"
           "\n 3. Regonfler les pneus avants (+20%)"
           "\n 4. Regonfler les pneus arrieres (+20%) "
           "\n 5. Changer les freins "
           "\n 6. Changer les pneus avants "
           "\n 7. Changer les pneus arrieres "<<endl;
    cin>> aChanger;

    Display::consoleClear();

    cout  << nomVoiture << " : " ;
    switch(aChanger){
        case 0 :
            break;
        case 1 :
            niveauEssence = 100;
            cout  << "Vous avez fait le plein !"  << endl;
            break;
        case 2 :
            temperatureMoteur -= 50;
            cout  << "La temperature du moteur est de " << temperatureMoteur << "%."  << endl;
            break;
        case 3 :
            pressionPneusAvant += 20;
            cout  << "La pression de vos pneus avant est maintenant de " << pressionPneusAvant << "%."  << endl;
            break;
        case 4 :
            pressionPneusArriere += 20;
            cout  << "La pression de vos pneus arriere est maintenant de " << pressionPneusArriere << "%."  << endl;
            break;
        case 5 :
            usureFreins = 5;
            cout  << "Vos freins sont comme neufs !"  << endl;
            break;
        case 6 :
            usurePneusAvant = 5;
            cout  << "Vos pneus avant sont neufs !"  << endl;
            break;
        case 7 :
            usurePneusArriere = 5;
            cout  << "Vos pneus arrieres sont neufs !";
            break;
    }
}

void Car::changementParamCourse(){
    // Remise a 0 des valeurs qu'on va changer
    vitesseVirage = 0;
    vitesseDroit = 0;

    // Changement des valeurs
    cout  << "*** PARAMETRES DE COURSE DE " << nomVoiture << " ***"  << endl;
    while (not Game::check("vitesse_droit",vitesseDroit)) {cin>> vitesseDroit;}
    while (not Game::check("vitesse_virage",vitesseVirage)) {cin>> vitesseVirage;}
}

void Car::verifications(){
    // Si on a eut un accident
    if (accident) {
        cout 
             << "La voiture " << nomVoiture
             << " a eut un accident ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si il n'y a plus d'essence
    if (niveauEssence <= 0) {
        cout 
             << "C'est la panne seche pour " << nomVoiture << " ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si le moteur est trop chaud
    if (temperatureMoteur >= 100) {
        cout 
             << "Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si les freins sont trop uses
    if (usureFreins >= 100) {
        cout 
             << "Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si les pneus sont a plat
    if (pressionPneusAvant <= 0 || pressionPneusArriere <= 0) {
        cout 
             << "Les pneus de " << nomVoiture << "sont a plat ! Elle quitte la course..."
              << endl;
        alive = false;
    }

    // Si les pneus arrieres sont trop sous gonfles sur une propulsion
    if (pressionPneusArriere <= 10 && propulsion) {
        cout 
             << "Complique pour " << nomVoiture << " de rouler alors que ses pneus arriere sont sous-gonfles ! "
                                                   "C'est une propulsion ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si les pneus avants sont trop sous glonfles sur un traction
    if (pressionPneusAvant <= 10 && traction) {
        cout 
             << "Complique pour " << nomVoiture << " de rouler alors que ses pneus avant sont sous-gonfles ! "
                                                   "C'est une traction ! Elle quitte la course..."
              << endl;
        alive = false;}

    // Si tous les pneus sont sous gonfles sur un 4x4
    if (pressionPneusAvant <= 10 && pressionPneusArriere <= 10) {
        cout 
             << "Complique pour " << nomVoiture << " de rouler alors que ses pneus sont sous-gonfles! "
                                                   "Elle quitte la course..."
              << endl;
        alive = false;}

    // Si les pneus sont trop uses
    if (usurePneusAvant >= 100 || usurePneusArriere >= 100) {
        cout 
             << "Les pneus de " << nomVoiture << " sont tous trop uses ! Elle quitte la course..."
              << endl;
        alive = false;}
}

void Car::afficheTexteStat(){
    cout  << "\n *** Statistiques de " << nomVoiture << " : ***"  << endl;
    cout  << "    Type : " << typeVoiture  << endl;
    cout<< "    Carburant :          ";
    Display::affichageDiagrameStat("d", niveauEssence);
    cout<< "\n    Pneus avant: ";
    cout<< "\n         - Usure :       ";
    Display::affichageDiagrameStat("c", usurePneusAvant);
    cout<< "\n         - Pression :    ";
    Display::affichageDiagrameStat("pp", pressionPneusAvant);
    cout<< "\n    Pneus arriere : ";
    cout<< "\n         - Usure :       ";
    Display::affichageDiagrameStat("c", usurePneusArriere);
    cout<< "\n         - Pression :    ";
    Display::affichageDiagrameStat("pp", pressionPneusArriere);
    cout<< "\n    Temperature moteur : ";
    Display::affichageDiagrameStat("temp", temperatureMoteur);
    cout<< "\n    Freins :             ";
    Display::affichageDiagrameStat("c", usureFreins);
}

void Car::affichageParamCourse(){
    cout  << "*** Parametres de course actuels de " << nomVoiture << " ***"  << endl;
    cout<< "    - Vitesse en ligne droite : " << vitesseDroit << " km/h" <<endl;
    cout<< "    - Vitesse dans les virages : " << vitesseVirage << " km/h" <<endl;
}
