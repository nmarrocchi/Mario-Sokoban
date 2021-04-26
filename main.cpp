#include <SFML/Graphics.hpp>
#include <iostream>

#include "const.h"
#include "jeu.h"
#include "editeur.h"



int main(int argc, char *argv[])
{
	// - Texture du menu
	sf::RenderWindow window{ sf::VideoMode(1200, 1000), "Mario Sokoban" };
	sf::Texture texture;
	if (!texture.loadFromFile("img/menu.jpg"));

	sf::Sprite sprite;
	sprite.setTexture(texture);

	// - Navigation entre les options
	sf::Event event;

	sf::VideoMode::VideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32);

	// - Fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		window.draw(sprite);

		// - Inspection de tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente it�ration
		sf::Event event;
		while (window.pollEvent(event))
		{
			// - Fermeture de la fen�tre demand�e
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				/*
				if (event.key.code == sf::Keyboard::Numpad1 || event.key.code == sf::Keyboard::Num1)
				{
					// - Envoie vers la page de jeu
					jouer();
				}
				else if (event.key.code == sf::Keyboard::Numpad2 || event.key.code == sf::Keyboard::Num2)
				{
					// - Envoie vers l'�diteur de niveau
					editeur();
				}
				*/
			}
		}

		window.display();
	}

	return 0;
}