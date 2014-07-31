#include "ui.h"

UI::UI(){
	this->loadFromFile(backgroundTex, background, "Resources\\background.png");
	this->loadFromFile(selectorTex, selector, "Resources\\selector.png");

	this->selectedPosX = 0;
	this->selectedPosY = 0;

	this->selected = false;

	this->colRect1.width = 10;
	this->colRect1.height = 10;
	this->colRect2.width = 10;
	this->colRect2.height = 10;
}

bool UI::loadFromFile(sf::Texture& tex, sf::Sprite& sprite, std::string fileName){
	if(!tex.loadFromFile(fileName)){
		log("[!] Error loading texture from: \n \
				Path: " + fileName + " \n");
		return false;
	}
	sprite.setTexture(tex);

	return true;
}

void UI::init(std::vector<block>& blocks){
	this->attemtpToSelect(blocks);
}

void UI::attemtpToSelect(std::vector<block>& blocks){
	// Select the middle blocks
	int xpos = BLOCK_GRID_X + (3 * BLOCK_SIZE);

	// Get the lowest 
	float lowestPos = 1000;
	for(int i = 0; i < blocks.size(); i++){
		float ypos = blocks[i].yPos();
		if(ypos + BLOCK_GRID_Y > 0){
			if(ypos < lowestPos){
				lowestPos = ypos;
			}

			this->selected = true;
		}
	}

	// Set the selection rect
	this->setSelectorPos(xpos, lowestPos, blocks);
	this->selectedRect.width = SELECTOR_WIDTH;
	this->selectedRect.height = SELECTOR_HEIGHT;
}

void UI::setSelectorPos(float xpos, float ypos, std::vector<block>& blocks){
	// Set the selection rect
	this->selectedRect.left = xpos;
	this->selectedRect.top = ypos;

	// If we moved too high, move it down
	if(this->selectedRect.top < BLOCK_GRID_Y - (this->selector.getTextureRect().height / 2)){
		this->selectedRect.top += BLOCK_SIZE;
	}

	//Align to Beacon
	// Check for the nearestby beacon to snap to, if applicable
	bool found = false;
	float x, y = -1;
	sf::FloatRect tmp;
	tmp.left = this->selectedRect.left;
	tmp.top = this->selectedRect.top;
	tmp.width = 1;
	tmp.height = 1;

	for(int i = 0; i < blocks.size(); i++){
		if(tmp.intersects(blocks[i].blockBeacon)){
			x = blocks[i].xPos();
			y = blocks[i].yPos();
			found = true;
		}
	}
	// Found a beacon, snap to it
	if(found){
		this->selectedRect.left = x;
		this->selectedRect.top = y;
	}

	// Update the sprite
	this->selector.setPosition(this->selectedRect.left, this->selectedRect.top);

	// Update the colision rects
	this->colRect1.left = this->selectedRect.left - (this->selectedRect.width / 4);
	this->colRect1.top = this->selectedRect.top - (this->selectedRect.height / 2);
	this->colRect2.left = this->selectedRect.left + (BLOCK_SIZE - (this->selectedRect.width / 4));
	this->colRect2.top = this->selectedRect.top - (this->selectedRect.height / 2);
}

void UI::moveLeft(bool doMove, std::vector<block>& blocks){
	if(doMove){
		// Move left
		if(this->selectedRect.left > BLOCK_GRID_X){
			this->setSelectorPos(this->selectedRect.left -= BLOCK_SIZE, this->selectedRect.top, blocks);
		}
	}else{
		// Move right
		if(this->selectedRect.left < BLOCK_GRID_X + (BLOCK_SIZE * (FIELD_SIZE-2))){
			this->setSelectorPos(this->selectedRect.left += BLOCK_SIZE, this->selectedRect.top, blocks);
		}
	}
}

void UI::moveUp(bool doMove, std::vector<block>& blocks){
	if(doMove){
		// Move up
		if(this->selectedRect.top > BLOCK_GRID_Y){
			this->setSelectorPos(this->selectedRect.left, this->selectedRect.top -= BLOCK_SIZE, blocks);
		}
	}else{
		// Move down
		if(this->selectedRect.top < BLOCK_GRID_Y + (BLOCK_SIZE * (FIELD_SIZE-1))){
			this->setSelectorPos(this->selectedRect.left, this->selectedRect.top += BLOCK_SIZE, blocks);
		}
	}
}

void UI::think(std::vector<block>& blocks){
	if(this->selected){
		// Move up with the blocks
		this->setSelectorPos(this->selectedRect.left, (this->selectedRect.top - RAISE_SPEED), blocks);
	}else{
		this->attemtpToSelect(blocks);
	}
	
}

sf::FloatRect UI::getRect(){
	return this->selectedRect;
}

sf::FloatRect UI::getColRect1(){
	return this->colRect1;
}

sf::FloatRect UI::getColRect2(){
	return this->colRect2;
}