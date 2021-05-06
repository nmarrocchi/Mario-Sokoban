/*
constantes.h
----------

D�finition des constantes pour tout le programme (taille de la fen�tre etc...)
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC         68 /* � Taille d'un bloc (carr�) en pixels � */
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum { HAUT, BAS, GAUCHE, DROITE };
enum { VIDE, MUR, CAISSE, OBJECTIF, PLAYER, CAISSE_OK };

#endif