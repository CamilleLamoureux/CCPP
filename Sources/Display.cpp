#include "../Headers/Display.h"

void Display::consoleClear() {
    cout<< string( 100, '\n' );
}

void Display::affichageDiagrameStat(string type, int n) {

    cout<< string(n, '|');
    cout<< string(100 - n, '-') << "   " << n << "%" << endl;
}

void Display::affichageProgression(int n){
    
    cout << string(n, '|');
    cout << string(50 - n, '-') <<endl;
}
