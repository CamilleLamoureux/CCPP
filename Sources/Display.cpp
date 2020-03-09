#include "../Headers/Display.h"

// Couleurs de texte
const string Display::black = "\033[1;30m";
const string Display::red = "\033[1;31m";
const string Display::green = "\033[1;32m";
const string Display::yellow = "\033[1;33m";
const string Display::blue = "\033[1;34m";
const string Display::magenta = "\033[1;35m";

// Couleur de surlignage
const string Display::backWhite = "\033[1;47m";
const string Display::backRed = "\033[1;41m";
const string Display::backGreen = "\033[1;42m";
const string Display::backYellow = "\033[1;43m";

// Balise de fermeture
const string Display::close = "\033[0m";

void Display::consoleClear() {
    cout<< string( 100, '\n' );
}

void Display::affichageDiagrameStat(string type, int n) {

    string color1; string color2;

    if(type=="c"){
        if(n <= 30){color1 = backGreen; color2 = close;}
        else if(n >= 70) {color1 = backRed; color2 = close;}
        else{color1 = backYellow; color2 = close;}
    }
    else if(type=="d"){
        if(n >= 70){color1 = backGreen; color2 = close;}
        else if(n <= 30) {color1 = backRed; color2 = close;}
        else{color1 = backYellow; color2 = close;}
    }
    else if (type=="temp"){
        if (n > 40 && n < 70){color1 = backGreen; color2 = close;}
        else if(n >= 80 || n <= 30) {color1 = backRed; color2 = close;}
        else{color1 = backYellow; color2 = close;}
    }
    else if (type=="pp"){
        if (n > 40 && n < 70){color1 = backGreen; color2 = close;}
        else if(n >= 80 || n <= 30) {color1 = backRed; color2 = close;}
        else{color1 = backYellow; color2 = close;}
    }

    cout << color1 << string(n, ' ') << color2;
    cout << backWhite << string(100 - n, ' ') << close << "   " << n << "%" << endl;
}

void Display::affichageProgression(int n){
    
    cout << backGreen << string(n, ' ') << Display::close;
    cout << backWhite << string(50 - n, ' ') << Display::close << endl;
}
