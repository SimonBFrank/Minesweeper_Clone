#include "Board.h"
#include <ctime>
#include <fstream>

Board::Board()
{
	debugButton = new Tile("images/debug.png");
	this->debugButton->setPosition(432, 512);
	Test1 = new Tile("images/test_1.png");
	this->Test1->setPosition(496, 512);
	Test2 = new Tile("images/test_2.png");
	this->Test2->setPosition(560, 512);
	Test3 = new Tile("images/Test_3.png");
	this->Test3->setPosition(624, 512);
	SmileyFace = new Tile("images/face_happy.png");
	this->SmileyFace->setPosition(304, 512);
	LoseFace = new Tile("images/face_lose.png");
	this->LoseFace->setPosition(304, 512);
	WinFace = new Tile("images/face_win.png");
	this->WinFace->setPosition(304, 512);
}

void Board::SetTile(int x, int y, Tile* tempTile)
{
	this->topTiles[x][y] = tempTile;
}

void Board::AddFlag(tuple<int, int>& flag)
{
	this->flagLocations.push_back(flag);
	this->numberFlags++;
}

void Board::RemoveFlag(tuple<int, int>& location)
{
	RemoveTuple(location);
	this->numberFlags--;
}

void Board::InitializeBoard()
{
	this->flagLocations.clear();
	this->numberFlags = 0;
	for (int i = 0; i < bottomTiles.size(); i++)
	{
		for (int j = 0; j < bottomTiles[0].size(); j++)
		{
			delete bottomTiles[i][j];
		}
	}
	bottomTiles.clear();
	for (int i = 0; i < topTiles.size(); i++)
	{
		for (int j = 0; j < topTiles[0].size(); j++)
		{
			tuple<int, int> location = make_tuple(i, j);
			if(checkRepeat(location, this->revealedTiles) == false && checkRepeat(location, this->bombTiles) == false)
				delete topTiles[i][j];
		}
	}
	this->bombTiles.clear();
	topTiles.clear();
	this->revealedTiles.clear();
	this->flagTiles.clear();

	for (int i = 0; i < 25; i++) //sets top board
	{
		this->topTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			Tile* tile = new Tile("images/tile_hidden.png");
			tile->setPosition(i * 32, j * 32);
			this->topTiles[i].push_back(tile);
		}
	}
	for (int i = 0; i < 25; i++) //Creates all the locations for bottom board
	{
		this->bottomTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			Tile* tile = new Tile("images/tile_revealed.png"); 
			tile->setPosition(i * 32, j * 32);
			this->bottomTiles[i].push_back(tile);
		}
	}
	flagTiles.resize(25);
	for (int i = 0; i < 25; i++)
	{
		this->flagTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			this->flagTiles[i].push_back(new Tile("images/tile_revealed.png", i * 32, j * 32));
		}
	}
	ResetBackground();
	RandomizeBombs();
	SetBombs();
	SetNumbers();
	this->nonMineTilesRemaining = 400 - this->bombTiles.size();

	for (int i = 0; i < GetBombTiles().size(); i++)
	{
		int j = get<0>(GetBombTiles()[i]);
		int k = get<1>(GetBombTiles()[i]);
		GetBackground()[j][k] = new Tile("images/tile_hidden.png", j * 32, k * 32);
	}
}

void Board::CreateBackGround()
{
	for (int i = 0; i < 25; i++) 
	{
		this->background.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			//Tile* tile = new Tile("images/tile_revealed.png");
			//tile->setPosition(i * 32, j * 32);
			this->background[i].push_back(new Tile("images/tile_revealed.png", i*32, j*32));
		}
	}
}

void Board::ResetBackground()
{
	for (int i = 0; i < background.size(); i++)
	{
		for (int j = 0; j < background[0].size(); j++)
		{
			delete background[i][j];
		}
	}
	background.clear();
	CreateBackGround();
}

vector< vector<Tile*>>& Board::GetBackground()
{
	return this->background;
}

vector< vector<Tile*>>& Board::GetFlags()
{
	return this->flagTiles;
}

vector< vector<Tile*>>& Board::GetBoardTop()
{
	return this->topTiles;
}

vector< vector<Tile*>>& Board::GetBoardBottom()
{
	return this->bottomTiles;
}

