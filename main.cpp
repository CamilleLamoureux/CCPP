#include <iostream>
#include <string>

using namespace std;

class Colors {
public:
    string black1 = "\033[1;30m";
    string black2 = "\033[0m";
    string red1 = "\033[1;31m";
    string red2 = "\033[0m";
    string green1 = "\033[1;32m";
    string green2 = "\033[0m";
    string yellow1 = "\033[1;33m";
    string yellow2 = "\033[0m";
    string blue1 = "\033[1;34m";
    string blue2 = "\033[0m";
    string magenta1 = "\033[1;35m";
    string magenta2 = "\033[0m";
    string cyan1 = "\033[1;36m";
    string cyan2 = "\033[0m";
    string white1 = "\033[1;37m";
    string white2 = "\033[0m";

    string backWhite1 = "\033[1;47m";
    string backWhite2 = "\033[0m";
    string backRed1 = "\033[1;41m";
    string backRed2 = "\033[0m";
    string backGreen1 = "\033[1;42m";
    string backGreen2 = "\033[0m";
    string backYellow1 = "\033[1;43m";
    string backYellow2 = "\033[0m";
};

void consoleClear() {
    cout<< string( 100, '\n' );
}

void finDuJeu(bool alive1, bool alive2, int nombreTours){
    consoleClear();
    if(alive1 == 1 && alive2 == 1) {cout<< "Votre victoire est totale ! Vous avez réussit à maintenair vos deux voitures pendant 50 tours !"<<endl;}
    else if(alive1 == 1 || alive2 == 1) {cout<< "Votre victoire est partielle ! Vous avez réussit à maintenair vos une voiture sur les deux pendant 50 tours !"<<endl;}
    else {cout<< "Vous avez perdu... Vous avez tenu " << nombreTours << " tours ! Vous pouvez toujours retenter votre chance !"<<endl;};
}

void display(string type, int n) {
    Colors colors;
    string color1; string color2;


    if(type=="c"){
        if(n <= 30){color1 = colors.backGreen1; color2 = colors.backGreen2;}
        else if(n >= 70) {color1 = colors.backRed1; color2 = colors.backRed2;}
        else{color1 = colors.backYellow1; color2 = colors.backYellow2;}
    }
    else if(type=="d"){
        if(n >= 70){color1 = colors.backGreen1; color2 = colors.backGreen2;}
        else if(n <= 30) {color1 = colors.backRed1; color2 = colors.backRed2;}
        else{color1 = colors.backYellow1; color2 = colors.backYellow2;}
    }


    cout << color1 << string(n, ' ') << color2;
    cout << colors.backWhite1 << string(100-n, ' ') << colors.backWhite2 <<endl;
};


class Voiture {
public:
    // ATTRIBUTS
    // Generic
    const int vitess_max = 323;

    // Chose by user
    string nomVoiture;
    string typeVoiture;
    bool propulsion = 0;
    bool traction = 0;
    bool quatreRouesMotrices = 0;
    int boiteVitesses;

    // Will change during a turn
    bool alive = 1;
    int temperatureMoteur = 50;
    int essence = 100;
    int pressionPneusAvant = 100;
    int pressionPneusArriere = 100;
    int usurePneusAvant = 5;
    int usurePneusArriere = 5;
    int huileMoteur = 100;
    int usureBoiteVitesse = 5;
    int usureFreins = 5;
    int usureCremaillere = 5;

    // METHODES
    void creationVoiture(string nom, int nombre_vitesses, int type) {
        boiteVitesses = nombre_vitesses;
        nomVoiture = nom;

        switch (type) {
            case 1 :
                propulsion = 1;
                typeVoiture = "propulsion";
                break;
            case 2 :
                traction = 1;
                typeVoiture = "traction";
                break;
            case 3 :
                quatreRouesMotrices =1;
                typeVoiture = "quatre roues motrices";
                break;
        }
    }

    void update() {
        essence -= 3;

        temperatureMoteur += 5;
        huileMoteur -= 2;

        pressionPneusAvant -= 2;
        pressionPneusArriere -= 2;

        usurePneusAvant += 5;
        usurePneusArriere += 5;

        usureFreins += 5;
        usureCremaillere += 5;
        usureBoiteVitesse += 5;
    }

