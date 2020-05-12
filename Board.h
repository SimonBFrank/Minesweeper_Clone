#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
using namespace std;

class Board
{
	vector<vector<Tile*>> topTiles;
	vector<vector<Tile*>> bottomTiles;
	vector<vector<Tile*>> background;
	vector<vector<Tile*>> flagTiles;
	
	vector<tuple<int, int>> bombTiles;
	vector<tuple<int, int>> flagLocations;
	vector<tuple<int, int>> revealedTiles;
	Tile* debugButton;
	Tile* Test1;
	Tile* Test2;
	Tile* Test3;
	Tile* SmileyFace;
	Tile* WinFace;
	Tile* LoseFace;
	int numberFlags;
	int nonMineTilesRemaining;
public:
	Board();
	void SetTile(int x, int y, Tile* tempTile);
	void AddFlag(tuple<int, int>&);
	void RemoveFlag(tuple<int, int>& location);
	void InitializeBoard();
	void CreateBackGround();
	void ResetBackground();

	void RandomizeBombs();
	bool checkRepeat(tuple<int, int>&, vector< tuple<int, int>>&);
	void RemoveTuple(tuple<int, int>&);
	void SetBombs();

	int NumberBombsAdjacent(tuple<int, int>& tempLocation);
	void SetNumbers();

	void RevealTiles(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesNorth(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesSouth(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesWest(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesEast(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesNorthWest(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesNorthEast(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesSouthEast(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealTilesSouthWest(tuple<int, int>&, vector<tuple<int, int>>&);
	void RevealAllMines();

	vector<Tile*> GetCounterTile(string);

	vector<vector<Tile*>>& GetBoardTop();
	vector<vector<Tile*>>& GetBoardBottom();
	vector< vector<Tile*>>& GetBackground();
	vector< vector<Tile*>>& GetFlags();
	vector<tuple<int, int>>& GetBombTiles();
	vector<tuple<int, int>>& GetFlagLocations();
	vector<tuple<int, int>>& GetRevealedTileLocations();
	int& GetNumberFlags();
	int& GetNumberNonMines();
	Tile* GetDebugButton();
	Tile* GetTest1Button();
	Tile* GetTest2Button();
	Tile* GetTest3Button();
	Tile* GetSmileyFace();
	Tile* GetWinFace();
	Tile* GetLoseFace();
	
	void LoadTest(int);
};


