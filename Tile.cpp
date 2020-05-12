#include "Tile.h"

Tile::Tile(string fileName)
{
	this->texture.loadFromFile(fileName);
	this->sprite.setTexture(texture);
}

Tile::Tile(string fileName, int x, int y)
{
	this->texture.loadFromFile(fileName);
	this->sprite.setTexture(texture);
	this->sprite.setPosition(x, y);
}

sf::Sprite& Tile::GetSprite()
{
	return this->sprite;
}

void Tile::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}