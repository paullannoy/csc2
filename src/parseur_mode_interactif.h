
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
 *
 * Role general de ce fichier
 * --------------------------------------------------------------
 * Le parseur permet d'analyser une chaine de caractere et
 *  de traduire celle-ci en action a effectuer.
 * Ici, le parseur traduit la chaine de caractere recuperee
 *  de la ligne de commande pour determiner quelle action
 *  a realiser pour le jeu de siam.
 *
 * Role des fonctions et note d'implementation
 * --------------------------------------------------------------
 * Les fonctions proposee dans le mode interactifs permettent de
 *  demarer le controle du jeu en ligne de commande.
 * Les fonctions du mode interactif ont pour but de dialoguer avec
 *  un utilisateur (potentiellement non programmeur). Elles
 *  affichent donc les messages de dialogue avec l'utilisateur.
 * Le mode interactif vient egalement realiser la synchronisation
 *  des fonctions de gestion du jeu (demande d'action, realisation
 *  d'actions, affichage informatif, enregistrement et lecture
 *  a partir de fichiers et affichage du vainqueur).
 * Comme les fonctions traitent de demandent utilisateurs elles
 *  ne peuvent pas presuposer de contraintes de type "assertions"
 *  sur les variables completees interactivement.
 *
 *
 * Notion d'abstraction
 * --------------------------------------------------------------
 * Ce niveau d'abstraction a pour role de traiter des chaines de
 *  caractere et d'indiquer une action a realiser.
 * Les fonctions ne verifie que la syntaxe des chaines de caracteres
 *  mais n'ont pas pour vocation de verifier les actions du jeu.
 *
 */


#ifndef PARSEUR_MODE_INTERACTIF_H
#define PARSEUR_MODE_INTERACTIF_H


#include "orientation_deplacement.h"

typedef enum
{
    aucune_action,
    deplacement,
    introduction,
    changement_orientation,
    fin,
    initialisation,
    lecture_fichier
}
action_type;


#define MAX_LIGNE_COMMANDE 4096
#define MAX_NOM_FICHIER_TAILLE 256


typedef struct
{
    action_type type_action;

    char filename[MAX_NOM_FICHIER_TAILLE];

    int x_depart;
    int y_depart;

    orientation_deplacement deplacement;
    orientation_deplacement orientation;

}action_a_realiser;

/**
 * Fonction action_initialiser:
 * *************************
 *    Initialise l'action comme etant "aucune action"
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une action_type modifiable.
 *    Garantie:
 *      - l'action_realiser pointee a maintenant pour action_type aucune_action.
 */
void action_initialiser(action_a_realiser* action_a_initialiser);

/**
 * Fonction action_initialiser:
 * *************************
 *    Traduit la ligne de commande passee en entree en une action_type sur l'element pointe par le pointeur passe en entree.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers une action_type modifiable.
 *      - Une chaine de caractere non modifiable
 *    Garantie:
 *      - l'action a realiser pointee a pour type aucune_action si la chaine est vide, si la chaine est "fin" (3 manieres possibles, sensible a la casse), ou si un        
 *        parametre passe en entree n'est pas integre.
 *      - l'action a realiser pointee est de type introduction avec x, y et une orientation_deplacement integre si la chaine commence par "n "
 *      - l'action a realiser pointee est de type changement_orientation avec x, y et une orientation_deplacement integre et  si la chaine commence par "o "
 *      - l'action a realiser pointee est de type deplacement avec x, y, une orientation_deplacement (orientation) et une orientation_deplacement (direction) integre si la 
 *        chaine commence par "d "
 *      - l'action a realiser de type initialisation si la chaine est "i"
 *      - l'action a realiser avec un type lecture_fichier avec filename, le nom du fichier a ouvrir si la chaine commence par "lit "
 */
void ligne_de_commande_parser(const char* ligne_commande,action_a_realiser* action_demandee);


#endif
