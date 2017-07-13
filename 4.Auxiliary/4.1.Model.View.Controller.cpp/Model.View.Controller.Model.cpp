#include <vector>
#include <memory>
#include <list>
#include <random>
#include <algorithm>

#include "Model.View.Controller.Model.h"
#pragma region --MinesweeperCell--
MinesweeperCell::MinesweeperCell(int _row, int _column)
	: row(_row)
	, column(_column)
{
}

void 
MinesweeperCell::nextMark(void)
{
	if (std::find(markSequence.begin(), markSequence.end(), state) != markSequence.end())
	{
		const State stateIndex = markSequence[state];
		state = markSequence[(stateIndex + 1) % markSequence.size()];
	}
}

void 
MinesweeperCell::open(void)
{
	if (state != flagged)
		state = opened;
}
#pragma endregion
#pragma region --MinesweeperModel--
MinesweeperModel::MinesweeperModel(void)
{
	startGame();
}

void 
MinesweeperModel::startGame(const int rowCount = 15, const int columnCount = 15, const int mineCount = 15)
{
	if (MIN_ROW_COUNT <= rowCount && rowCount <= MAX_ROW_COUNT)
		_rowCount = rowCount;

	if (MIN_COLUMN_COUNT <= columnCount && columnCount <= MAX_COLUMN_COUNT)
		_columnCount = columnCount;

	if (mineCount < _rowCount * _columnCount)
	{
		if (MIN_MINE_COUNT <= mineCount && mineCount <= MAX_MINE_COUNT)
			_mineCount = mineCount;
	}
	else
		_mineCount = _rowCount * _columnCount - 1; // Зверство !!!

	_firstStep = true;
	_gameOver = false;

	_cellsTable.reserve(_rowCount);
	for (std::vector<MinesweeperCell::ptr>& r : _cellsTable)
		r.reserve(columnCount);

	for (int row = 0; row < _rowCount; ++row)
		for (int col = 0; col < _columnCount; ++col)
			_cellsTable[row][col].reset(new MinesweeperCell(row, col));
}

MinesweeperCell::ptr 
MinesweeperModel::getCell(int row, int column)
{
	if (row < 0 || column < 0 || _rowCount <= row || _columnCount <= column)
		return MinesweeperCell::ptr();

	return _cellsTable[row][column];
}

bool MinesweeperModel::isWin(void)
{
	for (int row = 0; row < _rowCount; ++row)
		for (int column = 0; column < _columnCount; ++column)
		{
			auto cell = getCell(row, column);
			if (!cell->mined && (cell->state != MinesweeperCell::opened && cell->state != MinesweeperCell::flagged))
				return false;
		}
	return true;
}

bool 
MinesweeperModel::isGameOver(void)
{
	return _gameOver;
}

void MinesweeperModel::openCell(const int row, const int column)
{
	auto cell = getCell(row, column);
	if (!cell)
		return;

	cell->open();

	if (cell->mined)
	{
		_gameOver = true;
		return;
	}

	if (_firstStep)
	{
		_firstStep = false;
		generateMines();
	}

	cell->counter = countMinesAroundCell(row, column);
	if (cell->counter == 0)
	{
		auto neighbours = getCellNeighbours(row, column);
		for (auto n : neighbours)
			if (n->state == MinesweeperCell::closed)
				openCell(n->row, n->column);
	}
}

void MinesweeperModel::nextCellMark(const int row, const int column)
{
	auto cell = getCell(row, column);
	if (cell)
		cell->nextMark();
}

void MinesweeperModel::generateMines(void)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> cols_dis(0, _columnCount - 1);
	std::uniform_int_distribution<> rows_dis(0, _rowCount - 1);

	for (int i = 0; i < _mineCount; ++i)
	{
		while (true)
		{
			const int row = rows_dis(gen);
			const int col = cols_dis(gen);

			auto cell = getCell(row, col);
			if (cell->state != MinesweeperCell::opened && !cell->mined)
			{
				cell->mined = true;
				break;
			}
		}
	}
}

int MinesweeperModel::countMinesAroundCell(const int row, const int column)
{
	std::list<MinesweeperCell::ptr> neighbours = getCellNeighbours(row, column);
	int sum = 0;
	for (MinesweeperCell::ptr& n : neighbours)
		sum += n->mined;
	return sum;
}

std::list<MinesweeperCell::ptr> 
MinesweeperModel::getCellNeighbours(const int row, const int column)
{
	std::list<MinesweeperCell::ptr> neighbours;

	for (int r = row - 1; r < row + 2; ++r)
	{
		neighbours.push_back(getCell(r, column - 1));
		if (r != row)
			neighbours.push_back(getCell(r, column));
		neighbours.push_back(getCell(r, column + 1));
	}

	// Выкидываем нулевые указатели
	std::remove_if(neighbours.begin(), neighbours.end(), [](MinesweeperCell::ptr& p)->bool { return p == nullptr;  });

	return neighbours;
}
#pragma endregion