    void affichageStat(){
        Colors colors;

        cout<< colors.blue1 << "\n *** Statistiques de " << nomVoiture << " : ***" << colors.blue2 <<endl;
        cout<< colors.black1 << "    Type : " << typeVoiture << colors.black2 <<endl;
        cout<< "    Carburant :          "; display("d",essence);
        cout<< "\n    Pneus : ";
        cout<< "\n      - Avant : \n         - Usure :      "; display("c", usurePneusAvant);
        cout<< "\n         - Pression :    "; display("d", pressionPneusAvant);
        cout<< "\n      - Arrière : \n         - Usure :      "; display("c", usurePneusArriere);
        cout<< "\n         - Pression :    "; display("d", pressionPneusArriere);
        cout<< "\n    Moteur : ";
        cout<< "\n      - Niveau d'huile : "; display("d",huileMoteur);
        cout<< "\n      - Temperature :    "; display("c",temperatureMoteur);
        cout<< "\n    Freins :             "; display("c",usureFreins);
        cout<< "\n    Cremaillère :        "; display("c",usureCremaillere);
        cout<< "\n    Boite de Vitesses :  "; display("c",usureBoiteVitesse);
    }

    void ajustement(){
        Colors colors;
        int aChanger;

        cout<< colors.yellow1 << "\n == AJUSTEMENT DE " << nomVoiture << " ==" << colors.yellow2 <<endl;
        cout<< "0. Exit \n 1. Remettre de l'essence \n 2. Remettre de l'huile dans le moteur \n 3. Regonfler les pneus avants \n 4. Regonfler les pneus arrières \n 5. Changer les freins \n 6. Changer les pneus avants \n 7. Changer les pneus arrières \n 8. Faire refroidir le moteur \n 9. Renover la crémaillère \n 10. Renover la boite de vitesses"<<endl;
        cin>> aChanger;

        consoleClear();
        cout<< colors.green1 << nomVoiture << " : " << colors.green2;
        switch(aChanger){
            case 0 :
                break;
            case 1 :
                essence = 15;
                cout<< colors.green1 << "Vous avez fait le plein !" << colors.green2 <<endl;
                break;
            case 2 :
                huileMoteur = 10;
                cout<< colors.green1 << "Votre niveau d'huile moteur est parfait !" << colors.green2 <<endl;
                break;
            case 3 :
                pressionPneusAvant += 1;
                cout<< colors.green1 << "La pression de vos pneus avant est maintenant de " << pressionPneusAvant << "bar." << colors.green2 <<endl;
                break;
            case 4 :
                pressionPneusArriere += 1;
                cout<< colors.green1 << "La pression de vos pneus arrière est maintenant de " << pressionPneusArriere << "bar." << colors.green2 <<endl;
                break;
            case 5 :
                usureFreins = 0;
                cout<< colors.green1 << "Vos freins sont comme neufs !" << colors.green2 <<endl;
                break;
            case 6 :
                usurePneusAvant = 0;
                cout << colors.green1 << "Vos pneus avant sont neufs !" << colors.green2 <<endl;
                break;
            case 7 :
                usurePneusArriere = 0;
                cout << colors.green1 << "Vos pneus arrières sont neufs !";
                break;
            case 8 :
                temperatureMoteur -= 5;
                cout<< colors.green1 << "La température du moteur est de " << temperatureMoteur << "°C." << colors.green2 << endl;
                break;
            case 9 :
                usureCremaillere -= 0.5;
                cout<< colors.green1 << "Votre crémaillère est usée à " << usureCremaillere << "/10." << colors.green2 <<endl;
                break;
            case 10 :
                usureBoiteVitesse -= 0.5;
                cout<< colors.green1 << "Votre boite de vitesses est usée à " << usureBoiteVitesse << "/10." << colors.green2 <<endl;
                break;
        }
    };

