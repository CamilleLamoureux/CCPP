#include <iostream>
#include <string>

using namespace std;

class Voiture {
    // ATTRIBUTS
    // Generic
    const int vitess_max = 323;

    // Chose by user
    bool propulsion;
    bool traction;
    bool quatre_roues_motrices;
    int boite_de_vitesse;

    // Will change during a turn
    int temperature_moteur;         // En °C
    int essence;                    // En litres
    int pression_pneus_avant;       // En bar
    int pression_pneus_arriere;     // En bar
    int usure_pneus_avant;          // De 0 à 10
    int usure_pneus_arriere;        // De 0 à 10
    int niveau_huile_moteur;        // De 0 à 10
    int usure_boite_vitesse;        // De 0 à 10
    int usure_frein;                // De 0 à 10
    int usure_cremaillere;          // De 0 à 10

    // Méthodes
    void UtilisationEssence(essence) {
        essence = essence - 5;
    }

    void ChangementTempMoteur(temperature_moteur) {
        temperature_moteur = temperature_moteur + 10;
    }

    void ChangementPneus(pression_pneus_avant,pression_pneus_arriere,usure_pneus_arriere,usure_pneus_avant) {
        pression_pneus_avant = pression_pneus_avant - 0.2;
        pression_pneus_arriere = pression_pneus_arriere - 0.2;

        usure_pneus_avant = usure_pneus_avant + 1;
        usure_pneus_arriere = usure_pneus_arriere + 1;
    }
};


int main() {
    return 0;
}
