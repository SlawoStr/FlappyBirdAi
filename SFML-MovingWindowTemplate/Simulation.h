#pragma once
#include <SFML/Graphics.hpp>
#include <deque>
#include <list>
#include <vector>
#include "TextureManager.h"
#include "PythonConnector.h"
#include "TextArea.h"
#include "Gate.h"
#include "Bird.h"

namespace Settings
{
	const int POPULATION_SIZE = 100;
	const int SPAWN_RATIO = 30;
}

class Simulation
{
public:
	Simulation(sf::Vector2u windowSize);
	void run();
private:
	void pollEvent();
	void update();
	void draw();

	void loadTextures();
	void resetSimulation();
private:
	sf::RenderWindow window;
	TextureManager textureManager;
	TextArea textArea;
	PythonConnector connector;
	std::deque<Gate> gateDeq;
	std::list<Bird> birdList;
	std::vector<std::pair<int,int>> birdScore;
	int spawnRatio;
	int currentScore;
	int bestScore;
};
