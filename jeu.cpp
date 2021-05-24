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

	sf::Texture textureFinishedLevel;
	textureFinishedLevel.loadFromFile("img/FinishedLevel.png");

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
	sf::Sprite FinishedLevel;

	Mur.setTexture(textureMur);
	Caisse.setTexture(textureCaisse);
	CaisseOK.setTexture(textureCaisseOK);
	Objectif.setTexture(textureObjectif);
	Player.setTexture(texturePlayerBas);
	FinishedLevel.setTexture(textureFinishedLevel);


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
		objectifsRestants = 0;

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
				case CAISSE_OK:
					window->draw(CaisseOK);
					CaisseOK.setPosition(position.x, position.y);
					break;
				case OBJECTIF:
					window->draw(Objectif);
					Objectif.setPosition(position.x, position.y);
					objectifsRestants++;
					break;
				}

			}
		}

		// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
		if (objectifsRestants == 0)
		{
			printf("Finished\n");
			window->draw(FinishedLevel);
		}

		if (objectifsRestants == 0 && sf::Event::KeyPressed == sf::Keyboard::Backspace)
		{
			printf("TRUE");
		}

		Player.setPosition(positionJoueur.x * TAILLE_BLOC, positionJoueur.y * TAILLE_BLOC);
		window->draw(Player);

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
				deplacerJoueur(objectifsRestants, carte, &positionJoueur, HAUT, window);
				break;
			case sf::Keyboard::Down:
				deplacerJoueur(objectifsRestants, carte, &positionJoueur, BAS, window);
				break;
			case sf::Keyboard::Left:
				deplacerJoueur(objectifsRestants, carte, &positionJoueur, GAUCHE, window);
				break;
			case sf::Keyboard::Right:
				deplacerJoueur(objectifsRestants, carte, &positionJoueur, DROITE, window);
				break;
			case sf::Keyboard::Num0:
				continuer = 0;
				break;

			}
			break;

		}

		window->display();

	}

	window->clear();
	sf::Texture textureMenu;
	sf::Sprite menu;


	// • Texture du menu
	textureMenu.loadFromFile("img/menu.png");
	menu.setTexture(textureMenu);

	window->draw(menu);
	window->display();

}

void deplacerJoueur(int objectifRestant, int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i *playerPosition, int direction, sf::RenderWindow* window)
{

	if (direction == HAUT)
	{
		if (playerPosition->y - 1 < 0)
		{}
		else
		{
			if (carte[playerPosition->x][playerPosition->y - 1] == MUR)
			{}
			else
			{
				// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
				if ((carte[playerPosition->x][playerPosition->y - 1] == CAISSE || carte[playerPosition->x][playerPosition->y - 1] == CAISSE_OK) &&
					(playerPosition->y - 2 < 0 || carte[playerPosition->x][playerPosition->y - 2] == MUR ||
						carte[playerPosition->x][playerPosition->y - 2] == CAISSE || carte[playerPosition->x][playerPosition->y - 2] == CAISSE_OK))
				{}
				else
				{
					//deplacerCaisse(&carte[playerPosition->x][playerPosition->y - 1], &carte[playerPosition->x][playerPosition->y - 2]);
					playerPosition->y--;
				}
			}
		}

		printf("\n\n ------------------------------ \n");
		printf("PLAYER = X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		printf("HAUT\n");
		window->display();

	}


	else if (direction == BAS)
	{
		if (playerPosition->y + 1 > NB_BLOCS_HAUTEUR)
		{}
		else
		{
			if (carte[playerPosition->x][playerPosition->y + 1] == MUR)
			{}
			else
			{
				// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
				if ((carte[playerPosition->x][playerPosition->y + 1] == CAISSE || carte[playerPosition->x][playerPosition->y + 1] == CAISSE_OK) &&
					(playerPosition->y + 2 < 0 || carte[playerPosition->x][playerPosition->y + 2] == MUR ||
						carte[playerPosition->x][playerPosition->y + 2] == CAISSE || carte[playerPosition->x][playerPosition->y + 2] == CAISSE_OK))
				{}
				else
				{
					//deplacerCaisse(&carte[playerPosition->x][playerPosition->y + 1], &carte[playerPosition->x][playerPosition->y + 2]);

					playerPosition->y++;
				}
			}
		}

		printf("\n\n ------------------------------ \n");
		printf("PLAYER = X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
		printf("BAS\n");
		window->display();
	}

	else if (direction == DROITE)
	{
		if (playerPosition->x + 1 > NB_BLOCS_LARGEUR)
		{}
		else
		{
			if (carte[playerPosition->x + 1][playerPosition->y] == MUR)
			{}
			else
			{
				// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
				if ((carte[playerPosition->x + 1][playerPosition->y] == CAISSE || carte[playerPosition->x + 1][playerPosition->y] == CAISSE_OK) &&
					(playerPosition->x + 2 < 0 || carte[playerPosition->y + 2][playerPosition->x] == MUR ||
						carte[playerPosition->x + 2][playerPosition->x] == CAISSE || carte[playerPosition->x + 2][playerPosition->y] == CAISSE_OK))
				{}
				else
				{
					//deplacerCaisse(&carte[playerPosition->x + 1][playerPosition->y], &carte[playerPosition->x + 2][playerPosition->y]);

					playerPosition->x++;
				}
			}
		}

			printf("\n\n ------------------------------ \n");
			printf("PLAYER = X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
			printf("DROITE\n");
			window->display();

	}

	else if (direction == GAUCHE)
	{
		if (playerPosition->x - 1 < 0)
		{}
		else
		{
			if (carte[playerPosition->x - 1][playerPosition->y] == MUR)
			{}
			else
			{
				// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
				if ((carte[playerPosition->x - 1][playerPosition->y] == CAISSE || carte[playerPosition->x - 1][playerPosition->y] == CAISSE_OK) &&
					(playerPosition->x - 2 < 0 || carte[playerPosition->x - 2][playerPosition->y] == MUR ||
						carte[playerPosition->x - 2][playerPosition->y] == CAISSE || carte[playerPosition->x - 2][playerPosition->y] == CAISSE_OK))
				{}
				else
				{
					//deplacerCaisse(&carte[playerPosition->x][playerPosition->y + 1], &carte[playerPosition->x][playerPosition->y + 2]);

					playerPosition->x--;
				}
			}
		}

			printf("\n\n ------------------------------ \n");
			printf("PLAYER = X = %d ; Y = %d \n", playerPosition->x, playerPosition->y);
			printf("GAUCHE\n");
			window->display();
	}
}

void deplacerCaisse(int objectifRestant, sf::Vector2i *pos, int direction, sf::RenderWindow* window)
{
	printf("");
}