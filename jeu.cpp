/*
jeu.cpp
-----

Rôle : Fonctions du jeu.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "jeu.h"
#include "fichiers.h"

void jouer(sf::RenderWindow* window)
{
	printf("Jouer \n");

	sf::Sprite *paimon[4] = { NULL }; /* • 4 surfaces pour chacune des directions de paimon • */
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *paimonActuel = NULL;
	sf::IntRect position, positionJoueur;
	sf::Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	/* • Chargement des sprites (décors, personnage...) • */

	sf::Texture textureMur;
	if (!textureMur.loadFromFile("img/mur.jpg"));

	sf::Texture textureCaisse;
	if (!textureCaisse.loadFromFile("img/caisse.jpg"));

	sf::Texture textureCaisseOK;
	if (!textureCaisseOK.loadFromFile("img/caisse_ok.jpg"));

	sf::Texture textureObjectif;
	if (!textureObjectif.loadFromFile("img/objectif.png"));

	sf::Texture texturePaimonBas;
	if (!texturePaimonBas.loadFromFile("img/mario_bas.gif"));

	sf::Texture texturePaimonGauche;
	if (!texturePaimonGauche.loadFromFile("img/mario_gauche.gif"));

	sf::Texture texturePaimonHaut;
	if (!texturePaimonHaut.loadFromFile("img/mario_haut.gif"));

	sf::Texture texturePaimonDroite;
	if (!texturePaimonDroite.loadFromFile("img/mario_droite.gif"));



	paimonActuel = paimon[BAS]; /* • Paimon sera dirigé vers le bas au départ • */

		/* • Chargement du niveau • */
	if (!chargerNiveau(carte));
		exit(printf("Fail to load the map")); /* • On arrête le jeu si on n'a pas pu charger le niveau • */

}

void deplacerJoueur()
{

}

void deplacerCaisse()
{

}