#include "fieldmanager.h"

void fieldManager::swapBlocks(std::vector<block>& blocks, UI& ui){
	int block1 = -1;
	int xpos1 = 0;
	int block2 = -1;
	int xpos2 = 0;

	for(int i = 0; i < blocks.size(); i++){
		// Find the block that's at the rect's point
		//printf("%f,%f -> %f,%f\n", blocks[i].blockBeacon.left, blocks[i].blockBeacon.top, ui.getColRect1().left, ui.getColRect1().top);
		//if(blocks[i].xPos() == rect.left && blocks[i].yPos() == rect.top){
		//if(ui.getColRect1().intersects(blocks[i].blockBeacon)){
		if(ui.getColRect1().contains(blocks[i].xPos(), blocks[i].yPos())){
			block1 = i;
			xpos1 = blocks[i].xPos();
			i = blocks.size();
		}
	}

	for(int i = 0; i < blocks.size(); i++){
		// Find the block that's to the right of the rect's point
		printf("%f,%f -> %f,%f\n", blocks[i].blockBeacon.left, blocks[i].blockBeacon.top, ui.getColRect1().left, ui.getColRect1().top);
		//if(blocks[i].xPos() == rect.left+BLOCK_SIZE && blocks[i].yPos() == rect.top){
		//if(ui.getColRect2().intersects(blocks[i].blockBeacon)){
		if(ui.getColRect2().contains(blocks[i].xPos(), blocks[i].yPos())){
			block2 = i;
			xpos2 = blocks[i].xPos();
			i = blocks.size();
		}
	}

	if(block1 != -1 && block2 != -1){
		blocks[block1].setXPos(xpos2);
		blocks[block2].setXPos(xpos1);

		// Update them as falling
		blocks[block1].falling = true;
		blocks[block2].falling = true;
	}else if(block1 != -1 || block2 != -1){
		if(block1 != -1){
			blocks[block1].setXPos(blocks[block1].xPos() + BLOCK_SIZE);

		// Update it as falling
		blocks[block1].falling = true;
		}else{
			blocks[block2].setXPos(blocks[block2].xPos() - BLOCK_SIZE);

		// Update it as falling
		blocks[block2].falling = true;
		}
	}else{
		printf("3 - Both blocks empty\n");
	}
}

void fieldManager::pollField(std::vector<block>& blocks){
	// Check Horizontal
	std::vector<float> yPositions;

	// Populate our positions list with coordinates of blocks first
	for(int i = 0; i < blocks.size(); i++){
		float curBlockYPos = blocks[i].yPos();
		if(curBlockYPos > BLOCK_GRID_Y - BLOCK_SIZE){
			// Go through our float vector to see if the position we
			// have now isn't already added to it
			bool found = false;
			for(int j = 0; j < yPositions.size(); j++){
				if(curBlockYPos == yPositions[i]){
				 found = true;
				}
			}
			
			// If the value was not yet in there, add it
			if(!found){
				yPositions.push_back(curBlockYPos);
			}
		}

		// Now check for Horizontal matches
		for(int i = 0; i < yPositions.size(); i++){
			// In the vector the blocks are one after another, since we create
			// a whole row at once, in order. So a whole row could for example
			// be:
			// blocks[2] -> blocks[3] -> blocks[4] -> blocks[5], etc
			// So you could-- you know, you'll remember it tomorrow, for easy
			// value pulling and matching!
		
		}
	}
}