#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "const.h"
#include "jeu.h"
#include "editeur.h"


int main(int argc, char *argv[])
{


	sf::Sprite *ecran = NULL, *menu = NULL;
	sf::IntRect positionMenu;
	sf::Event event;

	sf::SoundBuffer buffer;
	buffer.loadFromFile("/music/background.mp3");
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();


	/* • Création de la fenêtre • */
	sf::RenderWindow window;
	window.create(sf::VideoMode(1000, 1000), "Paimon's Escape");
	sf::Texture texture;
	sf::Image icon;

	icon.loadFromFile("img/icon.png");
	window.setIcon(192, 192, icon.getPixelsPtr());

	/* • Texture du menu • */
	if (!texture.loadFromFile("img/menu.png"));


	sf::Sprite sprite;
	sprite.setTexture(texture);

	sf::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	/* • Fait tourner le programme jusqu'à ce que la fenêtre soit fermée • */
	while (window.isOpen())
	{
		window.draw(sprite);

		/* • Inspection de tous les évènements de la fenêtre qui ont été émis depuis la précédente itération • */
		sf::Event event;
		while (window.pollEvent(event))
		{
			/* • Fermeture de la fenêtre demandée • */
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1)
				{
					/* • Envoie vers la page de jeu • */
					delete(menu);
					
					jouer(ecran);
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2)
				{
					/* • Envoie vers l'éditeur de niveau • */
					editeur(ecran);
				}

			}
		}

		window.display();
	}
	delete(menu);

	return EXIT_SUCCESS;
}