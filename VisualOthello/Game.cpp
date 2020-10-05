#include "Game.h"

Game::Game(Player* player1, Player* player2)
{
	// �Ֆʂ̏�����
	this->board.resize(10);
	for (int y = 0; y < 10; y++)
	{
		this->board[y].resize(10);
		for (int x = 0; x < 10; x++)
		{
			if (x == 0 || x == 10 || y == 0 || y == 10)
			{
				this->board[y][x] = WALL;
			}
			else
			{
				this->board[y][x] = NONE;
			}
		}
	}

	// �����R�}�̔z�u
	this->board[4][4] = Player1;
	this->board[5][5] = Player1;
	this->board[4][5] = Player2;
	this->board[5][4] = Player2;

	// �v���C���[�̏�����
	this->players.resize(2);
	this->players[0] = player1;
	this->players[1] = player2;

	// �v���C���[���̏�����
	this->players[0]->set_player_num(Player1);
	this->players[1]->set_player_num(Player2);

	// first_player
	this->first_player = Player1;

	// player_str
	for (int i = 0; i < 8; i++)
	{
		this->player_str[0][i] = "Player1"[i];
		this->player_str[1][i] = "Player2"[i];
	}
}

void Game::start()
{
	Game::decide_first_player();

	std::cout << "First player is " << this->player_str[this->first_player] << std::endl;

	BoardStatus now_turn_player = this->first_player;

	while (!Game::is_finished())
	{
		Game::print_board(now_turn_player);

		// TODO: ���̃^�[����now_turn_player���u���邩�̔���
		// TODO: �p�X����Ƃ��̕\��
		Coordinate input = players[now_turn_player]->calc(board);

		if (Game::set_stone(input, now_turn_player))
		{
			std::cout << "�u���܂���" << std::endl;
		}
		else
		{
			std::cout << "�u���܂���ł���" << std::endl;
		}

		now_turn_player = Game::get_enemy(now_turn_player);
	}

	Game::game_over();
}

void Game::print_board(BoardStatus now_turn_player)
{
	std::cout << std::endl;
	std::cout << this->player_str[now_turn_player] << std::endl;
	std::cout << "  a b c d e f g h" << std::endl;
	for (int y = 1; y <= 8; y++)
	{
		std::cout << y << " ";
		for (int x = 1; x <= 8; x++)
		{
			switch (this->board[y][x])
			{
			case NONE:
				std::cout << " ";
				break;
			case Player1:
				std::cout << "O";
				break;
			case Player2:
				std::cout << "X";
				break;
			default:
				std::cout << "?";
				break;
			}

			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

bool Game::set_stone(Coordinate coordinate, BoardStatus player)
{
	if (Game::can_put(coordinate, player))
	{
		this->board[coordinate.y][coordinate.x] = player;
		// ���Ԃ�
		// �ォ�玞�v���
		const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
		const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
		const BoardStatus enemy = Game::get_enemy(player);

		// �f�o�b�O�p
		if (enemy == NONE)
		{
			std::cout << "NONE" << std::endl;
		}

		for (int i = 0; i < 8; i++)
		{
			bool line_flag = false;
			int delta = 1;

			while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
			{
				++delta;
			}

			if (delta >= 2 && this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == player)
			{
				line_flag = true;
			}

			// ���Ԃ�������Ȃ�
			if (line_flag)
			{
				delta = 1;
				// ���Ԃ�
				while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
				{
					this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] = player;
					++delta;
				}
			}
		}

		return true;
	}

	return false;
}

void Game::game_over()
{
	std::vector<int> point(2, 0);
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			++point[this->board[y][x]];
		}
	}

	std::cout << point[Player1] << " : " << point[Player2] << std::endl;

	if (point[Player1] > point[Player2])
	{
		std::cout << "Winner is O";
	}
	else if (point[Player2] < point[Player1])
	{
		std::cout << "Winner is X" << std::endl;
	}
	else
	{
		std::cout << "Draw" << std::endl;
	}
}

bool Game::can_put(Coordinate coordinate, BoardStatus player)
{
	// �Ֆʂ̓�����
	if (!is_inside(coordinate)) return false;

	// ���łɃR�}���u����Ă��邩
	if (this->board[coordinate.y][coordinate.x] != NONE) return false;

	// ���߂邩

	// �ォ�玞�v���
	const int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
	const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	const BoardStatus enemy = Game::get_enemy(player);

	// �f�o�b�O�p
	if (enemy == NONE)
	{
		std::cout << "NONE" << std::endl;
		return false;
	}

	for (int i = 0; i < 8; i++)
	{
		int delta = 1;
		while (this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == enemy)
		{
			++delta;
		}

		if (delta >= 2 && this->board[(long)coordinate.y + dy[i] * delta][(long)coordinate.x + dx[i] * delta] == player)
		{
			return true;
		}
	}

	return false;
}

bool Game::is_inside(Coordinate coordinate)
{
	if (coordinate.x < 1 || 8 < coordinate.x) return false;
	if (coordinate.y < 1 || 8 < coordinate.y) return false;

	return true;
}

bool Game::is_finished()
{
	for (int y = 1; y <= 8; y++)
	{
		for (int x = 1; x <= 8; x++)
		{
			if (Game::can_put(Coordinate{ x, y }, Player1) || Game::can_put(Coordinate{ x, y }, Player2)) return false;
		}
	}

	return true;
}

BoardStatus Game::get_enemy(BoardStatus player)
{
	if (player == Player1 || player == Player2)
	{
		if (player == Player1) return Player2;
		else return Player1;
	}

	return NONE;
}

BoardStatus Game::decide_first_player()
{
	srand((unsigned)time(NULL));
	this->first_player = (BoardStatus)(rand() % 2);

	return this->first_player;
}