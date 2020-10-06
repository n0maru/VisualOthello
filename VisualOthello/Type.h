#pragma once

enum BoardStatus
{
	Player1,
	Player2,
	NONE,
	WALL
};

struct Coordinate
{
	int x;
	int y;
};