vector<tuple<int, int>>& Board::GetBombTiles()
{
	return this->bombTiles;
}

vector<tuple<int, int>>& Board::GetRevealedTileLocations()
{
	return this->revealedTiles;
}

Tile* Board::GetDebugButton()
{
	return this->debugButton;
}

Tile* Board::GetTest1Button()
{
	return this->Test1;
}

Tile* Board::GetTest2Button()
{
	return this->Test2;
}

Tile* Board::GetTest3Button()
{
	return this->Test3;
}

Tile* Board::GetLoseFace()
{
	return this->LoseFace;
}

Tile* Board::GetWinFace()
{
	return this->WinFace;
}

Tile* Board::GetSmileyFace()
{
	return this->SmileyFace;
}

vector<tuple<int, int>>& Board::GetFlagLocations()
{
	return this->flagLocations;
}

int& Board::GetNumberFlags()
{
	return this->numberFlags;
}

int& Board::GetNumberNonMines()
{
	return this->nonMineTilesRemaining;
}

void Board::RandomizeBombs()
{
	
	srand((unsigned int)time(0));
	for (int i = 0; i < 50;)
	{
		int randomX = rand() % 25;
		int randomY = rand() % 16;
		tuple<int, int> potentialBomb = make_tuple(randomX, randomY);
		if (checkRepeat(potentialBomb, this->bombTiles) == false)
		{
			this->bombTiles.push_back(potentialBomb);
			i++;
		}
	}
}

bool Board::checkRepeat(tuple<int, int>& inputBomb, vector< tuple<int, int>>& bombVec)
{
	if (bombVec.size() == 0)
	{
		return false;
	}
	for (int i = 0; i< bombVec.size(); i++)
	{
		if (bombVec[i] == inputBomb)
		{
			return true;
		}
	}
	return false;
}

void Board::RemoveTuple(tuple<int, int>& removeTuple)
{
	vector<tuple<int, int>> temp;
	for (int j = 0; j < this->flagLocations.size(); j++)
	{
		if (this->flagLocations[j] == removeTuple)	
		{ }
		else
		{
			temp.push_back(this->flagLocations[j]);
		}
	}
	this->flagLocations.clear();
	this->flagLocations = temp;
}

void Board::SetBombs()
{
	for (int i = 0; i < 50; i++)
	{
		//Tile* tile = new Tile("images/mine.png");
		//tile->setPosition(get<0>(bombTiles[i]) * 32, get<1>(bombTiles[i]) * 32);
		this->bottomTiles[get<0>(bombTiles[i])][get<1>(bombTiles[i])] = new Tile("images/mine.png", get<0>(bombTiles[i]) * 32, get<1>(bombTiles[i]) * 32);
	}
}

