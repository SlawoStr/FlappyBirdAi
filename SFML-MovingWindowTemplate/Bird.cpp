#include "Bird.h"

Bird::Bird(int id, const sf::Texture& texture) : id(id)
{
	resetBird();
	body.setTexture(&texture);
}

void Bird::render(sf::RenderTarget& target)
{
	target.draw(body);
}

void Bird::jump()
{
	velocity = -20;
}

void Bird::update()
{
	velocity += gravity;
	velocity *= 0.9f;
	if (velocity > 15)
		velocity = 15;
	body.move(sf::Vector2f(0.0f, velocity));
	// Reached top screen bound
	if (body.getPosition().y + body.getRadius() * 2 >= 600.0f)
	{
		body.setPosition(15.0f, 580.0f);
		velocity = 0;
		alive = false;
	}
	// Reached bot screen bound
	else if (body.getPosition().y <= 0)
	{
		body.setPosition(sf::Vector2f(15.0f, 0.0f));
		velocity = 0;
		alive = false;
	}
}

void Bird::resetBird()
{
	this->alive = true;

	this->gravity = 1;
	this->velocity = 0;

	body.setPosition(sf::Vector2f(15.0f, 300.0f));
	body.setRadius(10.0f);
	body.setFillColor(sf::Color::Green);
}
