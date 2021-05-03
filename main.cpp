#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "const.h"
#include "jeu.h"
#include "editeur.h"


int main(int argc, char *argv[])
{

	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

	sf::Sprite *ecran = NULL, *menu = NULL;
	sf::IntRect positionMenu;
	sf::Event event;

	sf::Music music;
	if (!music.openFromFile("music/background.ogg"))
	{
		printf("Musique non charg�e \n");
	}
	else {
		printf("La musique a charg�e \n");
		music.play();
	}


	/* � Cr�ation de la fen�tre � */
	sf::RenderWindow window{ sf::VideoMode(1000, 1000), "Paimon's Escape" };
	sf::Texture texture;
	sf::Image icon;

	/* � Ajout d'un ic�ne personnalis� � */
	icon.loadFromFile("img/icon.png");
	window.setIcon(192, 192, icon.getPixelsPtr());

	/* � Texture du menu � */
	if (!texture.loadFromFile("img/menu.png"))
	{
		// erreur
	}



	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	/* � Fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e � */
	while (window.isOpen())
	{
		window.draw(sprite);

		/* � Inspection de tous les �v�nements de la fen�tre qui ont �t� �mis � */
		sf::Event event;
		while (window.pollEvent(event))
		{
			/* � Fermeture de la fen�tre � */
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1)
				{
					/* � Envoie vers le jeu � */
					//jouer(&window);
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2)
				{
					/* � Envoie vers l'�diteur de niveau � */
					delete(menu);
					editeur(&window);
				}
			}
		}
		window.draw(sprite);
		window.display();
	}
	return 0;
}