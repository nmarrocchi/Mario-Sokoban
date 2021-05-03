/*
editeur.c
---------

Rôle : Gestion de l'éditeur de niveaux.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "const.h"
#include "editeur.h"
#include "fichiers.h"

void editeur(sf::Sprite* ecran)
{
	printf("Editeur \n");

	sf::Sprite *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
	sf::IntRect position, positionJoueur;
	sf::Event event;

	int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
	int objetActuel = MUR, i = 0, j = 0;
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

	/* • Print chargerNiveau(carte) value • */
	bool level = (!chargerNiveau(carte));
	printf("%d\n", level);


	if (!chargerNiveau(carte))
		exit(printf("Fail to load the map")); /* • On arrête le jeu si on n'a pas pu charger le niveau • */


	/*
		// Boucle infinie de l'éditeur
	while (continuer)
	{
		*ecran.waitEvent(&event);
		switch (event.type)
		{
		case sf::QUIT:
			continuer = 0;
			break;
		case sf::MOUSEBUTTONDOWN:
			if (event.button.button == sf::BUTTON_LEFT)
			{
				// On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
				clicGaucheEnCours = 1; // On active un booléen pour retenir qu'un bouton est enfoncé
			}
			else if (event.button.button == sf::BUTTON_RIGHT) // Le clic droit sert à effacer
			{
				carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
				clicDroitEnCours = 1;
			}
			break;
		case sf::MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
			if (event.button.button == sf::BUTTON_LEFT)
				clicGaucheEnCours = 0;
			else if (event.button.button == sf::BUTTON_RIGHT)
				clicDroitEnCours = 0;
			break;
		case sf::MOUSEMOTION:
			if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
			}
			else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
			{
				carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
			}
			break;
		case sf::KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				continuer = 0;
				break;
			case SDLK_s:
				sauvegarderNiveau(carte);
				break;
			case SDLK_c:
				chargerNiveau(carte);
				break;
			case SDLK_KP1:
				objetActuel = MUR;
				break;
			case SDLK_KP2:
				objetActuel = CAISSE;
				break;
			case SDLK_KP3:
				objetActuel = OBJECTIF;
				break;
			case SDLK_KP4:
				objetActuel = PAIMON;
				break;
			}
			break;
		}

		// Effacement de l'écran
		sf::FillRect(ecran, NULL, sf::MapRGB(ecran->format, 255, 255, 255));

		// Placement des objets à l'écran
		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR:
					sf::BlitSurface(mur, NULL, ecran, &position);
					break;
				case CAISSE:
					sf::BlitSurface(caisse, NULL, ecran, &position);
					break;
				case OBJECTIF:
					sf::BlitSurface(objectif, NULL, ecran, &position);
					break;
				case PAIMON:
					sf::BlitSurface(paimon, NULL, ecran, &position);
					break;
				}
			}
		}

		// Mise à jour de l'écran
		sf::Flip(ecran);
	}

	*/




}
