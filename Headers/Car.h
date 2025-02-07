#ifndef FINAL_PROJECT_CAR_H
#define FINAL_PROJECT_CAR_H

#include <string>
#include <iostream>
#include "../Headers/Display.h"
#include "../Headers/Circuit.h"
#include "../Headers/Game.h"

using namespace std;

class Car {
public:
    int poidsVoiture = 735; // une formule 1 pèse 735kg

    string nomVoiture;
    string typeVoiture;
    bool propulsion = false;
    bool traction = false;
    bool quatreRouesMotrices = false;
    int nombreVitesses;
    bool alive = true;
    bool accident = false;

    int vitesseDroit = 0; // en km/h
    int vitesseVirage = 0; // en km/h
    int temperatureMoteur = 50; // en %
    int niveauEssence = 100; // en %
    int pressionPneusAvant = 60; // en %
    int pressionPneusArriere = 60; // en %
    int usurePneusAvant = 5; // en %
    int usurePneusArriere = 5; // en %
    int usureFreins = 5; // en %

    int freinage = vitesseDroit - vitesseVirage;
    float indiceConso = 1;

    // METHODES
    void creationVoiture(string nom, int boiteVitesse, int type);
    void update();
    void ajustement();
    void changementParamCourse();
    void verifications();
    void afficheTexteStat();
    void affichageParamCourse();
};

#endif //FINAL_PROJECT_CAR_H
