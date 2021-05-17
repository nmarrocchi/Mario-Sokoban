/*
editeur.c
---------

Rôle : Gestion de l'éditeur de niveaux.
*/
#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "const.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::RenderWindow* window)
{

	sf::Sprite *mur = NULL, *caisse = NULL, *objectif = NULL, *PlayerActuel = NULL;
	sf::Vector2i position(0, 0), cursorCoords(0, 0);
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	int crx = (cx - 816) / 2 ;
	int cry = (cy - 816) / 2 ;
	printf("%d , %d", crx, cry);



	// • Chargement des sprites (décors, personnage...)

	sf::Texture textureMur;
	sf::Texture textureCaisse;
	sf::Texture textureObjectif;
	sf::Texture texturePlayerBas;

	sf::Texture textureCursorBlock;


	textureMur.loadFromFile("img/mur.jpg");
	textureCaisse.loadFromFile("img/caisse.jpg");
	textureObjectif.loadFromFile("img/objectif.png");
	texturePlayerBas.loadFromFile("img/mario_bas.gif");

	textureCursorBlock.loadFromFile("img/caisse.jpg");


	sf::Sprite Mur;
	sf::Sprite Caisse;
	sf::Sprite Objectif;
	sf::Sprite PlayerBas;

	sf::Sprite CursorBlock;


	Mur.setTexture(textureMur);
	Caisse.setTexture(textureCaisse);
	Objectif.setTexture(textureObjectif);
	PlayerBas.setTexture(texturePlayerBas);

	CursorBlock.setTexture(textureCursorBlock);


	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE);
	}

	// • Boucle éditeur
	while (continuer)
	{

		

		window->waitEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			continuer = 0;
			break;

		case sf::Event::MouseButtonPressed :
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				// • On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1; // • On active un booléen pour retenir qu'un bouton est enfoncé
				
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // • Le clic droit sert à effacer
			{
				
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
				
			}
			break;

		case sf::Event::MouseButtonReleased: // • On désactive le booléen qui disait qu'un bouton était enfoncé
			if (event.MouseButtonPressed == sf::Mouse::Left)
				clicGaucheEnCours = 0;
			else if (event.MouseButtonPressed == sf::Mouse::Right)
				clicDroitEnCours = 0;
			break;
			
			// • Quand bouton enfoncé, changement en chaine des bloc survolés
		case sf::Event::MouseMoved:
			
			/*
			if (clicGaucheEnCours) // • Si on déplace la souris et que le bouton gauche de la souris est enfoncé
			{
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = objetActuel;
			}
			else if (clicDroitEnCours) // • Pareil pour le bouton droit de la souris
			{
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = CAISSE;
			}
			break;
			*/
			

		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::S:
				sauvegarderNiveau(carte);
				break;
			case sf::Keyboard::C:
				chargerNiveau(carte);
				break;
			case sf::Keyboard::Num1:
				objetActuel = MUR;
				break;
			case sf::Keyboard::Num2:
				objetActuel = CAISSE;
				break;
			case sf::Keyboard::Num3:
				objetActuel = OBJECTIF;
				break;
			case sf::Keyboard::Num4:
				objetActuel = PLAYER;
				break;
			case sf::Keyboard::Num0:
				continuer = 0;
				break;
			}
			break;
		}


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
					window->draw(PlayerBas);
					PlayerBas.setPosition(position.x, position.y);
					break;
				}

			}

			// • Set Cursor Block Sprite to indicate what can be used
			cursorCoords = sf::Mouse::getPosition();
			printf("X = %d, Y = %d \n", cursorCoords.x - crx, cursorCoords.y - cry);

			switch (objetActuel)
			{
			case MUR:
				CursorBlock.setTexture(textureMur);
				break;
			case CAISSE:
				CursorBlock.setTexture(textureCaisse);
				break;
			case OBJECTIF:
				CursorBlock.setTexture(textureObjectif);
				break;
			case PLAYER:
				CursorBlock.setTexture(texturePlayerBas);
				break;
			}

			window->draw(CursorBlock);

			CursorBlock.move(cursorCoords.x - crx, cursorCoords.y - cry);
			

		}

		// • Screen Refresh
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