#include "TextureManager.h"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
	sf::Texture texture;

	texture.loadFromFile(filename);

	texturesMap.insert(std::pair<std::string,sf::Texture>(name,texture));
}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return texturesMap.at(texture);
}
