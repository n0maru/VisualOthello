#pragma once

enum BoardStatus
{
	Player1,
	Player2,
	NONE,
	WALL
};

enum GameStatus
{
	SET,
	CANNOT_SET,
	PASS
};

struct Coordinate
{
	int x;
	int y;
};