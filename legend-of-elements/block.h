#ifndef __BLOCK_H
#define __BLOCK_H

#include "iostream"
#include "entity.h"
#include "log.h"

enum gemTypes{BLUE,GREEN,RED,ORANGE,PINK};
enum gemProperties{DOUBLE_POINTS,TRIPLE_POINTS,LOCKED};

// We'll store the spirtes in here so we can reference them instead
// of loading it for each block entity from the hdd
class blockSprites{
	sf::Texture tex[BLOCK_TYPES];
	sf::Sprite sprite[BLOCK_TYPES];

public:
	blockSprites();
	sf::Sprite getSprite(int type);
};

class block: public entity{
public:
	bool flaggedForDeletion;
	sf::FloatRect blockBeacon;

	block(int propertyId, float posx, float posy, blockSprites& sprites, std::vector<block>& blocks);
	int getHP();
	void setHP(int value);
	float xPos();
	void setXPos(float xpos);
	float yPos();
	void setYPos(float ypos);
	void setPosition(float newXPos, float newYPos);
	void flagForDelete();
	bool pendingDeletion();
	void think(std::vector<block>& blocks);
	void updateAllBlockPositions();
	sf::Sprite getSprite(float interpolation);
};

#endif