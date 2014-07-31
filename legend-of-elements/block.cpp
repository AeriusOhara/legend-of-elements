#include "block.h"

blockSprites::blockSprites(){
	for(int i = 0; i < BLOCK_TYPES; i++){
		std::string relativePath = "Resources\\gems\\";
		std::string fileName = "";
		std::string extention = ".png";

		switch(i){
		case gemTypes::BLUE:	// 0
			fileName = "blue";
			break;
		case gemTypes::GREEN:	// 1
			fileName = "green";
			break;
		case gemTypes::ORANGE:	// 2
			fileName = "orange";
			break;
		case gemTypes::PINK:	// 3
			fileName = "pink";
			break;
		case gemTypes::RED:		// 4
			fileName = "red";
			break;
		default:
			throw("Something went wrong, gemType: %d\n", i);
			break;
		}

		// Load the Texture
		std::string fullPath = relativePath + fileName + extention;
		log("[o] Loading "+fileName+" from ["+fullPath+"]\n");
		if(!this->tex[i].loadFromFile(fullPath)){
			log("[!] Error loading texture from: \n \
				   relativePath: " + relativePath + " \n \
				   fileName: %s" + fileName + " \n \
				   extention: %s" + extention);
		}
		this->sprite[i].setTexture(this->tex[i]);
	}
}

sf::Sprite blockSprites::getSprite(int type){
	return this->sprite[type];
}

block::block(int propertyId, float posx, float posy, blockSprites& sprites, std::vector<block>& blocks){
	// Grab a random number as id, make sure it's unique by
	// polling through the blocks vector and create a new id
	// if the one we assigned is in use
	this->id = 0;
	bool isUnique = false;
	while(!isUnique){
		isUnique = true;
		for(int i = 0; i < blocks.size(); i++){
			if(blocks[i].id == this->id){
				isUnique = false;
				this->id = rand()%RAND_MAX;
			}
		}
	}

	this->hp = 100;
	this->propertyId = propertyId;
	this->position.x = BLOCK_GRID_X + posx * BLOCK_SIZE;
	this->position.y = BLOCK_GRID_Y + posy * BLOCK_SIZE;
	this->flaggedForDeletion = false;
	this->falling = true;

	// Set up the beacon
	this->blockBeacon.left = this->position.x;
	this->blockBeacon.top = this->position.y;
	this->blockBeacon.width = 10;
	this->blockBeacon.width = 10;

	// Set up the sprite
	this->sprite = sprites.getSprite(this->propertyId);
	this->updateAllBlockPositions();
}

int block::getHP(){
	return this->hp;
}

void block::setHP(int value){
	this->hp = value;
}

float block::xPos(){
	return this->position.x;
}

void block::setXPos(float xpos){
	this->position.x = xpos;
	this->updateAllBlockPositions();
}

float block::yPos(){
	return this->position.y;
}

void block::setYPos(float ypos){
	this->position.y = ypos;
	this->updateAllBlockPositions();
}

void block::setPosition(float newXPos, float newYPos){
	this->position.x = newXPos;
	this->position.y = newYPos;
	this->updateAllBlockPositions();
}

void block::flagForDelete(){
	this->flaggedForDeletion = true;
}

bool block::pendingDeletion(){
	return this->flaggedForDeletion;
}

void block::think(std::vector<block>& blocks){
	if(this->position.y < BLOCK_GRID_Y - (BLOCK_SIZE * 2)){
		// Time to die, we're too far up
		this->flagForDelete();
	}else{
		// Move down
		if(falling){
			if(this->position.y < BLOCK_GRID_Y + (8 * BLOCK_SIZE)){
				this->position.y += FALL_SPEED;
				this->updateAllBlockPositions();

				// Move as close as possible too any blocks below if we detect
				// a colission
				for(unsigned int i = 0; i < blocks.size(); i++){
					if(blocks[i].id != this->id){
						// If we're not looking at the same block, lets see if they intersect
						if(this->colissionbox.intersects(blocks[i].colissionbox)){
							// Push up if interesecting until there's no longer a colission
							while(this->colissionbox.intersects(blocks[i].colissionbox)){
								this->position.y -= 0.01;
								this->updateAllBlockPositions();
							}
							this->falling = false;
						}
					}
				}
			}else{
				// We've fallen to the lowest part of the field,
				// stop falling
				this->falling = false;
			}
		}else{
			// We're not falling, move up
			this->position.y -= RAISE_SPEED;

			this->updateAllBlockPositions();
		}

		// Update the block beacon
		this->blockBeacon.left = this->position.x - (this->blockBeacon.width / 2);
		this->blockBeacon.top = this->position.y - (this->blockBeacon.height / 2);
	}
}

void block::updateAllBlockPositions(){
	this->colissionbox.left = this->position.x;
	this->colissionbox.top = this->position.y;
	this->colissionbox.width = BLOCK_SIZE;
	this->colissionbox.height = BLOCK_SIZE;
	this->sprite.setPosition(BLOCK_PADDING + colissionbox.left, BLOCK_PADDING + colissionbox.top);
}

sf::Sprite block::getSprite(float interpolation){
	//sf::Vector2f tmpPos = sprite.getPosition();
	//sprite.setPosition(tmpPos.x, tmpPos.y -= (RAISE_SPEED * interpolation));
	return this->sprite;
}