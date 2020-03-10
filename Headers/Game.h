//
// Created by c on 3/2/20.
//

#ifndef FINAL_PROJECT_GAME_H
#define FINAL_PROJECT_GAME_H


#include <string>
#include <iostream>
#include "../Headers/Display.h"

using namespace std;

class Game {
public:
    static const int butNombreTours = 5;

    static bool check(string type, int value);
    static void finDuJeu(bool alive1, bool alive2, int nombreTours);
};

#endif //FINAL_PROJECT_GAME_H