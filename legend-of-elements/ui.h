#ifndef __UI_H
#define __UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "log.h"
#include "defines.h"
#include "block.h"

class UI{
	sf::Texture backgroundTex;
	sf::Texture selectorTex;
	sf::FloatRect selectedRect;
	sf::FloatRect colRect1;
	sf::FloatRect colRect2;
	int selectedPosX, selectedPosY;
	bool selected;

public:
	sf::Sprite background;
	sf::Sprite selector;
	UI();
	bool loadFromFile(sf::Texture& tex, sf::Sprite& sprite, std::string fileName);
	void init(std::vector<block>& blocks);
	void attemtpToSelect(std::vector<block>& blocks);
	void setSelectorPos(float xpos, float ypos, std::vector<block>& blocks);
	void moveLeft(bool doMove, std::vector<block>& blocks);
	void moveUp(bool doMove, std::vector<block>& blocks);
	void think(std::vector<block>& blocks);
	sf::FloatRect getRect();
	sf::FloatRect getColRect1();
	sf::FloatRect getColRect2();
};
#endif