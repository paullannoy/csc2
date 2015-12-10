
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
 * Une piece du jeu de siam designe un piece possible du plateau.
 * Chaque piece est definie par un type ('elephant','rhinoceros',
 *   'rocher','case_vide'), ainsi que par l'orientation de la piece.
 * Un animal doit avoir une orientation de type 'gauche','droite',
 *   'haut','bas', alors qu'une case vide ou un rocher ne doivent
 *   pas avoir d'orientation.
 *
 * Role des fonctions et note d'implementation
 * --------------------------------------------------------------
 * Les fonctions de ces fichiers sont en mesure de manipuler
 *   une piece et de realiser des verifications avec les informations
 *   de type et d'orientation.
 *
 * Notion d'abstraction
 * --------------------------------------------------------------
 * Il n'y a pas de notion de positionnement ni de regles du jeu a
 *   ce niveau d'abstraction.
 * La piece correspond a un element fondamental du jeu que l'on
 *   viendra manipuler dans les niveaux d'abstractions plus eleves.
 *
 *
 */



#ifndef PIECE_SIAM_H
#define PIECE_SIAM_H


#include "type_piece.h"
#include "orientation_deplacement.h"


/** Une piece du jeu de siam est definie par son type et son
 *    orientation.
 */
typedef struct
{
    type_piece type; // elephant,rhinoceros,rocher,case_vide
    orientation_deplacement orientation; //haut,bas,gauche,droite,aucune_orientation

}piece_siam;


/**
 * Fonction appel_test_piece_siam :
 * *******************************
 * Appelle et lance toutes les fonctions de test de la classe 'piece_siam'
 */
void appel_test_piece_siam(void);

/**
 * Fonction piece_etre_integre:
 * *************************
 *    Verifie qu'une piece correspond a la definition donnee.
 *    Une piece est integre si:
 *     - Il s'agit d'un animal (elephant ou rhinoceros) et que
 *         son orientation vaut gauche,droite,haut ou bas.
 *     - Il s'agit d'un rocher ou d'une case vide et son orientation vaut
 *         aucune_orientation.
 *    Toute autre combinaison correspond a une piece non integre.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable.
 *    Garantie:
 *      - Un retour valant 1 si la piece correspond a la definition donnee.
 *      - Un retour valant 0 sinon.
 */
int piece_etre_integre(const piece_siam* piece);

/** Fonction de TEST piece_etre_integre
*
*   Fais les test pour la fonction piece_etre_integre
*   Pour les cas suivant:
*   - elephant haut
*   - elephant aucune_orientation
*   - rocher aucune_orientation
*   - case_vide haut
*/
void test_piece_etre_integre(void);

/**
 * Fonction piece_initialiser:
 * *************************
 *    Initialise une piece passee en argument avec des valeurs par defaut.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam modifiable.
 *    Garantie:
 *      - La piece est initialisee a une valeur integre.
 *
 */
void piece_initialiser(piece_siam* piece);



/**
 * Fonction piece_etre_animal:
 * *************************
 *    Verifie si une piece est un animal ou non.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable integre.
 *    Garantie:
 *      - Un retour valant 1 si la piece est un elephant ou un rhinoceros.
 *      - Un retour valant 0 sinon.
 */
int piece_etre_animal(const piece_siam* piece);

/** Fonction de TEST piece_etre_animal
*
*   Fais les test pour la fonction piece_etre_animal
*   Pour les cas suivant:
*   - elephant
*   - rhinoceros
*   - rocher
*   - case_vide
*/
void test_piece_etre_animal(void);

/**
 * Fonction piece_etre_rocher:
 * *************************
 *    Verifie si une piece est un rocher ou non.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable integre.
 *    Garantie:
 *      - Un retour valant 1 si la piece est un rocher.
 *      - Un retour valant 0 sinon.
 */
int piece_etre_rocher(const piece_siam* piece);

