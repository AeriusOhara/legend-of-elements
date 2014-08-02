#include <SFML/Window.hpp>
#include <vector>	
#include "fieldmanager.h"

int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	window.setFramerateLimit(60);

	srand(time(NULL));

	blockSprites sprites;

	fieldManager fieldmanager;

	std::vector<block> blocks;

	//std::vector<blockBeacon> beacons;

	// The UI
	UI ui;
	ui.init(blocks);

	// Whenever this step reaches 20, it will add a new row at the bottom
	float step = 20;

	// Timer for spawning ice creams
	sf::Clock clock;

	// DeltaTime implementation?
	sf::Clock dtclock;
	sf::Time dttimer;
	dttimer = dtclock.getElapsedTime();
	const int TICKS_PER_SECOND = 60;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 1;
	unsigned int next_game_tick = dttimer.asMilliseconds();
	int loops;
	float interpolation;

	// run the program as long as the window is open
	while (window.isOpen()){
		loops = 0;
		dttimer = dtclock.getElapsedTime();

		while(dttimer.asMilliseconds() > next_game_tick && loops < MAX_FRAMESKIP)
		{
			///////////////////////////////
			// Logic
			///////////////////////////////
			// check all the window's events that were triggered since the last iteration of the loop
			sf::Event event;
			while (window.pollEvent(event)){
				// "close requested" event: we close the window
				if (event.type == sf::Event::Closed){
					window.close();
				}
				if(event.type == sf::Event::KeyPressed){
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
						ui.moveLeft(true, blocks);
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
						ui.moveLeft(false, blocks);
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
						ui.moveUp(true, blocks);
					}else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
						ui.moveUp(false, blocks);
					}

					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
						fieldmanager.swapBlocks(blocks, ui);
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){

					}
				}
			}
			
			// Check if we should be spawning more blocks at the bottom
			step += RAISE_SPEED;
			if(step >= 20){
				// Spawn 5 blocks at the bottom
				for(int i = 0; i < FIELD_SIZE; i++){
					block newBlock(rand()%PINK, i, 8, sprites, blocks);
					blocks.push_back(newBlock);
				}
				step = 0;
			}

			for(unsigned int i = 0; i < blocks.size(); i++){
				blocks[i].think(blocks);

				if(blocks[i].pendingDeletion()){
					// Destroy the block
					blocks.erase(blocks.begin() + i);
				}
			}

			// UI Updates
			ui.think(blocks);

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		interpolation = float(dttimer.asMilliseconds() + SKIP_TICKS - next_game_tick ) / float(SKIP_TICKS);
	
		///////////////////////////////
		// Render
		///////////////////////////////
		window.clear();

		for(unsigned int i = 0; i < blocks.size(); i++){
			window.draw(blocks[i].getSprite(interpolation));
		}

		// Draw the background and selector
		window.draw(ui.background);
		window.draw(ui.selector);

		/* colission rect render
		sf::RectangleShape rect1(sf::Vector2f(10, 10));
		sf::RectangleShape rect2(sf::Vector2f(10, 10));
		rect1.setPosition(ui.getColRect1().left, ui.getColRect1().top);
		rect2.setPosition(ui.getColRect2().left, ui.getColRect2().top);
		rect1.setFillColor(sf::Color::Red);
		rect2.setFillColor(sf::Color::Red);
		window.draw(rect1);
		window.draw(rect2);
		for(unsigned int i = 0; i < blocks.size(); i++){
			sf::RectangleShape rect3(sf::Vector2f(10, 10));
			rect3.setPosition(blocks[i].blockBeacon.left, blocks[i].blockBeacon.top);
			window.draw(rect3);
		}*/

		window.display();
	}

	return 0;
}