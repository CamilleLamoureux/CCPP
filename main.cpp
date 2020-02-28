#include <iostream>
#include <string>

using namespace std;

class Voiture {
public:
    // ATTRIBUTS
    // Generic
    const int vitess_max = 323;

    // Chose by user
    string nom;
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

    // METHODES
    void CreationVoiture(string nom, int nombre_vitesses, int type) {
        Voiture::boite_de_vitesse = nombre_vitesses;
        Voiture::nom = nom;

        switch (type) {
            case 1 :
                Voiture::propulsion = 1;
                break;
            case 2 :
                Voiture::traction = 1;
                break;
            case 3 :
                Voiture::quatre_roues_motrices =1;
                break;
        }

        cout << "\n VOITURE CREE" << endl;
        cout << "Détails de " << Voiture::nom << " : " << endl;
        cout << "    - " << Voiture::boite_de_vitesse << " vitesses" << endl;
        switch (type) {
            case 1 :
                cout << "    - Propulsion" << endl;
                break;
            case 2 :
                cout << "    - Traction" << endl;
                break;
            case 3 :
                cout << "    - Quatre roues motrices" << endl;
                break;
        }
    }

    void ChangementEssence() {
        Voiture::essence = Voiture::essence - 5;
    }

    void ChangementTempMoteur() {
        Voiture::temperature_moteur = Voiture::temperature_moteur + 10;
    }

    void ChangementPneus() {
        Voiture::pression_pneus_avant = Voiture::pression_pneus_avant - 0.2;
        Voiture::pression_pneus_arriere = Voiture::pression_pneus_arriere - 0.2;

        Voiture::usure_pneus_avant = Voiture::usure_pneus_avant + 1;
        Voiture::usure_pneus_arriere = Voiture::usure_pneus_arriere + 1;
    }

    void ChangementUsureVoiture() {
        Voiture::usure_frein = Voiture::usure_frein +1;
        Voiture::usure_cremaillere = Voiture::usure_cremaillere +1;
        Voiture::usure_boite_vitesse = Voiture::usure_boite_vitesse +1;
    }
};

int main() {
    string nom_voiture_1;
    string nom_voiture_2;
    int nombre_vitesses_1;
    int nombre_vitesses_2;
    int type_1;
    int type_2;

    cout<<"== PREMIERE VOITURE =="<<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin>> nom_voiture_1;
    cout<< "Choisissez le nombre de vitesse : " <<endl;
    cin>> nombre_vitesses_1;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl;
    cin>> type_1;

    cout<<"== DEUXIEME VOITURE =="<<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin>> nom_voiture_2;
    cout<< "Choisissez le nombre de vitesse : " <<endl;
    cin>> nombre_vitesses_2;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl;
    cin>> type_2;

    Voiture voiture1, voiture2;

    voiture1.CreationVoiture(nom_voiture_1,nombre_vitesses_1,type_1);
    voiture2.CreationVoiture(nom_voiture_2,nombre_vitesses_2,type_2);

    return 0;
}
