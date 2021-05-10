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

	sf::Sprite *player[4] = { NULL }; // • 4 surfaces pour chacune des directions du joueur
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *playerActuel = NULL;
	sf::Vector2i position(0, 0), positionJoueur(0, 0);
	sf::Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	// • Chargement des sprites (décors, personnage...)

	sf::Texture textureMur;
	textureMur.loadFromFile("img/mur.jpg");


	sf::Texture textureCaisse;
	textureCaisse.loadFromFile("img/caisse.jpg");


	sf::Texture textureCaisseOK;
	textureCaisseOK.loadFromFile("img/caisse_ok.jpg");


	sf::Texture textureObjectif;
	textureObjectif.loadFromFile("img/objectif.png");


	sf::Texture texturePlayerBas;
	texturePlayerBas.loadFromFile("img/mario_bas.gif");


	sf::Texture texturePlayerGauche;
	texturePlayerGauche.loadFromFile("img/mario_gauche.gif");


	sf::Texture texturePlayerHaut;
	texturePlayerHaut.loadFromFile("img/mario_haut.gif");


	sf::Texture texturePlayerDroite;
	texturePlayerDroite.loadFromFile("img/mario_droite.gif");


	sf::Sprite Mur;
	sf::Sprite Caisse;
	sf::Sprite CaisseOK;
	sf::Sprite Objectif;
	sf::Sprite Player;

	Mur.setTexture(textureMur);
	Caisse.setTexture(textureCaisse);
	CaisseOK.setTexture(textureCaisseOK);
	Objectif.setTexture(textureObjectif);
	Player.setTexture(texturePlayerBas);


	// • Chargement du niveau
	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE);
	}


	// • Search Player Start Coords
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == PLAYER) // If Player Is Here
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
			}
		}
	}




	while (continuer)
	{

		// • Clear Window
		window->clear();


		// • Put the blocs on the map
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR:
					window->draw(Mur);
					Mur.setPosition(position.x, position.y);
					break;
				case CAISSE:
					window->draw(Caisse);
					Caisse.setPosition(position.x, position.y);
					break;
				case OBJECTIF:
					window->draw(Objectif);
					Objectif.setPosition(position.x, position.y);
					break;
				case PLAYER:
					Player.setPosition(position.x, position.y);
					printf("i/j :     X = %d ; Y = %d \n", i, j);
					break;
				}

			}
		}

		window->waitEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			continuer = 0;
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Up:
				position.y = position.y -1;
				//deplacerJoueur(carte, &position, HAUT, window);
				break;
			case sf::Keyboard::Down:
				position.y = position.y +1;
				//deplacerJoueur(carte, &position, BAS, window);
				break;
			case sf::Keyboard::Left:
				position.x = position.x - 1;
				//deplacerJoueur(carte, &position, GAUCHE, window);
				break;
			case sf::Keyboard::Right:
				position.x = position.x + 1;
				//deplacerJoueur(carte, &position, DROITE, window);
				break;
			case sf::Keyboard::Escape:
				continuer = 0;
				break;

				printf("\n Player Position : \n X = %d ; Y = %d \n", position.x, position.y);

			}
			break;

		}

		window->draw(Player);

		window->display();

	}
	// • Screen Refresh
	window->display();

	
	window->clear();
	sf::Texture textureMenu;
	sf::Sprite menu;


	// • Texture du menu
	textureMenu.loadFromFile("img/menu.png");
	menu.setTexture(textureMenu);

	window->draw(menu);
	window->display();

}


void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i *playerPosition, int direction, sf::RenderWindow* window)
{
	switch (direction)
	{
	case HAUT:
		if (playerPosition->y - 1 < 0) // • Si le joueur dépasse l'écran, on arrête
			break;
		if (carte[playerPosition->x][playerPosition->y - 1] == MUR) // • Si mur, on arrête
			break;
		// • Si caisse à pousser, verif si mur / caisse / limite map derrière
		if ((carte[playerPosition->x][playerPosition->y - 1] == CAISSE || carte[playerPosition->x][playerPosition->y - 1] == CAISSE_OK) &&
			(playerPosition->y - 2 < 0 || carte[playerPosition->x][playerPosition->y - 2] == MUR ||
				carte[playerPosition->x][playerPosition->y - 2] == CAISSE || carte[playerPosition->x][playerPosition->y - 2] == CAISSE_OK))
			break;

		// • Verif si caisse à déplaçer
		//deplacerCaisse(&carte[playerPosition->x][playerPosition->y - 1], &carte[playerPosition->x][playerPosition->y - 2]);

		playerPosition->y--;
		printf("X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		break;


	case BAS:
		if (playerPosition->y + 1 >= NB_BLOCS_HAUTEUR)
			break;
		if (carte[playerPosition->x][playerPosition->y + 1] == MUR)
			break;

		if ((carte[playerPosition->x][playerPosition->y + 1] == CAISSE || carte[playerPosition->x][playerPosition->y + 1] == CAISSE_OK) &&
			(playerPosition->y + 2 >= NB_BLOCS_HAUTEUR || carte[playerPosition->x][playerPosition->y + 2] == MUR ||
				carte[playerPosition->x][playerPosition->y + 2] == CAISSE || carte[playerPosition->x][playerPosition->y + 2] == CAISSE_OK))
			break;


		//deplacerCaisse(&carte[playerPosition->x][playerPosition->y + 1], &carte[playerPosition->x][playerPosition->y + 2]);

		playerPosition->y++;
		printf("X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		break;


	case GAUCHE:
		if (playerPosition->x - 1 < 0)
			break;
		if (carte[playerPosition->x - 1][playerPosition->y] == MUR)
			break;

		if ((carte[playerPosition->x - 1][playerPosition->y] == CAISSE || carte[playerPosition->x - 1][playerPosition->y] == CAISSE_OK) &&
			(playerPosition->x - 2 < 0 || carte[playerPosition->x - 2][playerPosition->y] == MUR ||
				carte[playerPosition->x - 2][playerPosition->y] == CAISSE || carte[playerPosition->x - 2][playerPosition->y] == CAISSE_OK))
			break;


		//deplacerCaisse(&carte[playerPosition->x - 1][playerPosition->y], &carte[playerPosition->x - 2][playerPosition->y]);

		playerPosition->x--;
		printf("X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		break;


	case DROITE:
		if (playerPosition->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (carte[playerPosition->x + 1][playerPosition->y] == MUR)
			break;

		if ((carte[playerPosition->x + 1][playerPosition->y] == CAISSE || carte[playerPosition->x + 1][playerPosition->y] == CAISSE_OK) &&
			(playerPosition->x + 2 >= NB_BLOCS_LARGEUR || carte[playerPosition->x + 2][playerPosition->y] == MUR ||
				carte[playerPosition->x + 2][playerPosition->y] == CAISSE || carte[playerPosition->x + 2][playerPosition->y] == CAISSE_OK))
			break;

		//deplacerCaisse(&carte[playerPosition->x + 1][playerPosition->y], &carte[playerPosition->x + 2][playerPosition->y]);

		playerPosition->x++;
		printf("X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		break;
	}
	window->display();
}

void deplacerCaisse()
{

}