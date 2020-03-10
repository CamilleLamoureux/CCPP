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
        if (pressionPneusAvant < 20){ // pas assez gonflé
            usurePneusAvant += 20;
        }
        else if (pressionPneusAvant > 90) { // trop gonflé
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
        if (pressionPneusArriere < 20){ // pas assez gonflé
            usurePneusArriere += 20;
        }
        else if (pressionPneusArriere > 90) { // trop gonflé
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
        if (pressionPneusArriere < 20 ){ // pas assez gonflé
            usurePneusArriere += 15;
        }
        else if (pressionPneusArriere > 90) { // trop gonflé
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
        
        if (pressionPneusAvant < 20){ // pas assez gonflé
            usurePneusAvant += 15;
        }
        else if (pressionPneusAvant > 90) { // trop gonflé
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

    // Si la vitesse et le rapport sont biens paramétrés
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
    niveauEssence -= ((( Circuit::tailleTour + poidsTotal * 0.01)*((45*indiceConso)/100))*100)/120; // consomation d'niveauEssence de 45L/100km, avec une légère influence du poids de la voiture, ramenée sur 100


    // Mise à 0 des valeurs négatives pour ne pas avoir d'erreur d'affichage
    if (temperatureMoteur < 0) {temperatureMoteur = 0;}
    if (pressionPneusArriere < 0) {pressionPneusArriere = 0;}
    if (pressionPneusAvant < 0) {pressionPneusAvant = 0;}
    if (usurePneusAvant < 0) {usurePneusAvant = 0;}
    if (usurePneusArriere < 0) {usurePneusArriere = 0;}
    if (usureFreins < 0) {usureFreins = 0;}
    if (niveauEssence < 0) {niveauEssence = 0;}
    if (temperatureMoteur < 0) {temperatureMoteur = 0;}

    // Mise à 100 des valeurs supérieures à 100 pour ne pas avoir d'erreur d'affichage
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

    cout << Display::yellow << "\n == AJUSTEMENT DE " << nomVoiture << " ==" << Display::close << endl;
    cout<< "0. Exit \n 1. Faire le plein d'essence "
           "\n 2. Faire refroidir le moteur (-50%)"
           "\n 3. Regonfler les pneus avants (+20%)"
           "\n 4. Regonfler les pneus arrières (+20%) "
           "\n 5. Changer les freins "
           "\n 6. Changer les pneus avants "
           "\n 7. Changer les pneus arrières "<<endl;
    cin>> aChanger;

    Display::consoleClear();

    cout << Display::green << nomVoiture << " : " << Display::close;
    switch(aChanger){
        case 0 :
            break;
        case 1 :
            niveauEssence = 100;
            cout << Display::green << "Vous avez fait le plein !" << Display::close << endl;
            break;
        case 2 :
            temperatureMoteur -= 50;
            cout << Display::green << "La température du moteur est de " << temperatureMoteur << "%." << Display::close << endl;
            break;
        case 3 :
            pressionPneusAvant += 20;
            cout << Display::green << "La pression de vos pneus avant est maintenant de " << pressionPneusAvant << "%." << Display::close << endl;
            break;
        case 4 :
            pressionPneusArriere += 20;
            cout << Display::green << "La pression de vos pneus arrière est maintenant de " << pressionPneusArriere << "%." << Display::close << endl;
            break;
        case 5 :
            usureFreins = 5;
            cout << Display::green << "Vos freins sont comme neufs !" << Display::close << endl;
            break;
        case 6 :
            usurePneusAvant = 5;
            cout << Display::green << "Vos pneus avant sont neufs !" << Display::close << endl;
            break;
        case 7 :
            usurePneusArriere = 5;
            cout << Display::green << "Vos pneus arrières sont neufs !";
            break;
    }
}

void Car::changementParamCourse(){
    // Remise à 0 des valeurs qu'on va changer
    vitesseVirage = 0;
    vitesseDroit = 0;

    // Changement des valeurs
    cout << Display::blue << "*** PARAMETRES DE COURSE DE " << nomVoiture << " ***" << Display::close << endl;
    while (not Game::check("vitesse_droit",vitesseDroit)) {cin>> vitesseDroit;}
    while (not Game::check("vitesse_virage",vitesseVirage)) {cin>> vitesseVirage;}
}

void Car::verifications(){
    // Si on a eut un accident
    if (accident) {
        cout << Display::red
             << "La voiture " << nomVoiture
             << " a eut un accident ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si il n'y a plus d'essence
    if (niveauEssence <= 0) {
        cout << Display::red
             << "C'est la panne sèche pour " << nomVoiture << " ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si le moteur est trop chaud
    if (temperatureMoteur >= 100) {
        cout << Display::red
             << "Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si les freins sont trop usés
    if (usureFreins >= 100) {
        cout << Display::red
             << "Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si les pneus sont à plat
    if (pressionPneusAvant <= 0 || pressionPneusArriere <= 0) {
        cout << Display::red
             << "Les pneus de " << nomVoiture << "sont à plat ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;
    }

    // Si les pneus arrières sont trop sous gonflés sur une propulsion
    if (pressionPneusArriere <= 10 && propulsion) {
        cout << Display::red
             << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus arrière sont sous-gonflés ! "
                                                   "C'est une propulsion ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si les pneus avants sont trop sous glonflés sur un traction
    if (pressionPneusAvant <= 10 && traction) {
        cout << Display::red
             << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus avant sont sous-gonflés ! "
                                                   "C'est une traction ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si tous les pneus sont sous gonflés sur un 4x4
    if (pressionPneusAvant <= 10 && pressionPneusArriere <= 10) {
        cout << Display::red
             << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus sont sous-gonflés! "
                                                   "Elle quitte la course..."
             << Display::close << endl;
        alive = false;}

    // Si les pneus sont trop usés
    if (usurePneusAvant >= 100 || usurePneusArriere >= 100) {
        cout << Display::red
             << "Les pneus de " << nomVoiture << " sont tous trop usés ! Elle quitte la course..."
             << Display::close << endl;
        alive = false;}
}

void Car::afficheTexteStat(){
    cout << Display::blue << "\n *** Statistiques de " << nomVoiture << " : ***" << Display::close << endl;
    cout << Display::black << "    Type : " << typeVoiture << Display::close << endl;
    cout<< "    Carburant :          ";
    Display::affichageDiagrameStat("d", niveauEssence);
    cout<< "\n    Pneus avant: ";
    cout<< "\n         - Usure :       ";
    Display::affichageDiagrameStat("c", usurePneusAvant);
    cout<< "\n         - Pression :    ";
    Display::affichageDiagrameStat("pp", pressionPneusAvant);
    cout<< "\n    Pneus arrière : ";
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
    cout << Display::blue << "*** Paramètres de course actuels de " << nomVoiture << " ***" << Display::close << endl;
    cout<< "    - Vitesse en ligne droite : " << vitesseDroit << " km/h" <<endl;
    cout<< "    - Vitesse dans les virages : " << vitesseVirage << " km/h" <<endl;
}
