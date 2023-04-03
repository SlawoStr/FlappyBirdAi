#pragma once
#include <SFML/Graphics.hpp>
#include "RandomNumberGenerator.h"

namespace GateSettings
{
	const float DISTANCE_INTERVAL = 100.0f;
	const float FREE_SPACE = 100.0f;
	const float MOVING_SPEED = 10.0f;
	const float PIPE_WIDTH = 20.0f;
	const int UPPER_BOUND = 150;
	const int LOWER_BOUND = 450;
}

class Gate
{
public:
	Gate();

	void render(sf::RenderTarget& target,const sf::Texture&,const sf::Texture&);
	void update();

	bool isOut();
	bool isColliding(const sf::CircleShape& shape);

	float getDistance();

	float getMidPoint();
private:
	sf::RectangleShape pipeUp;
	sf::RectangleShape pipeDown;
	static RandomNumberGenerator numGenerator;
	static float holePosition;
};