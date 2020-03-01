#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////// AFFICHAGE //////////////////////////////////////////////////////
class Colors {
public:
    // Couleurs de texte
    const string black = "\033[1;30m";
    const string red = "\033[1;31m";
    const string green = "\033[1;32m";
    const string yellow = "\033[1;33m";
    const string blue = "\033[1;34m";
    const string magenta = "\033[1;35m";

    // Couleur de surlignage
    const string backWhite = "\033[1;47m";
    const string backRed = "\033[1;41m";
    const string backGreen = "\033[1;42m";
    const string backYellow = "\033[1;43m";

    // Balise de fermeture
    const string close = "\033[0m";
};

void consoleClear() {
    cout<< string( 100, '\n' );
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
    else if (type=="temp"){
        if (n > 40 && n < 70){color1 = colors.backGreen; color2 = colors.close;}
        else if(n >= 80 || n <= 30) {color1 = colors.backRed; color2 = colors.close;}
        else{color1 = colors.backYellow; color2 = colors.close;}
    }
    else if (type=="pp"){
        if (n > 40 && n < 70){color1 = colors.backGreen; color2 = colors.close;}
        else if(n >= 80 || n <= 30) {color1 = colors.backRed; color2 = colors.close;}
        else{color1 = colors.backYellow; color2 = colors.close;}
    }

    cout << color1 << string(n, ' ') << color2;
    cout << colors.backWhite << string(100-n, ' ') << colors.close << "   " << n << "%"<<endl;
};

void affichageProgression(int n){
    Colors colors;

    cout<< colors.backGreen << string(n, ' ') << colors.close;
    cout<< colors.backWhite << string(50-n, ' ') << colors.close <<endl;
};

/////////////////////////////////////////////////////// JEU ////////////////////////////////////////////////////////////
bool check(string type, int value){
    Colors colors;

    if(type == "boite_vitesse") {
        if(value <= 6 && value > 0) {return true;} else {cout<< "Choisissez le nombre de vitesses de la boite de vitesses : " <<endl; return false;};
    }
    else if (type == "type_voiture") {
        if(value > 0 && value <= 3) {return true;} else {cout<< "Types : \n 1. Propulsion \n 2. Traction \n 3. Quatre roues motrices \n Choisissez le type de la voiture : " <<endl; return false;}
    }
    else if (type == "vitesse_droit") {
        if(value <= 323 && value > 0) {return true;} else {cout<< colors.magenta << "Vitesse dans les lignes droites : " << colors.close; return false;}
    }
    else if (type == "vitesse_virage") {
        if(value <= 323 && value > 0) {return true;} else {cout<< colors.magenta << "Vitesse dans les virages : " << colors.close; return false;}
    }
    else if (type == "direction") {
        if(value > 0 && value <= 100) {return true;} else {cout<< colors.magenta << "Paramétrage de la direction : " << colors.close; return false;}
    }
    else if (type == "one_or_two") {
        if (value > 0 && value <=3) {return true;} else {cout<< "Sur quelle voiture ?" <<endl; return false; }
    }
//    else if (type == "yes_or_no") {
//        if (to_string(value) == "O" || to_string(value) == "o" || to_string(value) == "0" || to_string(value) == "N") { return true;} else {cout<< "O/N" <<endl; return false;}
//    }
    return false;
};

void finDuJeu(bool alive1, bool alive2, int nombreTours){
    Colors colors;

    consoleClear();

    if(alive1 && alive2 && nombreTours >= 50) {cout<< colors.green << "Votre victoire est totale ! Vous avez réussit à maintenair vos deux voitures pendant 50 tours !" << colors.close <<endl;}
    else if((alive1 || alive2) && nombreTours >= 50) {cout<< colors.yellow << "Votre victoire est partielle ! Vous avez réussit à maintenair vos une voiture sur les deux pendant 50 tours !" << colors.close <<endl;}
    else if((alive1 && not alive2) && nombreTours >= 50) {cout<< colors.red << "Vous avez perdu... Vous avez tenu " << nombreTours << " tours ! Vous pouvez toujours retenter votre chance !" << colors.close <<endl;}
    else { cout<< "Unexpected end of game" <<endl;};
}

