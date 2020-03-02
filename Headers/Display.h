
#ifndef FINAL_PROJECT_DISPLAY_H
#define FINAL_PROJECT_DISPLAY_H

#include <string>
#include <iostream>
using namespace std;

class Display {

public:
    // Couleurs de texte
    static const string black;
    static const string red;
    static const string green;
    static const string yellow;
    static const string blue;
    static const string magenta;

    // Couleur de surlignage
    static const string backWhite;
    static const string backRed;
    static const string backGreen;
    static const string backYellow;

    // Balise de fermeture
    static const string close;

    static void consoleClear();
    static void affichageDiagrameStat(string type, int n);
    static void affichageProgression(int n);
};


#endif //FINAL_PROJECT_DISPLAY_H
