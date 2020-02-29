#include <iostream>
#include <string>

using namespace std;

class Colors {


public:
    const string black = "\033[1;30m";
    const string red = "\033[1;31m";
    const string green = "\033[1;32m";
    const string yellow = "\033[1;33m";
    const string blue = "\033[1;34m";
    const string magenta = "\033[1;35m";
    const string cyan = "\033[1;36m";
    const string white = "\033[1;37m";

    const string backWhite = "\033[1;47m";
    const string backRed = "\033[1;41m";
    const string backGreen = "\033[1;42m";
    const string backYellow = "\033[1;43m";
    const string backBlack = "\033[1;40m";

    const string close = "\033[0m";
};

void consoleClear() {
    cout<< string( 100, '\n' );
}

void finDuJeu(bool alive1, bool alive2, int nombreTours){
    Colors colors;
    consoleClear();

    if(alive1 == 1 && alive2 == 1 && nombreTours >= 50) {cout<< colors.green << "Votre victoire est totale ! Vous avez réussit à maintenair vos deux voitures pendant 50 tours !" << colors.close <<endl;}
    else if((alive1 == 1 || alive2 == 1) && nombreTours >= 50) {cout<< colors.yellow << "Votre victoire est partielle ! Vous avez réussit à maintenair vos une voiture sur les deux pendant 50 tours !" << colors.close <<endl;}
    else if((alive1 == 0 && alive2 == 0) && nombreTours >= 50) {cout<< colors.red << "Vous avez perdu... Vous avez tenu " << nombreTours << " tours ! Vous pouvez toujours retenter votre chance !" << colors.close <<endl;}
    else { cout<< "Unexpected end of game" <<endl;};
}

void affichageDiagrameStat(string type, int n) {
    Colors colors;
    string color1; string color2;


    if(type=="c"){
        if(n <= 30){color1 = colors.backGreen; color2 = colors.close;}
        else if(n >= 70) {color1 = colors.backRed; color2 = colors.close;}
        else{color1 = colors.backYellow; color2 = colors.close;}
    }
    else if(type=="d"){
        if(n >= 70){color1 = colors.backGreen; color2 = colors.close;}
        else if(n <= 30) {color1 = colors.backRed; color2 = colors.close;}
        else{color1 = colors.backYellow; color2 = colors.close;}
    }


    cout << color1 << string(n, ' ') << color2;
    cout << colors.backWhite << string(100-n, ' ') << colors.close << "   " << n << "%"<<endl;
};

void affichageProgression(int n){
    Colors colors;
    cout<< colors.green << string(n, ' ') << colors.close;
    cout<< colors.backWhite << string(50-n, ' ') << colors.close <<endl;
};

class Voiture {
public:
    // ATTRIBUTS
        // Circuit
    const int nombreTotalVoitures = 22;
    const float tailleTour = 5.371; // en km
    const int nombreVirageGauche = 5;
    const int nombreVirageDroite = 4;

    // Chose by user
    string nomVoiture;
    string typeVoiture; // propulsion, traction ou 4x4
    bool propulsion = 0;
    bool traction = 0;
    bool quatreRouesMotrices = 0;
    int boiteVitesses;

    // Will change during a turn
    bool alive = 1;
    int vitess_max = 323; // en km/h
    int poidsVoiture = 735; // kg
    int temperatureMoteur = 50; // en %
    int essence = 100; // en %
    int pressionPneusAvant = 100; // en %
    int pressionPneusArriere = 100; // en %
    int usurePneusAvant = 5; // en %
    int usurePneusArriere = 5; // en %
    int huileMoteur = 100; // en %
    int usureBoiteVitesse = 5; // en %
    int usureFreins = 5; // en %
    int usureCremaillere = 5; // en %

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
        //TODO : évènements aléatoire (crevaison, fuite huile moteur, etc)

        // Essence
        float poidsTotal = poidsVoiture + 0.755*(essence*120)/100; // poids de la voiture + niveau d'essence * poids de l'essence (0.755kg/L)
        essence -= (((tailleTour+poidsTotal*0.01)*45/100)*100)/120; // consomation d'essence de 45L/100km, avec une légère influence du poids de la voiture, ramenée sur 100

        // Moteur
        if(temperatureMoteur <=25){
            huileMoteur -= 1;
            temperatureMoteur += 10;
        } else if (temperatureMoteur <= 50){
            huileMoteur -= 1;
            temperatureMoteur += 5;
        }
        else if (temperatureMoteur >= 75){
            huileMoteur -= 5;
            temperatureMoteur += 2;
        }
        else{
            huileMoteur -= 1;
            temperatureMoteur += 3;
        };

        // Pneus
        if (traction == 1) {
            usurePneusAvant += 10;
            usurePneusArriere += 5;
        }
        else if (propulsion == 1) {
            usurePneusAvant += 5;
            usurePneusArriere += 10;
        }
        else if (quatreRouesMotrices == 1) {
            usurePneusArriere += 7;
            usurePneusAvant += 7;
        };

