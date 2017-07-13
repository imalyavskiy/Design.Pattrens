#pragma once

#define MIN_ROW_COUNT		5
#define MAX_ROW_COUNT		30
#define MIN_COLUMN_COUNT	5
#define MAX_COLUMN_COUNT	30
#define MIN_MINE_COUNT		1
#define MAX_MINE_COUNT		800

class MinesweeperCell
{
	// ¬озможные состо€ни€ игровой клетки:
	//   closed - закрыта
	//   opened - открыта
	//   flagged - помечена флажком
	//   questioned - помечена вопросительным знаком
public:
	typedef std::shared_ptr<MinesweeperCell> ptr;

	enum State
	{
		closed,
		flagged,
		questioned,
		opened
	};

	MinesweeperCell(int _row, int _column);

	void nextMark(void);

	void open(void);

	const std::vector<State> markSequence = { closed, flagged, questioned };

	const int	row;
	const int	column;
	State		state = closed;
	bool		mined = false;
	int			counter = 0;
};

class MinesweeperModel
{
public:
	int		_rowCount;
	int		_columnCount;
	int		_mineCount;
	bool	_firstStep;
	bool	_gameOver;

	std::vector<std::vector<MinesweeperCell::ptr>> _cellsTable;

public:
	MinesweeperModel(void);

	void startGame(const int rowCount = 15, const int columnCount = 15, const int mineCount = 15);

	MinesweeperCell::ptr getCell(int row, int column);

	bool isWin(void);

	bool isGameOver(void);

	void openCell(const int row, const int column);

	void nextCellMark(const int row, const int column);

	void generateMines(void);

	int countMinesAroundCell(const int row, const int column);

	std::list<MinesweeperCell::ptr> getCellNeighbours(const int row, const int column);
};