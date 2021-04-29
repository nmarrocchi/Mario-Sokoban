/*
editeur.c
---------

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : gestion de l'éditeur de niveaux.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "const.h"
#include "editeur.h"

void editeur()
{
	printf("Editeur \n");

	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::IntRect position, positionJoueur;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };


	// Chargement des sprites (décors, personnage...)

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


}
