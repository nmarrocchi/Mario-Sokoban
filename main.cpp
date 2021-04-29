#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "const.h"
#include "jeu.h"
#include "editeur.h"


int main(int argc, char *argv[])
{


	// - Texture du menu
	sf::RenderWindow window{ sf::VideoMode(1000, 1000), "Paimon's Escape" };
	sf::Texture texture;
	if (!texture.loadFromFile("img/menu.png"));

	sf::Sprite sprite;
	sprite.setTexture(texture);

	// - Navigation entre les options
	sf::Event event;

	sf::VideoMode::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	// - Fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		window.draw(sprite);

		// - Inspection de tous les évènements de la fenêtre qui ont été émis depuis la précédente itération
		sf::Event event;
		while (window.pollEvent(event))
		{
			// - Fermeture de la fenêtre demandée
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1)
				{
					// - Envoie vers la page de jeu
					jouer();
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2)
				{
					// - Envoie vers l'éditeur de niveau
					editeur();
				}
				
			}
		}

		window.display();
	}

	return 0;
}