////////////////////////////////////////////////////// CLASSES /////////////////////////////////////////////////////////
class Circuit {
public:
    // ATTRIBUTS
    const int nombreTotalVoitures = 22;
    const float tailleTour = 5.371; // en km
    const int nombreVirageGauche = 5;
    const int nombreVirageDroite = 4;
};

class Voiture {
public:
    Circuit circuit;
    Colors colors;

    ///////////////////////////////////////////////// ATTRIBUTS/////////////////////////////////////////////////////////
    // Constantes
    const int poidsVoiture = 735; // kg

    // Choix de l'utilisateur
    string nomVoiture;
    string typeVoiture; // propulsion, traction ou 4x4
    bool propulsion = false;
    bool traction = false;
    bool quatreRouesMotrices = false;
    int nombreVitesses;

    // Update à chaque tour
    bool alive = true;
    bool accident = false;

    int vitesseDroit = 0; // en km/h
    int vitesseVirage = 0; // en km/h

    int temperatureMoteur = 50; // en %
    int niveauEssence = 100; // en %

    int pressionPneusAvant = 60; // en %
    int pressionPneusArriere = 60; // en %
    int usurePneusAvant = 5; // en %
    int usurePneusArriere = 5; // en %

    int usureFreins = 5; // en %
    int dureteDirection = 0; // en %

    ///////////////////////////////////////////////////  METHODES //////////////////////////////////////////////////////
    void creationVoiture(string nom, int boiteVitesse, int type) {
        nombreVitesses = boiteVitesse;
        nomVoiture = nom;

        switch (type) {
            case 1 :
                propulsion = true;
                typeVoiture = "propulsion";
                break;
            case 2 :
                traction = true;
                typeVoiture = "traction";
                break;
            case 3 :
                quatreRouesMotrices = true;
                typeVoiture = "quatre roues motrices";
                break;
        }
    }

    void update() {
        // Variables
        float poidsTotal = poidsVoiture + 0.755*(niveauEssence*120)/100; // poids de la voiture + niveau d'niveauEssence * poids de l'niveauEssence (0.755kg/L)
        int freinage = vitesseDroit - vitesseVirage;

        // Essence
        niveauEssence -= (((circuit.tailleTour + poidsTotal * 0.01)*45/100)*100)/120; // consomation d'niveauEssence de 45L/100km, avec une légère influence du poids de la voiture, ramenée sur 100

        // Pneus
        if (traction) {
            usurePneusArriere += 5;
            if (pressionPneusAvant < 20){ // pas assez gonflé
                usurePneusAvant += 20;
            }
            else if (pressionPneusAvant > 90) { // trop gonflé
                if (vitesseVirage > 300){
                    accident = true;
                }
                else if (vitesseVirage > 250 && dureteDirection > 80){
                    accident = true;
                }
            }
            else {
                usurePneusAvant += 10;
            };
        }
        else if (propulsion){
            usurePneusAvant += 5;
            if (pressionPneusArriere < 20){ // pas assez gonflé
                usurePneusArriere += 20;
            }
            else if (pressionPneusArriere > 90) { // trop gonflé
                if (vitesseVirage > 300){
                    accident = true;
                }
                else if (vitesseVirage > 250 && dureteDirection > 80){
                    accident = true;
                }
            }
            else {
                usurePneusArriere += 10;
            };
        }
        else if (quatreRouesMotrices) {
            if (pressionPneusArriere < 20 ){ // pas assez gonflé
                usurePneusArriere += 15;
            }
            else if (pressionPneusArriere > 90) { // trop gonflé
                if (vitesseVirage > 300){
                    accident = true;
                }
                else if (vitesseVirage > 250 && dureteDirection > 80){
                    accident = true;
                }
            }
            else {
                usurePneusArriere += 7;
            };
            if (pressionPneusAvant < 20){ // pas assez gonflé
                usurePneusAvant += 15;
            }
            else if (pressionPneusAvant > 90) { // trop gonflé
                if (vitesseVirage > 300){
                    accident = true;
                }
                else if (vitesseVirage > 250 && dureteDirection > 80){
                    accident = true;
                }
            }
            else {
                usurePneusAvant += 7;
            };
        }

        pressionPneusArriere -= 2;
        pressionPneusAvant -= 2;

        // Freins
        if (freinage > 300) {
            usureFreins += 50;
        }
        else if (freinage > 200){
            usureFreins += 20;
        }
        else if (freinage > 100) {
            usureFreins += 10;
        };

        // Direction
        if (dureteDirection > 95){accident = true;}; // si la direction est trop dure
        if (dureteDirection < 20){accident = true;}; // si la direction est trop rapide

        // Vitesse
        if (vitesseVirage >= 250){accident = true;}; // si on roule trop vite dans un virage
        if (vitesseDroit > 300) {
            if (dureteDirection > 80) {accident = true;} // si on roule trop vite avec une direction trop dure
            else if (dureteDirection < 30) {accident = true;} // si on roule trop vite avec une direction trop rapide
        }

        // Moteur
        if (temperatureMoteur > 60) {
            temperatureMoteur += 1;
        }
        else if (temperatureMoteur > 40){
            temperatureMoteur += 3;
        }
        else if (temperatureMoteur > 30){
            temperatureMoteur += 5;
        }
        else if (temperatureMoteur > 20){
            temperatureMoteur += 7;
        }
        else if (temperatureMoteur <= 20){
            temperatureMoteur += 10;
        };

        // Mise à 0 des valeurs négatives pour ne pas avoir d'erreur d'affichage
        if (temperatureMoteur < 0) {temperatureMoteur = 0;};
        if (pressionPneusArriere < 0) {pressionPneusArriere = 0;};
        if (pressionPneusAvant < 0) {pressionPneusAvant = 0;};
        if (usurePneusAvant < 0) {usurePneusAvant = 0;};
        if (usurePneusArriere < 0) {usurePneusArriere = 0;};
        if (usureFreins < 0) {usureFreins = 0;};
        if (niveauEssence < 0) {niveauEssence = 0;};
        if (temperatureMoteur < 0) {temperatureMoteur = 0;};
    }

