#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

class Tile
{
	sf::Sprite sprite;
	sf::Texture texture;
public:
	Tile(string fileName);
	Tile(string fileName, int , int);
	sf::Sprite& GetSprite();
	void setPosition(float x, float y);
};

