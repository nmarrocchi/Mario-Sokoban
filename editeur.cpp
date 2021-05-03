/*
editeur.c
---------

Rôle : Gestion de l'éditeur de niveaux.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::RenderWindow* window)
{
	printf("Editeur \n");


	sf::Sprite *mur = NULL, *caisse = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };



	/* • Chargement des sprites (décors, personnage...) • */

	sf::Texture textureMur;
	sf::Texture textureCaisse;
	sf::Texture textureObjectif;
	sf::Texture texturePaimonBas;


	textureMur.loadFromFile("img/mur.jpg");
	textureCaisse.loadFromFile("img/caisse.jpg");
	textureObjectif.loadFromFile("img/objectif.png");
	texturePaimonBas.loadFromFile("img/mario_bas.gif");


	mur = new sf::Sprite(textureMur);
	caisse = new sf::Sprite(textureCaisse);
	objectif = new sf::Sprite(textureObjectif);
	marioActuel = new sf::Sprite(texturePaimonBas);



	if (chargerNiveau(carte))
	{
		printf("failed \n");
	}
	else {
		printf("success \n");
	}




	/* • Changement d'objets • */

	if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) )
	{
		objetActuel = PAIMON;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) )
	{
		objetActuel = OBJECTIF;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) )
	{
		objetActuel = CAISSE;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) )
	{
		objetActuel = MUR;
	}

}
