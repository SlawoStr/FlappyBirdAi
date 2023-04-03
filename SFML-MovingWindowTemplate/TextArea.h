#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextArea
{
public:
	TextArea(sf::Vector2f position,sf::Vector2f size,std::string msg);

	void render(sf::RenderTarget& target);

	void setText(const std::string& msg);

private:
	sf::Text text;
	sf::Font font;
};