int Board::NumberBombsAdjacent(tuple<int, int>& tempLocation)
{
	int numberSurrounding = 0;
	int i = get<0>(tempLocation);
	int j = get<1>(tempLocation);
	if (i < 0 || i > 24) //tile doesn't exist
		return -1;
	if (j < 0 || j > 15)
		return -1;
	if (checkRepeat(tempLocation, GetBombTiles()) == false) //checks to see if bomb, if not then count around
	{
		if (i == 0 && j == 0)
		{
			tuple<int, int> tempE = make_tuple(i+1, j);
			tuple<int, int> tempS = make_tuple(i, j+1);
			tuple<int, int> tempSE = make_tuple(i+1, j + 1);
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (i == 0 && j == 15)
		{
			tuple<int, int> tempE = make_tuple(i + 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempNE = make_tuple(i + 1, j + 1);
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (i == 24 && j == 0)
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempS = make_tuple(i, j + 1);
			tuple<int, int> tempSW = make_tuple(i - 1, j + 1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (i == 24 && j == 15)
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempNW = make_tuple(i - 1, j - 1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (i == 0 && j != 0 && j != 15)
		{
			tuple<int, int> tempE = make_tuple(i + 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempS = make_tuple(i, j + 1);
			tuple<int, int> tempNE = make_tuple(i + 1, j - 1);
			tuple<int, int> tempSE = make_tuple(i + 1, j + 1);
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (i == 24 && j != 15 && j != 0)
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempS = make_tuple(i, j + 1);
			tuple<int, int> tempNW = make_tuple(i - 1, j - 1);
			tuple<int, int> tempSW = make_tuple(i - 1, j + 1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (j == 0 && i != 0 && i != 24)
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempE = make_tuple(i + 1, j);
			tuple<int, int> tempS = make_tuple(i, j + 1);
			tuple<int, int> tempSW = make_tuple(i - 1, j+1);
			tuple<int, int> tempSE = make_tuple(i + 1, j+1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else if (j == 15 && i != 0 && i != 24)
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempE = make_tuple(i + 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempNW = make_tuple(i - 1, j-1);
			tuple<int, int> tempNE = make_tuple(i + 1, j-1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
		else
		{
			tuple<int, int> tempW = make_tuple(i - 1, j);
			tuple<int, int> tempE = make_tuple(i + 1, j);
			tuple<int, int> tempN = make_tuple(i, j - 1);
			tuple<int, int> tempS = make_tuple(i, j + 1);
			tuple<int, int> tempNW = make_tuple(i - 1, j-1);
			tuple<int, int> tempNE = make_tuple(i + 1, j-1);
			tuple<int, int> tempSE = make_tuple(i - 1, j + 1);
			tuple<int, int> tempSW = make_tuple(i + 1, j + 1);
			if (checkRepeat(tempW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempN, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempS, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempNE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSE, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
			if (checkRepeat(tempSW, this->bombTiles) == true)
			{
				numberSurrounding++;
			}
		}
	}
	return numberSurrounding;
}

void Board::SetNumbers()
{
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			tuple<int, int> location = make_tuple(i, j);
			if (checkRepeat(location, this->bombTiles) == false)
			{
				if (NumberBombsAdjacent(location) != 0)
				{
					string fileName = "images/number_" + to_string(NumberBombsAdjacent(location)) + ".png";
					//Tile* tile = new Tile(fileName);
					//tile->setPosition(i * 32, j * 32);
					this->bottomTiles[i][j] = new Tile(fileName, i*32,j*32);
				}
			}
		}
	}
}

void Board::RevealTilesNorth(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> North = make_tuple(i, j - 1);
	if (NumberBombsAdjacent(North) == 0 && j != 0 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(North, tuplesChecked) == false)
		{
			RevealTiles(North, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(North) != 0 && checkRepeat(North, GetBombTiles()) == false && j != 0 && checkRepeat(North, GetFlagLocations()) == false
		&& checkRepeat(North, tuplesChecked) == false)
	{
		SetTile(i, j-1, GetBoardBottom()[i][j-1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(North);
	}
}

void Board::RevealTilesSouth(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> South = make_tuple(i, j + 1);
	if (NumberBombsAdjacent(South) == 0 && j != 15 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(South, tuplesChecked) == false)
		{
			RevealTiles(South, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(South) != 0 && checkRepeat(South, GetBombTiles()) == false && j != 15 && checkRepeat(South, GetFlagLocations()) == false
		&& checkRepeat(South, tuplesChecked) == false)
	{
		SetTile(i, j+1, GetBoardBottom()[i][j+1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(South);
	}
}

void Board::RevealTilesWest(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> West = make_tuple(i - 1, j);
	if (NumberBombsAdjacent(West) == 0 && i != 0 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(West, tuplesChecked) == false)
		{
			RevealTiles(West, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(West) != 0 && checkRepeat(West, GetBombTiles()) == false && i != 0 && checkRepeat(West, GetFlagLocations()) == false
		&& checkRepeat(West, tuplesChecked) == false)
	{
		SetTile(i-1, j, GetBoardBottom()[i-1][j]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(West);
	}
}

void Board::RevealTilesEast(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> East = make_tuple(i + 1, j);
	if (NumberBombsAdjacent(East) == 0 && i != 24 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(East, tuplesChecked) ==  false)
		{
			RevealTiles(East, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(East) != 0 && checkRepeat(East, GetBombTiles()) == false && i != 24 && checkRepeat(East, GetFlagLocations()) == false
		&& checkRepeat(East, tuplesChecked) == false)
	{
		SetTile(i+1, j, GetBoardBottom()[i+1][j]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(East);
	}
}

void Board::RevealTilesNorthWest(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{	
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> NorthWest = make_tuple(i - 1, j - 1);
	if (NumberBombsAdjacent(NorthWest) == 0 && i != 0 && j != 0 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(NorthWest, tuplesChecked) ==  false)
		{
			RevealTiles(NorthWest, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(NorthWest) != 0 && checkRepeat(NorthWest, GetBombTiles()) == false && i != 0 && j != 0 && checkRepeat(NorthWest, GetFlagLocations()) == false
		&& checkRepeat(NorthWest, tuplesChecked) == false)
	{
		SetTile(i-1, j-1, GetBoardBottom()[i-1][j-1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(NorthWest);
	}
}

void Board::RevealTilesNorthEast(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> NorthEast = make_tuple(i + 1, j - 1);
	if (NumberBombsAdjacent(NorthEast) == 0 && i != 0 && j != 15 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(NorthEast, tuplesChecked) ==  false)
		{
			RevealTiles(NorthEast, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(NorthEast) != 0 && checkRepeat(NorthEast, GetBombTiles()) == false && i != 24 && j != 0 && checkRepeat(NorthEast, GetFlagLocations()) == false
		&& checkRepeat(NorthEast, tuplesChecked) == false)
	{
		SetTile(i+1, j-1, GetBoardBottom()[i+1][j-1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(NorthEast);
	}
}

void Board::RevealTilesSouthWest(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> SouthWest = make_tuple(i - 1, j + 1);
	if (NumberBombsAdjacent(SouthWest) == 0 && i != 0 && j != 0 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (checkRepeat(SouthWest, tuplesChecked) == false)
		{
			RevealTiles(SouthWest, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(SouthWest) != 0 && checkRepeat(SouthWest, GetBombTiles()) == false && i != 0 && j != 15 && checkRepeat(SouthWest, GetFlagLocations()) == false
		&& checkRepeat(SouthWest, tuplesChecked) == false)
	{
		SetTile(i-1, j+1, GetBoardBottom()[i-1][j+1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(SouthWest);
	}
}

void Board::RevealTilesSouthEast(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	int i = get<0>(location);
	int j = get<1>(location);
	tuple<int, int> SouthEast = make_tuple(i + 1, j + 1);
	if (NumberBombsAdjacent(SouthEast) == 0 && i != 24 && j != 15 && checkRepeat(location, GetFlagLocations()) == false)
	{
		if (NumberBombsAdjacent(SouthEast) == 0 && !checkRepeat(SouthEast, tuplesChecked))
		{
			RevealTiles(SouthEast, tuplesChecked);
		}
	}
	else if (NumberBombsAdjacent(SouthEast) != 0 && checkRepeat(SouthEast, GetBombTiles()) == false && i != 24 && j != 15 && checkRepeat(SouthEast, GetFlagLocations()) == false
		&& checkRepeat(SouthEast, tuplesChecked) == false)
	{
		SetTile(i+1, j+1, GetBoardBottom()[i+1][j+1]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(SouthEast);
	}
}

void Board::RevealTiles(tuple<int, int>& location, vector<tuple<int, int>>& tuplesChecked)
{
	if (checkRepeat(location, tuplesChecked) == false && checkRepeat(location, GetBombTiles()) == false && checkRepeat(location, GetFlagLocations()) == false
		&& NumberBombsAdjacent(location) == 0)
	{
		int i = get<0>(location);
		int j = get<1>(location);
		SetTile(i, j, GetBoardBottom()[i][j]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(location);
			
		if (NumberBombsAdjacent(location) == 0)
		{
			RevealTilesNorth(location, tuplesChecked);
			RevealTilesNorthWest(location, tuplesChecked);
			RevealTilesNorthEast(location, tuplesChecked);
			RevealTilesSouth(location, tuplesChecked);
			RevealTilesSouthWest(location, tuplesChecked);
			RevealTilesSouthEast(location, tuplesChecked);
			RevealTilesEast(location, tuplesChecked);
			RevealTilesWest(location, tuplesChecked);
		}
	}
	else if (checkRepeat(location, tuplesChecked) == false && checkRepeat(location, GetBombTiles()) == false && checkRepeat(location, GetFlagLocations()) == false)
	{
		int i = get<0>(location);
		int j = get<1>(location);
		SetTile(i, j, GetBoardBottom()[i][j]);
		this->nonMineTilesRemaining--;
		tuplesChecked.push_back(location);
	}
}

void Board::RevealAllMines()
{
	for (int i = 0; i < bombTiles.size(); i++)
	{
		int j = get<0>(bombTiles[i]);
		int k = get<1>(bombTiles[i]);
		topTiles[j][k] = bottomTiles[j][k];
	}
}

vector<Tile*> Board::GetCounterTile(string numberFlags)
{
	int xPos = 0;
	vector<Tile*> counterReturned;
	for (int i = 0; i < numberFlags.length(); i++)
	{
		if (numberFlags[i] == '-')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(210, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '1')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(21, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '2')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(42, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '3')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(63, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '4')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(84, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '5')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(105, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '6')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(126, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '7')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(147, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '8')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(168, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '9')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(189, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
		else if (numberFlags[i] == '0')
		{
			Tile* counterTile = new Tile("images/digits.png");
			counterTile->setPosition(xPos, 512);
			counterTile->GetSprite().setTextureRect(sf::IntRect(0, 0, 21, 32));
			counterReturned.push_back(counterTile);
			xPos += 21;
		}
	}
	return counterReturned;
}

void Board::LoadTest(int testNumber)
{
	this->flagLocations.clear();
	this->numberFlags = 0;
	for (int i = 0; i < bottomTiles.size(); i++)
	{
		for (int j = 0; j < bottomTiles[0].size(); j++)
		{
			delete bottomTiles[i][j];
		}
	}
	bottomTiles.clear();
	for (int i = 0; i < topTiles.size(); i++)
	{
		for (int j = 0; j < topTiles[0].size(); j++)
		{
			tuple<int, int> location = make_tuple(i, j);
			if (checkRepeat(location, this->revealedTiles) == false && checkRepeat(location, this->bombTiles) == false)
				delete topTiles[i][j];
		}
	}
	topTiles.clear();
	this->revealedTiles.clear();
	this->bombTiles.clear();
	this->flagTiles.clear();
	ResetBackground();
	for (int i = 0; i < 25; i++)
	{
		this->topTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			//Tile* tile = new Tile("images/tile_hidden.png");
			//tile->setPosition(i * 32, j * 32);
			this->topTiles[i].push_back(new Tile("images/tile_hidden.png", i*32, j*32));
		}
	}
	for (int i = 0; i < 25; i++) //Creates all the locations
	{
		this->bottomTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			//Tile* tile = new Tile("images/tile_revealed.png");
			//tile->setPosition(i * 32, j * 32);
			this->bottomTiles[i].push_back(new Tile("images/tile_revealed.png",i*32, j*32));
		}
	}
	flagTiles.resize(25);
	for (int i = 0; i < 25; i++)
	{
		this->flagTiles.push_back(vector<Tile*>());
		for (int j = 0; j < 16; j++)
		{
			this->flagTiles[i].push_back(new Tile("images/tile_revealed.png", i * 32, j * 32));
		}
	}
	string fileName = "boards/testboard" + to_string(testNumber) + ".brd";
	ifstream infile(fileName);
	for (int j = 0; j < 16; j++)
	{
		string value;
		getline(infile, value);
		for (int i = 0; i < 25; i++)
		{
			
			int numValue = int(value[i])-48;
			if (numValue == 1)
			{
				//Tile* bombTile = new Tile("images/mine.png");
				//bombTile->setPosition(i * 32, j * 32);
				this->bottomTiles[i][j] = new Tile("images/mine.png", i * 32, j * 32);
				tuple<int, int> location = make_tuple(i, j);
				this->bombTiles.push_back(location);
				
			}
			else
			{
				//Tile* blankTile = new Tile("images/tile_revealed.png");
				//blankTile->setPosition(i * 32, j * 32);
				this->bottomTiles[i][j] = new Tile("images/tile_revealed.png", i * 32, j * 32);
				
			}
		}
	}
	SetNumbers();
	this->nonMineTilesRemaining = 400 - this->bombTiles.size();
	for (int i = 0; i < GetBombTiles().size(); i++)
	{
		int j = get<0>(GetBombTiles()[i]);
		int k = get<1>(GetBombTiles()[i]);
		GetBackground()[j][k] = new Tile("images/tile_hidden.png", j * 32, k * 32);
	}
}