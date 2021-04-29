/*
jeu.cpp
-----

Rôle : Fonctions du jeu.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "const.h"
#include "jeu.h"

void jouer()
{

	sf::Sprite *paimon[4] = { NULL }; // 4 surfaces pour chacune des directions de mario
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::IntRect position, positionJoueur;
	sf::Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// Chargement des sprites (décors, personnage...)
	sf::Texture textureMur;
	sf::Texture textureCaisse;
	sf::Texture textureCaisseOK;
	sf::Texture textureObjectif;
	sf::Texture texturePaimonBas;
	sf::Texture texturePaimonGauche;
	sf::Texture texturePaimonHaut;
	sf::Texture texturePaimonDroite;


	if (!textureMur.loadFromFile("img/mur.jpg"));

	if (!textureCaisse.loadFromFile("img/caisse.jpg"));

	if (!textureCaisseOK.loadFromFile("img/caisse_ok.jpg"));

	if (!textureObjectif.loadFromFile("img/objectif.jpg"));

	if (!texturePaimonBas.loadFromFile("img/paimon_bas.jpg"));

	if (!texturePaimonGauche.loadFromFile("img/paimon_gauche.jpg"));

	if (!texturePaimonHaut.loadFromFile("img/paimon_haut.jpg"));

	if (!texturePaimonDroite.loadFromFile("img/paimon_droite.jpg"));


	paimonActuel = paimon[BAS]; // Paimon sera dirigé vers le bas au départ



		// Effacement de l'écran
		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

}

void deplacerJoueur()
{

}

void deplacerCaisse()
{

}

