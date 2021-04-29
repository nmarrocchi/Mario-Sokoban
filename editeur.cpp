/*
editeur.c
---------

Par mateo21, pour Le Site du Z�r0 (www.siteduzero.com)

R�le : gestion de l'�diteur de niveaux.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "const.h"
#include "editeur.h"

void editeur()
{
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::IntRect position, positionJoueur;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };


	// Chargement des sprites (d�cors, personnage...)
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

}
