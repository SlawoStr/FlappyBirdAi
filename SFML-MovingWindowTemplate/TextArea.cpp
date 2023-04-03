#include "TextArea.h"
#include <iostream>

TextArea::TextArea(sf::Vector2f position, sf::Vector2f size,std::string msg)
{
	if (!font.loadFromFile("Tusz.ttf"))
	{
		std::cout << "Font not found in program folder" << std::endl;
	}

	//Text settings
	text.setString(msg);
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(20);
	text.setFont(font);
	text.setPosition(sf::Vector2f(position.x + size.x / 2.0f - text.getGlobalBounds().width / 2.0f, position.y + size.y / 2.0f - text.getGlobalBounds().height / 2.0f));
}

void TextArea::render(sf::RenderTarget& target)
{
	target.draw(text);
}

void TextArea::setText(const std::string& msg)
{
	text.setString(msg);
}
