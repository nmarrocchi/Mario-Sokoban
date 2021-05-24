#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>

#include "const.h"
#include "jeu.h"
#include "editeur.h"



int main(int argc, char *argv[])
{

	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	sf::Sprite *ecran = NULL;
	sf::Vector2i positionMenu(0, 0);
	sf::Event event;

	int continuer = 1;


	// � Musique de fond
	sf::Music music;
	if (!music.openFromFile("music/ScreenTitle.ogg"))
	{
		printf("Musique non charg�e \n");
	}
	else {
	//music.play();
	music.setLoop(true);
	}

	//Cr�ation de la fen�tre
	sf::RenderWindow window{ sf::VideoMode(816, 816), "Soulworker" };
	sf::Texture textureMenu;
	sf::Sprite menu;
	

	// � Texture du menu
	textureMenu.loadFromFile("img/menu.png");
	menu.setTexture(textureMenu);

	// � Ajout d'un ic�ne personnalis�
	sf::Image icon;
	icon.loadFromFile("img/icon.png");
	window.setIcon(180, 180, icon.getPixelsPtr());

	window.draw(menu);
	window.display();

	while (continuer)
	{

		window.waitEvent(event);

		switch (event.type)
		{
			// � Fermeture de la fen�tre
		case sf::Event::Closed:
			continuer = 0;
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code)
			{
			case sf::Keyboard::Space: // � Veut arr�ter le jeu
				continuer = 0;
				break;
			case sf::Keyboard::Numpad1: // � Demande � jouer
				jouer(&window);
				break;
			case sf::Keyboard::Numpad2: // � Demande l'�diteur de niveaux
				editeur(&window);
				break;

			}
			break;
		}

	}

	return 0;
}