        pressionPneusAvant -= 2;
        pressionPneusArriere -= 2;

        // Freins
        if ((pressionPneusArriere+pressionPneusAvant)/2 <= 50) {
            usureFreins -= (nombreVirageDroite+nombreVirageGauche)*0.90; // si les pneus sont sous-gonflés, les freins s'usent + vite
            vitess_max = 300; //TODO : utiliser la vitesse max dans les calculs
        }
        else {
            usureFreins += (nombreVirageDroite + nombreVirageGauche) * 0.5; // nombre de virages influe sur l'usure des freins
        }

        // Cremaillère
        if(usureCremaillere >= 75){
            usureCremaillere += 10; // si elle est très usée, elle s'use encore plus vite
        }
        else {usureCremaillere += (nombreVirageGauche+nombreVirageDroite)*0.75;} // nombre de virages influe sur la crémaillère

        // Boite de vitesse
        usureBoiteVitesse += 10/boiteVitesses; // Plus on a de vitesses, moins notre boite de vitesse s'use vite
    }

    void afficheTexteStat(){
        Colors colors;

        cout<< colors.blue << "\n *** Statistiques de " << nomVoiture << " : ***" << colors.close <<endl;
        cout<< colors.black << "    Type : " << typeVoiture << colors.close <<endl;
        cout<< "    Carburant :          ";
        affichageDiagrameStat("d", essence);
        cout<< "\n    Pneus avant: ";
        cout<< "\n         - Usure :       ";
        affichageDiagrameStat("c", usurePneusAvant);
        cout<< "\n         - Pression :    ";
        affichageDiagrameStat("d", pressionPneusAvant);
        cout<< "\n    Pneus arrière : ";
        cout<< "\n         - Usure :       ";
        affichageDiagrameStat("c", usurePneusArriere);
        cout<< "\n         - Pression :    ";
        affichageDiagrameStat("d", pressionPneusArriere);
        cout<< "\n    Temperature moteur : ";
        affichageDiagrameStat("c", temperatureMoteur);
        cout<< "\n    Niveau d'huile :     ";
        affichageDiagrameStat("d", huileMoteur);
        cout<< "\n    Freins :             ";
        affichageDiagrameStat("c", usureFreins);
        cout<< "\n    Cremaillère :        ";
        affichageDiagrameStat("c", usureCremaillere);
        cout<< "\n    Boite de Vitesses :  ";
        affichageDiagrameStat("c", usureBoiteVitesse);
    }

    void ajustement(){
        Colors colors;
        int aChanger;

        cout<< colors.yellow << "\n == AJUSTEMENT DE " << nomVoiture << " ==" << colors.close <<endl;
        cout<< "0. Exit \n 1. Faire le plein d'essence \n 2. Remettre de l'huile dans le moteur \n 3. Regonfler les pneus avants (+20%)\n 4. Regonfler les pneus arrières (+20%) \n 5. Changer les freins \n 6. Changer les pneus avants \n 7. Changer les pneus arrières \n 8. Faire refroidir le moteur \n 9. Renover la crémaillère (-25%) \n 10. Renover la boite de vitesses (-25%)"<<endl;
        cin>> aChanger;

        consoleClear();
        cout<< colors.green << nomVoiture << " : " << colors.close;
        switch(aChanger){
            case 0 :
                break;
            case 1 :
                essence = 100;
                cout<< colors.green << "Vous avez fait le plein !" << colors.close <<endl;
                break;
            case 2 :
                huileMoteur = 100;
                cout<< colors.green << "Votre niveau d'huile moteur est parfait !" << colors.close <<endl;
                break;
            case 3 :
                pressionPneusAvant += 20;
                cout<< colors.green << "La pression de vos pneus avant est maintenant de " << pressionPneusAvant << "%." << colors.close <<endl;
                break;
            case 4 :
                pressionPneusArriere += 20;
                cout<< colors.green << "La pression de vos pneus arrière est maintenant de " << pressionPneusArriere << "%." << colors.close <<endl;
                break;
            case 5 :
                usureFreins = 5;
                cout<< colors.green << "Vos freins sont comme neufs !" << colors.close <<endl;
                break;
            case 6 :
                usurePneusAvant = 5;
                cout << colors.green << "Vos pneus avant sont neufs !" << colors.close <<endl;
                break;
            case 7 :
                usurePneusArriere = 5;
                cout << colors.green << "Vos pneus arrières sont neufs !";
                break;
            case 8 :
                temperatureMoteur -= 50;
                cout<< colors.green << "La température du moteur est de " << temperatureMoteur << "%." << colors.close << endl;
                break;
            case 9 :
                usureCremaillere -= 25;
                cout<< colors.green << "Votre crémaillère est usée à " << usureCremaillere << "%." << colors.close <<endl;
                break;
            case 10 :
                usureBoiteVitesse -= 25;
                cout<< colors.green << "Votre boite de vitesses est usée à " << usureBoiteVitesse << "%." << colors.close <<endl;
                break;
        }
    };

    void verifications(){
        Colors colors;

        if (essence <= 0) { cout<< colors.red << "C'est la panne sèche pour " << nomVoiture << " ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (huileMoteur <= 0) { cout<< colors.red <<"Le moteur a cassé sur " << nomVoiture << " ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (temperatureMoteur >= 100) { cout<< colors.red << "Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (usureBoiteVitesse >= 100) { cout<< colors.red << "La boite de vitesse de" << nomVoiture << "  est morte ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (usureCremaillere >= 100) { cout<< colors.red << "La cremaillère de " << nomVoiture << "  est trop usée ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (usureFreins >= 100) { cout<< colors.red <<"Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (pressionPneusArriere >= 100 && propulsion == 1) { cout<< colors.red << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus arrière sont à plat ! C'est une propulsion ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (pressionPneusAvant >= 100 && traction == 1) { cout<< colors.red <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus avant sont à plat ! C'est une traction ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (pressionPneusAvant >= 100 && pressionPneusArriere >= 100) { cout<< colors.red <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus sont tous à plat ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
        if (usurePneusAvant >= 100 && usurePneusArriere >= 100) { cout<< colors.red <<"Les pneus de " << nomVoiture << " sont tous trop usés ! Elle quitte la course..." << colors.close <<endl; alive = 0;}
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
    cout<< colors.yellow << "== CREATION DES VOITURES ==" << colors.close <<endl;
    cout<< colors.blue << "*** PREMIERE VOITURE ***" << colors.close <<endl;
    cout<< "Choisissez le nom de la voiture : Voiture1" <<endl;
    //cin>> nom_voiture_1;
    cout<< "Choisissez le nombre de vitesse : 6 " <<endl;
    //cin>> nombre_vitesses_1;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : 1" <<endl;
    //cin>> type_1;
    nom_voiture_1 = "Voiture1";
    nombre_vitesses_1 = 6;
    type_1 = 1;

    cout<< colors.blue << "*** DEUXIEME VOITURE ***" << colors.close <<endl;
    cout<< "Choisissez le nom de la voiture : Voitre2" <<endl;
    //cin>> nom_voiture_2;
    cout<< "Choisissez le nombre de vitesse : 5 " <<endl;
    //cin>> nombre_vitesses_2;
    cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : 3" <<endl;
    //cin>> type_2;
    nom_voiture_2 = "Voiture2";
    nombre_vitesses_2 = 5;
    type_2 = 3;

    Voiture voiture1, voiture2;

    voiture1.creationVoiture(nom_voiture_1, nombre_vitesses_1, type_1);
    voiture2.creationVoiture(nom_voiture_2, nombre_vitesses_2, type_2);

    consoleClear();

    // DEBUT DES TOURS
    for (int i = 1; i <= 10 ; i++) {
        cout<< colors.cyan << "\n == TOUR "<< i << " ==" << colors.close <<endl;

        // Changement des différents éléments de la voiture suite au premier tour et affichage des stats
        if (voiture1.alive == 1){voiture1.update();
            voiture1.afficheTexteStat(); voiture1.verifications();}
        if (voiture2.alive == 1){voiture2.update();
            voiture2.afficheTexteStat(); voiture2.verifications();}
        // Vérification qu'on a pas perdu
        if(voiture1.alive == 0 && voiture2.alive == 0) {nombreTours = i; break;}

        // Changement d'informations par l'utilisateur
        cout<< colors.magenta <<"Souhaitez-vous effectuer un ajustement sur une voiture ? [O/N]" << colors.close <<endl;
        cin >> ajustement;
        if(ajustement == "O" || ajustement == "o" || ajustement == "0"){
            cout<< colors.red << "ATTENTION : Vous ne pouvez effectuer qu'une action par tour, et sur une seule voiture ! Choisissez sagement ;-)" << colors.close <<endl;
            cout<< "Sur quelle voiture ?" <<endl;
            cout<< "0. Exit" <<endl;
            if(voiture1.alive == 1){ cout<< "1. " << voiture1.nomVoiture <<endl;};
            if(voiture2.alive == 1){ cout<< "2. " << voiture2.nomVoiture <<endl;};
            cin >> ajustementAFaire;

            if(ajustementAFaire == 1) {consoleClear();
                voiture1.afficheTexteStat(); voiture1.ajustement();}
            else if(ajustementAFaire == 2) {consoleClear();
                voiture2.afficheTexteStat(); voiture2.ajustement();}
            else {continue;};
        }
        else{
            consoleClear();
        }
    }
    cout<< colors.yellow << "== END OF GAME ==" <<colors.close <<endl;
    finDuJeu(voiture1.alive, voiture2.alive, nombreTours);

    return 0;
}