    void ajustement(){
        int aChanger;

        cout<< colors.yellow << "\n == AJUSTEMENT DE " << nomVoiture << " ==" << colors.close <<endl;
        cout<< "0. Exit \n 1. Faire le plein d'essence "
               "\n 2. Faire refroidir le moteur (-50%)"
               "\n 3. Regonfler les pneus avants (+20%)"
               "\n 4. Regonfler les pneus arrières (+20%) "
               "\n 5. Changer les freins "
               "\n 6. Changer les pneus avants "
               "\n 7. Changer les pneus arrières "<<endl;
        cin>> aChanger;

        consoleClear();

        cout<< colors.green << nomVoiture << " : " << colors.close;
        switch(aChanger){
            case 0 :
                break;
            case 1 :
                niveauEssence = 100;
                cout<< colors.green << "Vous avez fait le plein !" << colors.close <<endl;
                break;
            case 2 :
                temperatureMoteur -= 50;
                cout<< colors.green << "La température du moteur est de " << temperatureMoteur << "%." << colors.close << endl;
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
        }
    };

    void changementParamCourse(){
        // Remise à 0 des valeurs qu'on va changer
        vitesseVirage = 0;
        vitesseDroit = 0;
        dureteDirection = 0;

        // Changement des valeurs
        cout<< colors.blue << "*** PARAMETRES DE COURSE DE " << nomVoiture << " ***" << colors.close <<endl;
        while (not check("vitesse_droit",vitesseDroit)) {cin>> vitesseDroit;}
        while (not check("vitesse_virage",vitesseVirage)) {cin>> vitesseVirage;}
        while (not check("direction",dureteDirection)) {cin>> dureteDirection;}
    };

