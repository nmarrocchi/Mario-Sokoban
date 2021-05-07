/*
fichiers.c++
----------

Rôle : Fonctions de lecture / écriture de fichiers de niveau.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


#include "const.h"
#include "jeu.h"
#include "editeur.h"
#include "fichiers.h"

using namespace std;

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{

	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = { 0 };
	int i = 0, j = 0;

	FILE *fichier = fopen("levels.lvl", "r");
	if (fichier == NULL) {
		printf("Not existing \n");
		return 0;

		// Le fichier n'existe pas
	}
	else {
		printf("Existing \n");
		// le fichier existe !

	}

	fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
			{
			case '0':
				niveau[j][i] = 0;
				break;
			case '1':
				niveau[j][i] = 1;
				break;
			case '2':
				niveau[j][i] = 2;
				break;
			case '3':
				niveau[j][i] = 3;
				break;
			case '4':
				niveau[j][i] = 4;
				break;
			}
		}
	}

	fclose(fichier);
	return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
	FILE* fichier = NULL;
	int i = 0, j = 0;

	fichier = fopen("levels.lvl", "w");

	if (fichier == NULL)
		return 0;

	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			fprintf(fichier, "%d", niveau[j][i]);
		}
	}

	printf("File Saved");

	fclose(fichier);
	return 1;
}