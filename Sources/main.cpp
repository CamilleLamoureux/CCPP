#include <iostream>
#include <string>
#include "../Headers/Display.h"
#include "../Headers/Game.h"
#include "../Headers/Car.h"

using namespace std;

int main() {
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
    int ajustementAFaire = 0;

    // Pour le jeu
    int nombreTours = 50;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CREATION DES VOITURES
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Saisie des variables par l'utilisateur
    cout << Display::yellow << "== CREATION DES VOITURES ==" << Display::close << endl;
    cout << Display::blue << "*** Première voiture ***" << Display::close << endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin >> nomVoiture1;
    while (not Game::check("boite_vitesse", nombreVitesses1)) {cin >> nombreVitesses1;}
    while (not Game::check("type_voiture", type1)){cin >> type1;}

    cout << Display::blue << "*** Deuxième voiture ***" << Display::close << endl;
    cout<< "Choisissez le nom de la voiture : " <<endl;
    cin >> nomVoiture2;
    while (not Game::check("boite_vitesse", nombreVitesses2)) {cin >> nombreVitesses2;}
    while (not Game::check("type_voiture", type2)){cin >> type2;}

    // Création des objets
    Car voiture1, voiture2;

    // Configuration des objets avec les variables de l'utilisateur
    voiture1.creationVoiture(nomVoiture1, nombreVitesses1, type1);
    voiture2.creationVoiture(nomVoiture2, nombreVitesses2, type2);

    Display::consoleClear();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // DEBUT DES TOURS
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int i = 1; i <= 50 ; i++) {
        cout << voiture1.alive << voiture2.alive <<endl;
        // Affichage du numéro du tour et de la progression dans la course (but => 50 tours)
        cout << Display::yellow << "\n == TOUR " << i << " ==" << Display::close << endl;
        Display::affichageProgression(i);

        // SI C'EST LE PREMIER TOUR : Saisie des paramètres de course des voiture
        if (i == 1) {
            voiture1.changementParamCourse();
            voiture2.changementParamCourse();
        }

        // SI C'EST PAS LE PREMIER TOUR : Affichage et potentiel changement des paramètres de course des voitures
        if (i > 1) {
            if (voiture1.alive) {
                voiture1.affichageParamCourse();
                cout << Display::magenta
                     << "Souhaitez-vous changer les vitesses et/ou la direction par rapport au tour précedent pour "
                     << voiture1.nomVoiture
                     << " ? [O/N]"
                     << Display::close << endl;
                cin>> paramConduiteV1;

                if (paramConduiteV1 == "O" || paramConduiteV1 == "o" || paramConduiteV1 == "0") {
                    voiture1.changementParamCourse();
                }
            }

            if (voiture2.alive) {
                voiture2.affichageParamCourse();
                cout << Display::magenta
                     << "Souhaitez-vous changer les vitesses et/ou la direction par rapport au tour précedent pour "
                     << voiture2.nomVoiture
                     << " ? [O/N]"
                     << Display::close << endl;
                cin >> paramConduiteV2;

                if (paramConduiteV2 == "O" || paramConduiteV2 == "o" || paramConduiteV2 == "0") {
                    voiture2.changementParamCourse();
                }
            }
        }

        Display::consoleClear();

        // Changement des différents éléments de la voiture suite au tour
        if (voiture1.alive){
            cout << "Change Voiture 1" <<endl;
            voiture1.update();
            voiture1.verifications();
        }
        if (voiture2.alive){
            cout << "Change Voiture 2" <<endl;
            voiture2.update();
            voiture2.verifications();
        }

        // Vérification qu'on a pas perdu les deux voitures
        if( not voiture1.alive && not voiture2.alive) {nombreTours = i; break;}

        // Affichage des stats
        if (voiture1.alive) {voiture1.afficheTexteStat();}
        if (voiture2.alive) {voiture2.afficheTexteStat();}

        // Ajustements par l'utilisateur
        cout << Display::magenta << "Souhaitez-vous effectuer un ajustement sur une voiture ? [O/N]" << Display::close << endl;
        cin >> ajustement;

        if(ajustement == "O" || ajustement == "o" || ajustement == "0"){
            cout << Display::red << "ATTENTION : Vous ne pouvez effectuer qu'une action par tour, et sur une seule voiture ! Choisissez sagement ;-)" << Display::close << endl;
            if(voiture1.alive){ cout<< "1. " << voiture1.nomVoiture <<endl;}
            if(voiture2.alive){ cout<< "2. " << voiture2.nomVoiture <<endl;}
            cout<< "3. Exit" <<endl;
            while (not Game::check("one_or_two", ajustementAFaire)) {cin >> ajustementAFaire;}

            if(ajustementAFaire == 1) {Display::consoleClear();
                voiture1.afficheTexteStat(); voiture1.ajustement();}
            else if(ajustementAFaire == 2) {Display::consoleClear();
                voiture2.afficheTexteStat(); voiture2.ajustement();}
            else {continue;}

            ajustementAFaire = 0;
        }
        else{
            Display::consoleClear();
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // FIN DU JEU
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    cout << Display::yellow << "== END OF GAME ==" << Display::close << endl;
    Game::finDuJeu(voiture1.alive, voiture2.alive, nombreTours);

    return 0;
}
