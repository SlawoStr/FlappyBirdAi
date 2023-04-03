#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>


class TextureManager
{
public:
	TextureManager() {}

	void loadTexture(const std::string& name, const std::string& filename);

	sf::Texture& getRef(const std::string& texture);

private:
	std::map<std::string, sf::Texture> texturesMap;
};