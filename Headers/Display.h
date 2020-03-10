
#ifndef FINAL_PROJECT_DISPLAY_H
#define FINAL_PROJECT_DISPLAY_H

#include <string>
#include <iostream>
using namespace std;

class Display {

public:
    static void consoleClear();
    static void affichageDiagrameStat(string type, int n);
    static void affichageProgression(int n);
};


#endif //FINAL_PROJECT_DISPLAY_H