    void verifications(){
        Colors colors;

        if (essence <= 0) { cout<< colors.red1 << "C'est la panne sèche pour " << nomVoiture << " ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (huileMoteur <= 0) { cout<< colors.red1 <<"Le moteur a cassé sur " << nomVoiture << " ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (temperatureMoteur >= 100) { cout<< colors.red1 << "Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (usureBoiteVitesse >= 100) { cout<< colors.red1 << "La boite de vitesse de" << nomVoiture << "  est morte ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (usureCremaillere >= 100) { cout<< colors.red1 << "La cremaillère de " << nomVoiture << "  est trop usée ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (usureFreins >= 100) { cout<< colors.red1 <<"Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (pressionPneusArriere >= 100 && propulsion == 1) { cout<< colors.red1 << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus arrière sont à plat ! C'est une propulsion ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (pressionPneusAvant >= 100 && traction == 1) { cout<< colors.red1 <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus avant sont à plat ! C'est une traction ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (pressionPneusAvant >= 100 && pressionPneusArriere >= 100) { cout<< colors.red1 <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus sont tous à plat ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
        if (usurePneusAvant >= 100 && usurePneusArriere >= 100) { cout<< colors.red1 <<"Les pneus de " << nomVoiture << " sont tous trop usés ! Elle quitte la course..." << colors.red2 <<endl; alive = 0;}
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

    string ajustement;
    int ajustementAFaire;

    int nombreTours = 50;

    Colors colors;

    // CREATION DES VOITURES
    cout<< colors.yellow1 << "== CREATION DES VOITURES ==" << colors.yellow2 <<endl;
    cout<< colors.blue1 << "*** PREMIERE VOITURE ***" << colors.blue2 <<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin>> nom_voiture_1;
    cout<< "Choisissez le nombre de vitesse : " <<endl;
    cin>> nombre_vitesses_1;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl;
    cin>> type_1;

    cout<< colors.blue1 << "*** DEUXIEME VOITURE ***" << colors.blue2 <<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin>> nom_voiture_2;
    cout<< "Choisissez le nombre de vitesse : " <<endl;
    cin>> nombre_vitesses_2;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl;
    cin>> type_2;

    Voiture voiture1, voiture2;

    voiture1.creationVoiture(nom_voiture_1, nombre_vitesses_1, type_1);
    voiture2.creationVoiture(nom_voiture_2, nombre_vitesses_2, type_2);

    consoleClear();

    // DEBUT DES TOURS
    for (int i = 1; i <= 10 ; i++) {
        cout<< colors.cyan1 << "\n == TOUR "<< i << " ==" << colors.cyan2 <<endl;

        // Changement des différents éléments de la voiture suite au premier tour et affichage des stats
        if (voiture1.alive == 1){voiture1.update(); voiture1.affichageStat(); voiture1.verifications();}
        if (voiture2.alive == 1){voiture2.update(); voiture2.affichageStat(); voiture2.verifications();}
        // Vérification qu'on a pas perdu
        if(voiture1.alive == 0 && voiture2.alive == 0) {nombreTours = i; break;}

        // Changement d'informations par l'utilisateur
        cout<< colors.magenta1 <<"Souhaitez-vous effectuer un ajustement sur une voiture ? [O/N]" << colors.magenta2 <<endl;
        cin >> ajustement;
        if(ajustement == "O" || ajustement == "o" || ajustement == "0"){
            cout<< colors.red1 << "ATTENTION : Vous ne pouvez effectuer qu'une action par tour, et sur une seule voiture ! Choisissez sagement ;-)" << colors.red2 <<endl;
            cout<< "Sur quelle voiture ?" <<endl;
            cout<< "0. Exit" <<endl;
            if(voiture1.alive == 1){ cout<< "1. " << voiture1.nomVoiture <<endl;};
            if(voiture2.alive == 1){ cout<< "2. " << voiture2.nomVoiture <<endl;};
            cin >> ajustementAFaire;

            if(ajustementAFaire == 1) {consoleClear(); voiture1.affichageStat(); voiture1.ajustement();}
            else if(ajustementAFaire == 2) {consoleClear(); voiture2.affichageStat(); voiture2.ajustement();}
            else {continue;};
        }
        else{
            consoleClear();
        }
    }
    cout<< colors.yellow1 << "== END OF GAME ==" <<colors.yellow2 <<endl;
    finDuJeu(voiture1.alive, voiture2.alive, nombreTours);

    return 0;
}
