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
		printf("Musique non chargée \n");
	}
	else {
		printf("La musique a chargée \n");
		music.play();
	}


	/* • Création de la fenêtre • */
	sf::RenderWindow window{ sf::VideoMode(1000, 1000), "Paimon's Escape" };
	sf::Texture texture;
	sf::Image icon;

	/* • Ajout d'un icône personnalisé • */
	icon.loadFromFile("img/icon.png");
	window.setIcon(192, 192, icon.getPixelsPtr());

	/* • Texture du menu • */
	if (!texture.loadFromFile("img/menu.png"))
	{
		// erreur
	}



	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	/* • Fait tourner le programme jusqu'à ce que la fenêtre soit fermée • */
	while (window.isOpen())
	{
		window.draw(sprite);

		/* • Inspection de tous les évènements de la fenêtre qui ont été émis • */
		sf::Event event;
		while (window.pollEvent(event))
		{
			/* • Fermeture de la fenêtre • */
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1)
				{
					/* • Envoie vers le jeu • */
					//jouer(&window);
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2)
				{
					/* • Envoie vers l'éditeur de niveau • */
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