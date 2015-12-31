
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
 * Le mode interactif permet d'interfacer le jeu de siam avec
 *  la commande d'utilisateur en ligne de commande.
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
 * Ce niveau d'abstraction a pour role de realiser l'interface entre
 *  une entree sous forme de demande utilisateur vers l'API du programme.
 * Le mode interactif ne vient utiliser que des fonctions de hauts
 *  niveaux du jeu qu'il utilise comme une librairie externe.
 */





#ifndef MODE_INTERACTIF_H
#define MODE_INTERACTIF_H

#include "jeu_siam.h"

/**
 * Fonction mode_interactif_lancer:
 * ********************************
 *   Lance le mode interactif affichant les actions possibles pour l'utilisateur, en crÃ©ant le jeu, la variable d'action et en les initialisant.
 *    Sauvegarde ensuite l'Ã©tat du plateau dans un fichier puis l'affiche pour le joueur. Laisse le joueur entrer une commande et l'execute.
 *
 */
void mode_interactif_lancer();

/**
 * Fonction mode_interactif_introduire_nouvelle_piece:
 * *************************
 *    Introduit une nouvelle piece dans le mode interactif
 *      avec les parametres passes en entre
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu modifiable
 *      - Un pointeur non NULL sur une condition de victoire
 *      - Deux entiers pour les coordonnÃ©es et un autre pour la victoire
 *      - Une orientation_deplacement
 *    Garantie:
 *      - La realisation de l'introduction si les parametres sont valides
 *      - victoire=1 si le coup et victorieux
 *      - Un message d'erreur si l'introduction n'est pas possible
 */
void mode_interactif_introduire_nouvelle_piece(jeu_siam* jeu,int x,int y,orientation_deplacement orientation,int* victoire);

/**
 * Fonction mode_interactif_deplacer_piece:
 * *************************
 *    Deplace une piece existante dans le mode interactif
 *      avec les parametres passes en entre
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu modifiable
 *      - Un pointeur non NULL sur une condition de victoire modifiable
 *      - Deux entiers pour les coordonnÃ©es et un autre pour la victoire
 *      - Deux orientation_deplacement pour le pelcament et l'orientation
 *    Garantie:
 *      - La realisation de le deplacement avec des parametres valide
 *      - victoire=1 si le coup et victorieux
 *      - Un message d'erreur si le deplacement n'est pas possible
 */
void mode_interactif_deplacer_piece(jeu_siam* jeu,int x,int y,orientation_deplacement deplacement,orientation_deplacement orientation,int* victoire);

/**
 * Fonction mode_interactif_changer_orientation:
 * *************************
 *    change l'orientation dune piece existante au coordonnee en entree dans le mode interactif par la nouvelle orientation entree
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu modifiable
 *      - Un pointeur non NULL sur une condition de victoire modifiable
 *      - Deux entiers pour les coordonnÃ©es et un autre pour la victoire
 *      - Une orientation_deplacement
 *    Garantie:
 *      - Le changement d'orientation de la piece si les parametres sont valides
 *      - victoire=1 si le coup et victorieux
 *      - Un message d'erreur si le changement n'est pas possible
 */
void mode_interactif_changer_orientation(jeu_siam* jeu,int x,int y,orientation_deplacement orientation);

/**
 * Fonction mode_interactif_sauvegarder_jeu_fichier:
 * *************************
 *    Sauvegarde l'Ã©tat du jeu dans un fichier texte
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu integre non modifiable
 *    Garantie:
 *      - L'etat du jeu est ecrit dans un fichier etat_courant.txt
 */
void mode_interactif_sauvegarder_jeu_fichier(const jeu_siam* jeu);

/**
 * Fonction mode_interactif_lire_fichier:
 * *************************
 *    Lit le fichier en entree et le stocke sur la variable jeu pointee en entree
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu modifiable
 *      - Un pointeur non NULL sur une chaine de caractÃ¨re non modifiable
 *    Garantie:
 *      - Un message d'erreur si le fichier n'est pas accessible.
 *      - Le contenu du fichier est stocke sur la variable jeu et le jeu est sauvegarde dans un fichier texte sinon
 */
void mode_interactif_lire_fichier(jeu_siam* jeu,const char* filename);

/**
 * Fonction mode_interactif_parametres_etre_valides:
 * *************************
 *    VÃ©rifie si les paramÃ¨tres sont integres ou valides
 *
 *    Necessite:
 *      - Un pointeur non NULL sur un jeu integre non modifiable
 *      - Deux entiers pour les coordonnÃ©es et un autre pour la victoire
 *      - Une orientation_deplacement
 *    Garantie:
 *      - Un retour de 0 si l'orientation_deplacement n'est pas integre/les coordonnes ne sont pas dans le plateau avec un message d'erreur
 *      - Un retour valant 1 sinon
 */
int mode_interactif_parametres_etre_valides(const jeu_siam* jeu,int x,int y,orientation_deplacement orientation);


#endif
