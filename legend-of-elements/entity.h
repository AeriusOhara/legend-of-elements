#ifndef __ENTITY_H
#define __ENTITY_H
#include <SFML/Graphics.hpp>
#include "defines.h"

class entity{
public:
	int id;
	sf::Vector2f position;
	int hp;
	int propertyId;
	bool falling;
	sf::Sprite sprite;
	sf::FloatRect colissionbox;
};

#endif