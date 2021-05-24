/*
jeu.h
----------

Rôle : Prototypes des fonctions du jeu.
*/
#ifndef DEF_JEU
#define DEF_JEU
#include <SFML/Graphics/Rect.hpp>

void jouer(sf::RenderWindow* window);
void deplacerJoueur(int objectifRestant, int carte[][NB_BLOCS_HAUTEUR], sf::Vector2i *pos, int direction, sf::RenderWindow* window);
void deplacerCaisse(int objectifRestant, int *premiereCase, int *secondeCase, sf::RenderWindow* window);

#endif
