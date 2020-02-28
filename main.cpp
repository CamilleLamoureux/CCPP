#include <iostream>
#include <string>

using namespace std;

class Voiture {
public:
    // ATTRIBUTS
    // Generic
    const int vitess_max = 323;

    // Chose by user
    string nomVoiture;
    bool propulsion = 0;
    bool traction = 0;
    bool quatreRouesMotrices = 0;
    int boiteVitesses;

    // Will change during a turn
    bool alive = 1;
    int temperatureMoteur = 2;          // En °C
    int essence = 15;                   // En litres
    float pressionPneusAvant = 2;       // En bar
    float pressionPneusArriere = 2;     // En bar
    int usurePneusAvant = 0;            // De 0 à 10
    int usurePneusArriere = 0;          // De 0 à 10
    float huileMoteur = 5;              // sur 5
    int usureBoiteVitesse = 0;          // De 0 à 10
    int usureFreins = 0;                // De 0 à 10
    int usureCremaillere = 0;           // De 0 à 10

    // METHODES
    void creationVoiture(string nom, int nombre_vitesses, int type) {
        boiteVitesses = nombre_vitesses;
        nomVoiture = nom;

        switch (type) {
            case 1 :
                Voiture::propulsion = 1;
                break;
            case 2 :
                Voiture::traction = 1;
                break;
            case 3 :
                Voiture::quatreRouesMotrices =1;
                break;
        }

        cout << "\n VOITURE CREE" << endl;
        cout << "Détails de " << nomVoiture << " : " << endl;
        cout << "    - " << boiteVitesses << " vitesses" << endl;
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

    void update() {
        essence -= 3;

        temperatureMoteur += 10;
        huileMoteur -= 0.10;

        pressionPneusAvant -= 0.2;
        pressionPneusArriere -= 0.2;

        usurePneusAvant += 1;
        usurePneusArriere += 1;

        usureFreins += 1;
        usureCremaillere += 1;
        usureBoiteVitesse += 1;
    }

    void affichageStat(){
        cout<< "Statistiques de " << nomVoiture << " : " <<endl;
        cout<< "Carburant : " << essence << " L (maximum de 15L)" <<endl;
        cout<< "Pneus : " <<endl;
        cout<< "    - Avant : \n      - Usure : " << usurePneusAvant << "/10" << "\n      - Pression : " << pressionPneusAvant << " bar" <<endl;
        cout<< "    - Arrière : \n      - Usure : " << usurePneusArriere << "/10" << "\n      - Pression : " << pressionPneusArriere << " bar" <<endl;
        cout<< "Moteur : " <<endl;
        cout<< "    - Niveau d'huile : " << huileMoteur << "/5" << "\n    - Temperature : " << temperatureMoteur << "°C" <<endl;
        cout<< "Freins : " << usureFreins << "/10" <<endl;
        cout<< "Cremaillère : " << usureCremaillere << "/10" <<endl;
        cout<< "Boite de Vitesses : " << usureBoiteVitesse << "/10" <<endl;
    }

    void maintenance(){
        int aChanger;

        cout<< "== MAINTENANCE DE " << nomVoiture << " ==" <<endl;
        cout<< "0. Exit \n 1. Remettre de l'essence \n 2. Remettre de l'huile dans le moteur \n 3. Regonfler les pneus avants \n 4. Regonfler les pneus arrières \n 5. Changer les freins \n 6. Changer les pneus avants \n 7. Changer les pneus arrières \n 8. Faire refroidir le moteur \n 9. Renover la crémaillère \n 10. Renover la boite de vitesses"<<endl;
        cin>> aChanger;

        switch(aChanger){
            case 0 :
                break;
            case 1 :
                essence = 15;
                cout<< "Vous avez refait le plein !" <<endl;
                break;
            case 2 :
                huileMoteur = 5;
                cout<< "Votre niveau d'huile moteur est parfait !"<<endl;
                break;
            case 3 :
                pressionPneusAvant += 1;
                cout<< "La pression de vos pneus avant est maintenant de " << pressionPneusAvant << "bar." <<endl;
                break;
            case 4 :
                pressionPneusArriere += 1;
                cout<< "La pression de vos pneus arrière est maintenant de " << pressionPneusArriere << "bar." <<endl;
                break;
            case 5 :
                usureFreins = 0;
                cout<< "Vos freins sont comme neufs !" <<endl;
                break;
            case 6 :
                usurePneusAvant = 0;
                cout << "Vos pneus avant sont neufs !";
                break;
            case 7 :
                usurePneusArriere = 0;
                cout << "Vos pneus arrières sont neufs !";
                break;
            case 8 :
                temperatureMoteur -= 5;
                cout<< "La température du moteur est de " << temperatureMoteur << "°C.";
                break;
            case 9 :
                usureCremaillere -= 0.5;
                cout<< "Votre crémaillère est usée à " << usureCremaillere << "/10."<<endl;
                break;
            case 10 :
                usureBoiteVitesse -= 0.5;
                cout<< "Votre boite de vitesses est usée à " << usureBoiteVitesse << "/10."<<endl;
                break;
        }
    };

    void verifications(){
        if (essence <= 0) { cout<< " C'est la panne sèche pour " << nomVoiture << " ! Elle quitte la course..." <<endl; alive = 0;}
        if (huileMoteur <= 0) { cout<< " Le moteur a cassé sur " << nomVoiture << " ! Elle quitte la course..." <<endl; alive = 0;}
        if (temperatureMoteur >= 120) { cout<< " Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..." <<endl; alive = 0;}
        if (usureBoiteVitesse >= 10) { cout<< " La boite de vitesse de" << nomVoiture << "  est morte ! Elle quitte la course..." <<endl; alive = 0;}
        if (usureCremaillere >= 10) { cout<< " La cremaillère de " << nomVoiture << "  est trop usée ! Elle quitte la course..." <<endl; alive = 0;}
        if (usureFreins >= 10) { cout<< " Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..." <<endl; alive = 0;}
        if (pressionPneusArriere >= 10 && propulsion == 1) { cout<< "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus arrière sont à plat ! C'est une propulsion ! Elle quitte la course..." <<endl; alive = 0;}
        if (pressionPneusAvant >= 10 && traction == 1) { cout<< "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus avant sont à plat ! C'est une traction ! Elle quitte la course..." <<endl; alive = 0;}
        if (pressionPneusAvant >= 10 && pressionPneusArriere >= 10) { cout<< "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus sont tous à plat ! Elle quitte la course..." <<endl; alive = 0;}
        if (usurePneusAvant >= 10 && usurePneusArriere >= 10) { cout<< "Les pneus de " << nomVoiture << " sont tous trop usés ! Elle quitte la course..." <<endl; alive = 0;}
    };
};

int main() {
    // VARIABLES
    string nom_voiture_1;
    string nom_voiture_2;
    int nombre_vitesses_1;
    int nombre_vitesses_2;
    int type_1;
    int type_2;

    string maintenance;
    int voitureMaintenance;

    // CREATION DES VOITURES
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

    voiture1.creationVoiture(nom_voiture_1, nombre_vitesses_1, type_1);
    voiture2.creationVoiture(nom_voiture_2, nombre_vitesses_2, type_2);

    // DEBUT DES TOURS
    while (voiture1.alive == 1 || voiture2.alive ==1 ){
        for (int i = 1; i <= 50 ; i++) {
            cout<< "== TOUR "<< i << " ==" <<endl;

            // Changement des différents éléments de la voiture suite au premier tour et affichage des stats
            if (voiture1.alive == 1){voiture1.update(); voiture1.affichageStat(); voiture1.verifications();}
            if (voiture2.alive == 1){voiture2.update(); voiture2.affichageStat(); voiture2.verifications();}

            // Changement d'informations par l'utilisateur
            cout<< "Souhaitez-vous effectuer une maintenance sur une voiture ? [O/N]" <<endl;
            cin>> maintenance;
            if(maintenance == "O" || maintenance == "o" || maintenance == "0"){
                cout<< "ATTENTION : Vous ne pouvez effectuer qu'une action par tour, et sur une seule voiture ! Choisissez sagement ;-)" <<endl;
                cout<< "Sur quelle voiture ? \n" <<endl;
                if(voiture1.alive == 1){ cout<< "1." << voiture1.nomVoiture <<endl;};
                if(voiture2.alive == 1){ cout<< "2." << voiture2.nomVoiture <<endl;};
                cin>> voitureMaintenance;

                if(voitureMaintenance == 1) { voiture1.maintenance();}
                else if(voitureMaintenance == 2) { voiture2.maintenance();}
                else { break;};
            }
        }
    }
    return 0;
}