    void verifications(){
        // Si on a eut un accident
        if (accident) {
            cout << colors.red
                << "La voiture " << nomVoiture
                << " a eut un accident ! Elle quitte la course..."
                << colors.close << endl;
            alive = false;};

        // Si il n'y a plus d'essence
        if (niveauEssence <= 0) {
            cout << colors.red
                << "C'est la panne sèche pour " << nomVoiture << " ! Elle quitte la course..."
                << colors.close << endl;
            alive = false;};

        // Si le moteur est trop chaud
        if (temperatureMoteur >= 100) {
            cout<< colors.red
                << "Surchauffe du moteur pour " << nomVoiture << " ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};

        // Si les freins sont trop usés
        if (usureFreins >= 100) {
            cout<< colors.red
                <<"Les freins de " << nomVoiture << "  sont HS ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};

        // Si les pneus sont à plat
        if (pressionPneusAvant <= 0 || pressionPneusArriere <= 0) {
            cout<< colors.red
                << "Les pneus de " << nomVoiture << "sont à plat ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;
        };

        // Si les pneus arrières sont trop sous gonflés sur une propulsion
        if (pressionPneusArriere <= 10 && propulsion) {
            cout<< colors.red
                << "Compliqué pour " << nomVoiture << " de rouler alors que ses pneus arrière sont sous-gonflés ! "
                                                      "C'est une propulsion ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};

        // Si les pneus avants sont trop sous glonflés sur un traction
        if (pressionPneusAvant <= 10 && traction) {
            cout<< colors.red
                <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus avant sont sous-gonflés ! "
                                                     "C'est une traction ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};

        // Si tous les pneus sont sous gonflés sur un 4x4
        if (pressionPneusAvant <= 10 && pressionPneusArriere <= 10) {
            cout<< colors.red
                <<"Compliqué pour " << nomVoiture << " de rouler alors que ses pneus sont sous-gonflés! "
                                                     "Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};

        // Si les pneus sont trop usés
        if (usurePneusAvant >= 100 && usurePneusArriere >= 100) {
            cout<< colors.red
                <<"Les pneus de " << nomVoiture << " sont tous trop usés ! Elle quitte la course..."
                << colors.close <<endl;
            alive = false;};
    };

    void afficheTexteStat(){
        cout<< colors.blue << "\n *** Statistiques de " << nomVoiture << " : ***" << colors.close <<endl;
        cout<< colors.black << "    Type : " << typeVoiture << colors.close <<endl;
        cout<< "    Carburant :          ";
        affichageDiagrameStat("d", niveauEssence);
        cout<< "\n    Pneus avant: ";
        cout<< "\n         - Usure :       ";
        affichageDiagrameStat("c", usurePneusAvant);
        cout<< "\n         - Pression :    ";
        affichageDiagrameStat("pp", pressionPneusAvant);
        cout<< "\n    Pneus arrière : ";
        cout<< "\n         - Usure :       ";
        affichageDiagrameStat("c", usurePneusArriere);
        cout<< "\n         - Pression :    ";
        affichageDiagrameStat("pp", pressionPneusArriere);
        cout<< "\n    Temperature moteur : ";
        affichageDiagrameStat("temp", temperatureMoteur);
        cout<< "\n    Freins :             ";
        affichageDiagrameStat("c", usureFreins);
    }

    void affichageParamCourse(){
        cout << colors.blue << "*** Paramètres de course actuels de " << nomVoiture << " ***" << colors.close <<endl;
        cout<< "    - Vitesse en ligne droite : " << vitesseDroit << " km/h" <<endl;
        cout<< "    - Vitesse dans les virages : " << vitesseVirage << " km/h" <<endl;
        cout<< "    - Direction : " << dureteDirection << "%" <<endl;
    }
};

////////////////////////////////////////////////////// MAIN ////////////////////////////////////////////////////////////
int main() {
    // VARIABLES
    Colors colors;

    // Pour la creation des voitures
    string nomVoiture1;
    string nomVoiture2;
    int nombreVitesses1 = 0;
    int nombreVitesses2 = 0;
    int type1 = 0;
    int type2 = 0;

    // Pour les paramètres de conduite
    string paramConduiteV1 = "nothing yet";
    string paramConduiteV2 = "nothing yet";

    // Pour les ajustements
    string ajustement;
    int ajustementAFaire;

    // Pour le jeu
    int nombreTours = 50;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATION DES VOITURES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Saisie des variables par l'utilisateur
    cout<< colors.yellow << "== CREATION DES VOITURES ==" << colors.close <<endl;
    cout<< colors.blue << "*** Première voiture ***" << colors.close <<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin >> nomVoiture1;
    while (not check("boite_vitesse", nombreVitesses1)) {cin >> nombreVitesses1;}
    while (not check("type_voiture", type1)){cin >> type1;}

    cout<< colors.blue << "*** Deuxième voiture ***" << colors.close <<endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin >> nomVoiture2;
    while (not check("boite_vitesse", nombreVitesses2)) {cin >> nombreVitesses2;}
    while (not check("type_voiture", type2)){cin >> type2;}

    // Création des objets
    Voiture voiture1, voiture2;

    // Configuration des objets avec les variables de l'utilisateur
    voiture1.creationVoiture(nomVoiture1, nombreVitesses1, type1);
    voiture2.creationVoiture(nomVoiture2, nombreVitesses2, type2);

    consoleClear();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // DEBUT DES TOURS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int i = 1; i <= 50 ; i++) {
        // Affichage du numéro du tour et de la progression dans la course (but => 50 tours)
        cout<< colors.yellow << "\n == TOUR "<< i << " ==" << colors.close <<endl;
        affichageProgression(i);

        // SI C'EST LE PREMIER TOUR : Saisie des paramètres de course des voiture
        if (i == 1) {
            voiture1.changementParamCourse();
            voiture2.changementParamCourse();
        };

        // SI C'EST PAS LE PREMIER TOUR : Affichage et potentiel changement des paramètres de course des voitures
        if (i > 1) {
            if (voiture1.alive) {
                voiture1.affichageParamCourse();
                cout<< colors.magenta
                    <<"Souhaitez-vous changer les vitesses et/ou la direction par rapport au tour précedent pour "
                    << voiture1.nomVoiture
                    << " ? [O/N]"
                    << colors.close <<endl;
                cin>> paramConduiteV1;

                if (paramConduiteV1 == "O" || paramConduiteV1 == "o" || paramConduiteV1 == "0") {
                    voiture1.changementParamCourse();
                }
            };

            if (voiture2.alive) {
                voiture2.affichageParamCourse();
                cout << colors.magenta
                     << "Souhaitez-vous changer les vitesses et/ou la direction par rapport au tour précedent pour "
                     << voiture2.nomVoiture
                     << " ? [O/N]"
                     << colors.close << endl;
                cin >> paramConduiteV2;

                if (paramConduiteV2 == "O" || paramConduiteV2 == "o" || paramConduiteV2 == "0") {
                    voiture2.changementParamCourse();
                }
            };
        };

        consoleClear();

        // Changement des différents éléments de la voiture suite au tour
        if (voiture1.alive){
            voiture1.update();
            voiture1.verifications();
        }
        if (voiture2.alive){
            voiture2.update();
            voiture2.verifications();
        }

        // Vérification qu'on a pas perdu les deux voitures
        if( not voiture1.alive && not voiture2.alive) {nombreTours = i; break;}

        // Affichage des stats
        if (voiture1.alive) {voiture1.afficheTexteStat();};
        if (voiture2.alive) {voiture2.afficheTexteStat();};

        // Ajustements par l'utilisateur
        cout<< colors.magenta <<"Souhaitez-vous effectuer un ajustement sur une voiture ? [O/N]" << colors.close <<endl;
        cin >> ajustement;

        if(ajustement == "O" || ajustement == "o" || ajustement == "0"){
            cout<< colors.red << "ATTENTION : Vous ne pouvez effectuer qu'une action par tour, et sur une seule voiture ! Choisissez sagement ;-)" << colors.close <<endl;
            if(voiture1.alive){ cout<< "1. " << voiture1.nomVoiture <<endl;};
            if(voiture2.alive){ cout<< "2. " << voiture2.nomVoiture <<endl;};
            cout<< "3. Exit" <<endl;
            while (not check("one_or_two", ajustementAFaire)) {cin >> ajustementAFaire;};

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

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FIN DU JEU
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout<< colors.yellow << "== END OF GAME ==" <<colors.close <<endl;
    finDuJeu(voiture1.alive, voiture2.alive, nombreTours);

    return 0;
}
