#pragma once
#include <SFML/Graphics.hpp>


class Bird
{
public:
	Bird(int id,const sf::Texture& texture);

	void render(sf::RenderTarget& target);
	void jump();
	void update();
	bool isAlive()const { return alive; }
	void killBird() { alive = false; body.setFillColor(sf::Color::Red); }
	void resetBird();
	// Getters
	sf::CircleShape getCircle() { return body; }
	float getVelocity() { return velocity; }
	int getId()const { return id; }
private:
	sf::CircleShape body;
	int id;
	float gravity;
	float velocity;
	bool alive;
};