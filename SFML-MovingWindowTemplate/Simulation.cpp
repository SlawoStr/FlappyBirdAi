#include "Simulation.h"
#include <chrono>
#include <iostream>

Simulation::Simulation(sf::Vector2u windowSize) : window(sf::VideoMode(windowSize.x,windowSize.y),"Simulation"), textArea(sf::Vector2f(400.0f,20.f),sf::Vector2f(40.0f,60.0f),"0")
{
	// Framerate limit
	window.setFramerateLimit(144);

	loadTextures();
	bestScore = 0;

	gateDeq.push_back(Gate());
	for (int i = 0; i < Settings::POPULATION_SIZE; i++)
	{
		birdList.push_back(Bird(i, textureManager.getRef("Bird")));
	}
	birdScore.resize(Settings::POPULATION_SIZE);
	for (int i = 0; i < birdList.size(); i++)
	{
		birdScore[i] = std::make_pair(0, i);
	}

	spawnRatio = Settings::SPAWN_RATIO;
	connector.createPopulation(Settings::POPULATION_SIZE);
}

void Simulation::run()
{
	while (window.isOpen())
	{
		window.clear(sf::Color::White);
		draw();
		window.display();
		update();
		pollEvent();
	}
}

void Simulation::pollEvent()
{
	sf::Event e;
	while (window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Space)
			{
				(*birdList.begin()).jump();
			}
		}
	}
}

void Simulation::update()
{
	currentScore++;
	textArea.setText(std::to_string(currentScore));
	bool isAlive = false;
	// If Gate is out of the screen remove from deq
	if (gateDeq.front().isOut())
	{
		gateDeq.pop_front();
	}
	for (auto it = gateDeq.begin(); it != gateDeq.end(); ++it)
	{
		(*it).update();
	}

	float gateDistance = gateDeq.front().getDistance();
	float midPointDistance = gateDeq.front().getMidPoint();

	auto t_start = std::chrono::high_resolution_clock::now();

	for (auto it = birdList.begin(); it != birdList.end(); ++it)
	{
		if ((*it).isAlive())
		{
			birdScore[(*it).getId()].first = currentScore;
			if (gateDeq.front().isColliding((*it).getCircle()))
			{
				(*it).killBird();
			}
			else
			{
				bool isJumping = connector.predictJump((*it).getId(), (midPointDistance - (*it).getCircle().getGlobalBounds().top - (*it).getCircle().getRadius()) / 500.0f, gateDistance / 1000.0f, (*it).getVelocity() / 15.0f);
				if (isJumping)
				{
					(*it).jump();
				}
				(*it).update();
				isAlive = true;
			}
		}
	}

	spawnRatio--;
	if (spawnRatio == 0)
	{
		gateDeq.push_back(Gate());
		spawnRatio = Settings::SPAWN_RATIO;
	}
	if (!isAlive)
	{
		std::nth_element(birdScore.begin(), birdScore.begin() + 1, birdScore.end(), [](std::pair<int,int> lhs, std::pair<int,int> rhs){return lhs.first > rhs.first; });

		if (bestScore < birdScore[0].first)
			bestScore = birdScore[0].first;
		connector.mutatePopulation(birdScore[0].second, birdScore[1].second);

		std::cout << "Best score: " << bestScore << std::endl;

		resetSimulation();
	}
}

void Simulation::draw()
{
	sf::Sprite background;
	background.setPosition(sf::Vector2f(0.0f, 0.0f));
	background.setTexture(textureManager.getRef("Background"));
	background.setScale(window.getSize().x / background.getLocalBounds().width, window.getSize().y / background.getLocalBounds().height);
	window.draw(background);

	for (auto it = gateDeq.begin(); it != gateDeq.end(); ++it)
	{
		(*it).render(window, textureManager.getRef("PipeDown"), textureManager.getRef("PipeUp"));
	}

	for (auto it = birdList.begin(); it != birdList.end(); ++it)
	{
		(*it).render(window);
	}

	textArea.render(window);
}

void Simulation::loadTextures()
{
	textureManager.loadTexture("Background", "Images/background.png");
	textureManager.loadTexture("Bird", "Images/bird.png");
	textureManager.loadTexture("PipeUp", "Images/pipeup.png");
	textureManager.loadTexture("PipeDown", "Images/pipedown.png");
}

void Simulation::resetSimulation()
{
	// Restore starting values to birds
	for (auto it = birdList.begin(); it != birdList.end(); it++)
	{
		(*it).resetBird();
	}
	// Reset score
	for (int i = 0; i < birdScore.size(); i++)
	{
		birdScore[i].first = 0;
		birdScore[i].second = i;
	}

	gateDeq.clear();
	gateDeq.push_back(Gate());

	spawnRatio = Settings::SPAWN_RATIO;

	currentScore = 0;
	textArea.setText(std::to_string(currentScore));
}
