#include "Gate.h"
#include <iostream>

bool checkOverlap(int R, int Xc, int Yc, int X1, int Y1, int X2, int Y2)
{
	int Xn = std::max(X1, std::min(Xc, X2));
	int Yn = std::max(Y1, std::min(Yc, Y2));

	int Dx = Xn - Xc;
	int Dy = Yn - Yc;
	return (Dx * Dx + Dy * Dy) <= R * R;
}

Gate::Gate()
{
	int holeOffset = numGenerator.getRandomInt();

	if (holePosition + holeOffset > GateSettings::LOWER_BOUND || holePosition + holeOffset < GateSettings::UPPER_BOUND)
	{
		holePosition -= holeOffset;
	}
	else
	{
		holePosition += holeOffset;
	}

	// Starting position of pipes
	pipeDown.setPosition(sf::Vector2f(1000.0f, 0.0f));
	pipeUp.setPosition(sf::Vector2f(1000.f, holePosition));

	pipeDown.setSize(sf::Vector2f(GateSettings::PIPE_WIDTH,holePosition - GateSettings::FREE_SPACE));
	pipeUp.setSize(sf::Vector2f(20.0f,1000.0f));
}

void Gate::render(sf::RenderTarget& target, const sf::Texture& textureUp, const sf::Texture& textureDown)
{
	pipeDown.setTexture(&textureUp);
	pipeUp.setTexture(&textureDown);
	target.draw(pipeUp);
	target.draw(pipeDown);
}

void Gate::update()
{
	pipeUp.move(sf::Vector2f(-GateSettings::MOVING_SPEED, 0.0f));
	pipeDown.move(sf::Vector2f(-GateSettings::MOVING_SPEED, 0.0f));
}

bool Gate::isOut()
{
	return pipeUp.getPosition().x + GateSettings::PIPE_WIDTH < 0.0f;
}

bool Gate::isColliding(const sf::CircleShape& shape)
{
	if (checkOverlap((int)shape.getRadius(), (int)shape.getPosition().x, (int)shape.getPosition().y, (int)pipeUp.getGlobalBounds().left, (int)pipeUp.getGlobalBounds().top, int(pipeUp.getGlobalBounds().left + pipeUp.getGlobalBounds().width), int(pipeUp.getGlobalBounds().top + pipeUp.getGlobalBounds().height)))
	{
		return true;
	}
	if (checkOverlap((int)shape.getRadius(), (int)shape.getPosition().x, (int)shape.getPosition().y, (int)pipeDown.getGlobalBounds().left, (int)pipeDown.getGlobalBounds().top, int(pipeDown.getGlobalBounds().left + pipeDown.getGlobalBounds().width), int(pipeDown.getGlobalBounds().top + pipeDown.getGlobalBounds().height)))
	{
		return true;
	}
	return false;
}

float Gate::getDistance()
{
	return pipeUp.getPosition().x + 20;
}

float Gate::getMidPoint()
{
	return (pipeUp.getGlobalBounds().top + pipeDown.getGlobalBounds().top + pipeDown.getGlobalBounds().height) / 2;
}


RandomNumberGenerator Gate::numGenerator(-50, 50);

float Gate::holePosition(300.0f);