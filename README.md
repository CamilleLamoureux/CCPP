*Langue : français (France)*

# Jeu de gestion de voitures de course

## Règles 

### But du jeu
Vous possédez deux voitures de course. Votre but est de faire en sorte qu'elles complètent 50 tours 
de piste.

*NB : Vous ne cherchez pas à finir premier.*

**UPDATE**, nouvelle fonctionnalité : vous pouvez choisir le nombre de tours nécessaires pour gagner.

### Présentation des éléments
#### La piste

La piste fait 5km et 371m et possède 9 virages (5 à gauche et 4 à droite).

#### Les voitures de course
Les voitures ont un réservoir de 120L d'essence.

Au début de la partie, vous pourrez choisir entre **3 types de voiture** :
- Propulsion
- Traction
- Quatre roues motrices

Vous pourrez aussi choisir **un nom** (qui ne servira qu'à identifier la voiture) ainsi que le **nombre 
de rapports** de votre boite de vitesses. 

*NB : Ces paramètres auront un réel impact sur les statistiques de votre voiture durant la partie (consommation
d'essence, usure des pneus, etc... Choisissez les bien !)*

### Déroulement d'un tour
1. Au début de chaque tour, vous pourrez choisir différents paramètres pour le tour à venir :
    - La vitesse que la voiture prendra dans les lignes droites
    - La vitesse que la voiture prendra dans les virages
    
2. Vous pourrez ensuite voir les statiques de vos voitures encore dans la course et choisir **un ajustement** à faire. Celui ci pourra 
vous permettre d'agir sur une des statistiques d'une de vos voitures :
    - La température du moteur
    - Le niveau d'essence
    - La pression des pneus, avant ou arrière
    - L'usure des pneus, avant ou arrière
    - L'usure des freins
    
    *NB : vous ne pourrez faire qu'un unique ajustement par tour, et sur une seule voiture !*
   
3. Le tour va ensuite être simulé par le jeu. Les statistiques de vos voitures seront mises à jour.
Vous serez notifié en cas de perte d'une ou plusieurs voitures

### Perdre une voiture
Vous pouvez perdre vos deux voitures dans le même tour.

Vous pouvez perdre une voiture selon deux motifs :
- **Un accident pendant le tour** : si votre vitesse n'était pas adapté, par exemple
- **Une panne** pour différents motifs : cela arrivera si vos ajustements ne sont pas bons. 
(*Exemples de pannes : Pneus crevés, panne d'essence, freins trop usés, etc...*)


### Fin du jeu
**Vous gagnez** si vous arrivez à conserver 2 voitures pendant la totalité des tours.

**Vous perdez** si vos deux voitures sont hors courses avant la fin des tours.

*NB : vous pouvez avoir une "victoire partielle" si vous conservez une voiture sur les deux pendant la totalité des tours.*


## Informations techniques
Language utilisé : C++

Codé sous Linux à l'origine.

Version de compatibilité Windows disponible, avec des graphiques moins poussés.
