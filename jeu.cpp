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

	sf::Sprite *player[4] = { NULL }; /* • 4 surfaces pour chacune des directions du joueur • */
	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *playerActuel = NULL;
	sf::Vector2i position(0, 0), positionJoueur(0, 0);
	sf::Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	/* • Chargement des sprites (décors, personnage...) • */

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



	playerActuel = player[BAS]; /* • Paimon sera dirigé vers le bas au départ • */

	// • Clear Window
	window->clear();

	/* • Chargement du niveau • */
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



	// • Activation répétition touches
	window->setKeyRepeatEnabled(1);

	while (continuer)
	{
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
				playerActuel = player[HAUT];
				deplacerJoueur(carte, &positionJoueur, HAUT, window);
				break;
			case sf::Keyboard::Down:
				playerActuel = player[BAS];
				deplacerJoueur(carte, &positionJoueur, BAS, window);
				break;
			case sf::Keyboard::Left:
				playerActuel = player[GAUCHE];
				deplacerJoueur(carte, &positionJoueur, GAUCHE, window);
				break;
			case sf::Keyboard::Right:
				playerActuel = player[DROITE];
				deplacerJoueur(carte, &positionJoueur, DROITE, window);
				break;

			}
			break;

		}

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
					window->draw(Player);
					printf("i/j :     X = %d ; Y = %d \n", i, j);
					printf("Player :     X = %d ; Y = %d \n", positionJoueur.x, positionJoueur.y);
					break;
				}

			}
		}


		// • Si aucun objectif sur la carte, alors gagné
		if (!objectifsRestants)
			continuer = 0;

	}

	// • Désactivation répétition touches
	window->setKeyRepeatEnabled(0);

	window->display();
}


void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i *pos, int direction, sf::RenderWindow* window)
{
	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
			break;
		if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
			break;
		// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;

		// Si on arrive là, c'est qu'on peut déplacer le joueur !
		// On vérifie d'abord s'il y a une caisse à déplacer
		//deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--; // On peut enfin faire monter le joueur (oufff !)
		printf("X = %d ; Y = %d \n", pos->x, pos->y);
		break;


	case BAS:
		if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
			break;
		if (carte[pos->x][pos->y + 1] == MUR)
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
			(pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			break;


		//deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		printf("X = %d ; Y = %d \n", pos->x, pos->y);
		break;


	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (carte[pos->x - 1][pos->y] == MUR)
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			break;


		//deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		printf("X = %d ; Y = %d \n", pos->x, pos->y);
		break;


	case DROITE:
		if (pos->x + 1 >= NB_BLOCS_LARGEUR)
			break;
		if (carte[pos->x + 1][pos->y] == MUR)
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
			(pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			break;

		//deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		printf("X = %d ; Y = %d \n", pos->x, pos->y);
		break;
	}
	window->display();
}

void deplacerCaisse()
{

}