/** Fonction de TEST piece_etre_rocher
*
*   Fais les test pour la fonction piece_etre_rocher
*   Pour les cas suivant:
*   - elephant
*   - rhinoceros
*   - rocher
*   - case_vide
*/
void test_piece_etre_rocher(void);

/**
 * Fonction piece_etre_case_vide:
 * *************************
 *    Verifie si une piece est une case vide ou non.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable integre.
 *    Garantie:
 *      - Un retour valant 1 si la piece est une case vide.
 *      - Un retour valant 0 sinon.
 */
int piece_etre_case_vide(const piece_siam* piece);

/** Fonction de TEST piece_etre_case_vide
*
*   Fais les test pour la fonction piece_etre_case_vide
*   Pour les cas suivant:
*   - elephant
*   - rhinoceros
*   - rocher
*   - case_vide
*/
void test_piece_etre_case_vide(void);

/**
 * Fonction piece_definir:
 * *************************
 *    Definie les elements d'une piece directement a l'aide d'un
 *      type et d'une orientation.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam modifiable.
 *      - Un type integre.
 *      - Une orientation integre.
 *    Garantie:
 *      - Une piece mise a jour avec le nouveau type et orientation.
 *      - La piece doit etre integre.
 */
void piece_definir(piece_siam* piece,type_piece type,orientation_deplacement orientation);

/** Fonction de TEST piece_definir
*
*   Fais les test pour la fonction piece_definir
*   Pour les cas suivant:
*   - elephant haut
*   - rocher aucune_orientation
*   - rhinoceros bas
*/
void test_piece_definir(void);

/**
 *
 * Fonction piece_definir_rocher:
 * *******************************
 *    Definie une pièce comme étant un rocher en moidifiant son type et son orientation
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam modifiable.
 *    Garantie
 *      -La mise a jour de la piece en type rocher et de l'orientation en "aucune_orientation"
 *      -Une piece integre
 *
 */
void piece_definir_rocher(piece_siam* piece);

/**
 *
 * Fonction piece_definir_rocher:
 * *******************************
 *    Definie une pièce comme étant une case vide en moidifiant son type et son orientation
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam modifiable.
 *    Garantie
 *      -La mise a jour de la piece en type case_vide et de l'orientation en "aucune_orientation"
 *      -Une piece integre
 *
 */
void piece_definir_case_vide(piece_siam* piece);


/**
 * Fonction piece_recuperer_orientation_animal:
 * *************************
 *    Recupere l'orientation d'une piece designant un animal.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable.
 *      - La piece est integre et designe un animal.
 *    Garantie:
 *      - Une piece mise a jour est une case vide.
 *      - La piece est integre.
 */
orientation_deplacement piece_recuperer_orientation_animal(const piece_siam* piece);


/**
 * Fonction piece_afficher:
 * *************************
 *    Affiche de maniere lisible sur la console le type et l'orientation
 *      d'une piece.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable.
 *    Garantie:
 *      - Affichage sur la console de la piece.
 */
void piece_afficher(const piece_siam* piece);

/**
 * Fonction piece_afficher_nom_cours_debug:
 * *************************
 *    Affiche de maniere lisible sur la console le type et l'orientation
 *      d'une piece par une chaine de caractere courte.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une piece_siam non modifiable.
 *    Garantie:
 *      - Affichage sur la console de la piece par une chaine de
 *         caractere courte.
 */
void piece_afficher_nom_cours(const piece_siam* piece);

/**
 * Fonction piece_correspondre_nom_cours:
 * *************************
 *    Retourne une piece definie pour le type et l'orientation en fonction de la chaine
 *    de caractere reçue en entree.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une chaine de caractere non modifiable.
 *      - Une taille de la chaine egale a 3
 *    Garantie:
 *      - Le renvoie d'une piece integre de type et d'orientation
 *        correspondant a la chaine de caractere recue en entree
 */
piece_siam piece_correspondre_nom_cours(const char* nom_cours);



#endif
