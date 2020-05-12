#include <SFML/Graphics.hpp>
using namespace std;
#include <iostream>
#include <vector>
#include "Board.h"

/*
1.) Might need to change bottom board such that it initializes to hidden tiles and as they are revealed change them to revealed 
	tiles.  Right now the debug board has all the tiles revealed regardless and it might need to be different. Ask TA on 4/18/2019.

Written on 4/16/2019 - Simon Frank (fixed)

2.) Memory leak due to flag counter, need to fix.

Written on 4/19/2019 - Simon Frank (fixed)

3.) Try to fix memory allocation upon restarting the game, think it's the top and bottom tile

Written on 4/19/2019 - Simon Frank

4.) Fixed memory allocations for top and bottom, but still have issues with memory allocation. Gains 4MB after starting each game and when game is
	won it rapidly gains memory.

Written on 4/23/2019 - Simon Frank
*/

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	Board gameBoard;
	gameBoard.CreateBackGround();
	gameBoard.InitializeBoard();
	
	bool WonOrLost = false;
	bool gameWon = false;
	bool flagsRevealed = false;
	bool isDebugPressed = false;
	while (window.isOpen())
	{
		if (gameBoard.GetNumberNonMines() <= 0)
		{
			WonOrLost = true;
			gameWon = true;
			isDebugPressed = false;
			if (flagsRevealed == false)
			{
				flagsRevealed = true;
				for (int i = 0; i < gameBoard.GetBombTiles().size(); i++)
				{
					int x = get<0>(gameBoard.GetBombTiles()[i]);
					int y = get<1>(gameBoard.GetBombTiles()[i]);
					//Tile* flag = new Tile("images/flag.png");
					//flag->setPosition(x * 32, y * 32);
					//Tile* tile = new Tile("images/tile_hidden.png");
					//tile->setPosition(x * 32, y * 32);
					gameBoard.GetBoardTop()[x][y] = new Tile("images/flag.png", x * 32, y * 32);
					gameBoard.GetBackground()[x][y] = new Tile("images/tile_hidden.png", x * 32, y * 32);
				}
			}
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && WonOrLost == false)
			{
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						tuple<int, int> location = make_tuple(i, j);
						if (gameBoard.GetBoardBottom()[i][j]->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
							&& !gameBoard.checkRepeat(location, gameBoard.GetFlagLocations()) && gameBoard.checkRepeat(location, gameBoard.GetRevealedTileLocations()) == false)
						{
							gameBoard.RevealTiles(location, gameBoard.GetRevealedTileLocations());
							if (gameBoard.checkRepeat(location, gameBoard.GetBombTiles()) == true)
							{
								WonOrLost = true;
								gameWon = false;
								gameBoard.RevealAllMines();
							}
 						}
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && WonOrLost == false)
			{
				for (int i = 0; i < 25; i++)
				{
					for (int j = 0; j < 16; j++)
					{
						if (gameBoard.GetBoardBottom()[i][j]->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
						{
							tuple<int, int> location = make_tuple(i, j);
							if (gameBoard.checkRepeat(location, gameBoard.GetFlagLocations()) == true)
							{
								gameBoard.RemoveFlag(location);
								delete gameBoard.GetFlags()[i][j];
								//gameBoard.GetBackground()[i][j] = new Tile("images/tile_revealed.png", i * 32, j * 32);;
							}
							else if(gameBoard.checkRepeat(location, gameBoard.GetRevealedTileLocations()) == false)
							{
								gameBoard.GetFlags()[i][j] = new Tile("images/flag.png", i*32,j*32);
								gameBoard.AddFlag(location);
								//gameBoard.GetBackground()[i][j] = new Tile("images/tile_hidden.png", i*32,j*32);
							}
						}
					}
				}
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)) )
				&& gameBoard.GetDebugButton()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)
				&& WonOrLost == false)
			{
				isDebugPressed = !isDebugPressed;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetTest1Button()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.LoadTest(1);
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetTest2Button()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.LoadTest(2);
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetTest3Button()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.LoadTest(3);
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetSmileyFace()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.InitializeBoard();
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetWinFace()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.InitializeBoard();
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
			if ((sf::Mouse::isButtonPressed(sf::Mouse::Left) || (sf::Mouse::isButtonPressed(sf::Mouse::Right)))
				&& gameBoard.GetLoseFace()->GetSprite().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
			{
				gameBoard.InitializeBoard();
				gameWon = false;
				WonOrLost = false;
				isDebugPressed = false;
				flagsRevealed = false;
			}
		}

		window.clear();
		if (isDebugPressed == false)
		{
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 16; j++)
				{
						window.draw(gameBoard.GetBackground()[i][j]->GetSprite());
						window.draw(gameBoard.GetBoardTop()[i][j]->GetSprite());
				}
			}
		}
		else //debug is pressed
		{
			for (int i = 0; i < 25; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					tuple<int, int> location = make_tuple(i, j);
					if (gameBoard.checkRepeat(location, gameBoard.GetBombTiles()) == true
						&& gameBoard.checkRepeat(location, gameBoard.GetFlagLocations()) == false)
					{
						window.draw(gameBoard.GetBackground()[i][j]->GetSprite());
						window.draw(gameBoard.GetBoardBottom()[i][j]->GetSprite());
					}
					else if (gameBoard.checkRepeat(location, gameBoard.GetBombTiles()) == true
						&& gameBoard.checkRepeat(location, gameBoard.GetFlagLocations()) == true)
					{
						window.draw(gameBoard.GetBackground()[i][j]->GetSprite());
						window.draw(gameBoard.GetBoardBottom()[i][j]->GetSprite());
					}
					else
					{
						window.draw(gameBoard.GetBackground()[i][j]->GetSprite());
						window.draw(gameBoard.GetBoardTop()[i][j]->GetSprite());
					}
				}
			}
		}

		window.draw(gameBoard.GetDebugButton()->GetSprite());
		window.draw(gameBoard.GetTest1Button()->GetSprite());
		window.draw(gameBoard.GetTest2Button()->GetSprite());
		window.draw(gameBoard.GetTest3Button()->GetSprite());

		if (WonOrLost == true && gameWon == false)
			window.draw(gameBoard.GetLoseFace()->GetSprite());
		else if(WonOrLost == true && gameWon == true)
			window.draw(gameBoard.GetWinFace()->GetSprite());
		else
			window.draw(gameBoard.GetSmileyFace()->GetSprite());

		if (gameBoard.GetFlagLocations().size() > 0)
		{
			for (int i = 0; i < gameBoard.GetFlagLocations().size(); i++)
			{
				int j = get<0>(gameBoard.GetFlagLocations()[i]);
				int k = get<1>(gameBoard.GetFlagLocations()[i]);
				window.draw(gameBoard.GetFlags()[j][k]->GetSprite());
			}
		}

		string counterString = "";
		vector<Tile*> counterTiles;
		if (gameWon == true)
		{
			counterString = "000";
		}
		else if (gameBoard.GetBombTiles().size() < gameBoard.GetNumberFlags())
		{
			counterString += "-";
			int i = gameBoard.GetNumberFlags() - gameBoard.GetBombTiles().size();
			for (; i < 3; i++)
			{
				counterString += "0";
			}
			counterString += to_string(gameBoard.GetNumberFlags() - gameBoard.GetBombTiles().size());
		}
		else
		{
			int i = to_string(gameBoard.GetBombTiles().size() - gameBoard.GetNumberFlags()).size();
			for (;i < 3;i++)
			{
				counterString += "0";
			}
			counterString += to_string(gameBoard.GetBombTiles().size() - gameBoard.GetNumberFlags());
		}
		counterTiles = gameBoard.GetCounterTile(counterString);
		for (int i = 0; i < counterTiles.size(); i++)
		{
			window.draw(counterTiles[i]->GetSprite());
		}
		window.display();
		for (int i = 0; i < counterTiles.size(); i++)
		{
			delete counterTiles[i];
		}
	}
	return 0;
}