/*
editeur.c
---------

R�le : Gestion de l'�diteur de niveaux.
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
	sf::Vector2i position(0, 0), cursorCoords;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };




	// � Chargement des sprites (d�cors, personnage...)

	sf::Texture textureMur;
	sf::Texture textureCaisse;
	sf::Texture textureObjectif;
	sf::Texture texturePlayerBas;

	sf::Texture textureTest;


	textureMur.loadFromFile("img/mur.jpg");
	textureCaisse.loadFromFile("img/caisse.jpg");
	textureObjectif.loadFromFile("img/objectif.png");
	texturePlayerBas.loadFromFile("img/mario_bas.gif");

	textureTest.loadFromFile("img/caisse.jpg");


	sf::Sprite Mur;
	sf::Sprite Caisse;
	sf::Sprite Objectif;
	sf::Sprite PlayerBas;

	sf::Sprite Test;


	Mur.setTexture(textureMur);
	Caisse.setTexture(textureCaisse);
	Objectif.setTexture(textureObjectif);
	PlayerBas.setTexture(texturePlayerBas);

	Test.setTexture(textureTest);


	if (!chargerNiveau(carte))
	{
		exit(EXIT_FAILURE);
	}

	// � Boucle �diteur
	while (continuer)
	{
		sf::Mouse::getPosition();
		//printf("X = %d ; Y = %d \n", cursorCoords.x, cursorCoords.y);

		window->waitEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			continuer = 0;
			break;

		case sf::Event::MouseButtonPressed :
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				
				// � On met l'objet actuellement choisi (mur, caisse...) � l'endroit du clic
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1; // � On active un bool�en pour retenir qu'un bouton est enfonc�
				
			}
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) // � Le clic droit sert � effacer
			{
				
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
				
			}
			break;

		case sf::Event::MouseButtonReleased: // � On d�sactive le bool�en qui disait qu'un bouton �tait enfonc�
			if (event.MouseButtonPressed == sf::Mouse::Left)
				clicGaucheEnCours = 0;
			else if (event.MouseButtonPressed == sf::Mouse::Right)
				clicDroitEnCours = 0;
			break;
			
			// � Quand bouton enfonc�, changement en chaine des bloc survol�s
		case sf::Event::MouseMoved:
			
			/*
			if (clicGaucheEnCours) // � Si on d�place la souris et que le bouton gauche de la souris est enfonc�
			{
				carte[event.mouseButton.x / TAILLE_BLOC][event.mouseButton.y / TAILLE_BLOC] = objetActuel;
			}
			else if (clicDroitEnCours) // � Pareil pour le bouton droit de la souris
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
			}
			break;
		}


		// � Clear Window
		window->clear();

		// � Put the blocs on the map
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
		}

		// � Screen Refresh
		window->display();

	}

}