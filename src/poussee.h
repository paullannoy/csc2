/**
 * **************************************************
 * **************************************************
 *   _____ _____  ______   _
 *  / ____|  __ \|  ____| | |
 * | |    | |__) | |__    | |    _   _  ___  _ __
 * | |    |  ___/|  __|   | |   | | | |/ _ \| '_ \
 * | |____| |    | |____  | |___| |_| | (_) | | | |
 *  \_____|_|    |______| |______\__, |\___/|_| |_|
 *                                __/ |
 *                               |___/
 * **************************************************
 * **************************************************
 *
 * Role general de ce fichier
 * --------------------------------------------------------------
 * Une poussee
 * Role des fonctions et note d'implementation
 * --------------------------------------------------------------
 *
 * --------------------------------------------------------------
 *
 *
 */

#ifndef POUSSEE_H
#define POUSSEE_H

#include "plateau_siam.h"
#include "coup_jeu.h"
#include "piece_siam.h"


/**
* Fonction poussee_etre_valide:
* *****************************
*   Verifie si il est possible de realiser une poussee qui debute
*   aux coordonnees(x,y) dans l'orientation définie.
*   Note : Les coordonnées (x,y) designent la premiere piece rencontree
*   dans la poussee (et non pas les coordonnees de la piece a l'origine
*   de la poussee).
*
* Necessite :
*   - Un pointeur non NULL vers un plateau intègre non modifiable.
*   - Deux coordonnees entieres (x,y) designant une piece non
* vides integres du tableau.
*   - Une orientation de poussee designant une direction integre.
*
* Garantie :
*   - Un retour valant 1 si la poussee est possible
*   - Un retour valant 0 sinon
*
* */
int poussee_etre_valide(plateau_siam* plateau,int x, int y, orientation_deplacement orientation);

/**
* Fonction pousse_realiser:
* *****************************
*   Realise une poussee sur un plateau en supposant que celle-ci
*   est realisable (et non pas les coordonnees de la piece a l'origine
*   de la poussee)
*
* Necessite :
*   - Un pointeur non NULL vers un plateau intègre non modifiable.
*   - Deux coordonnees entieres (x,y) designant une piece non
* vides integres du tableau.
*   - Un type d'animal a deplacer.
*   - Une orientation de poussee designant une direction integre.
*   - Un pointeur non NULL vers une condition de victoire modifiable.
* Garantie :
*   - Un plateau integre mis a jour en ayant realise la poussee.
*
* */
void poussee_realiser(plateau_siam* plateau,int x, int y, orientation_deplacement orientation, type_piece type, coup_jeu* coup);



int poussee_calculer_longueur(plateau_siam* plateau, int x, int y, orientation_deplacement orientation);


int poussee_calculer_force(plateau_siam* plateau, int x, int y, orientation_deplacement orientation);



#endif
