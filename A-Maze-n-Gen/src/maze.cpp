#include "maze.h"

Maze::Maze(unsigned int mazeGridSizePx) noexcept
    : mazeGridSizePx_(mazeGridSizePx)
{
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateMazeGrid(unsigned int mazeSize)
{
    // Перед генерацией поля очищаем его от старых значений
    cellGrid_.clear();

    mazeSize_ = mazeSize;
    unsigned int cellSize = mazeGridSizePx_ / mazeSize_;

    for (unsigned int row {0}; row < mazeSize_; row++)
    {
        QVector<Cell> curRowCells {};
        for (unsigned int col {0}; col < mazeSize_; col++)
        {
            curRowCells.push_back(Cell(cellSize, row, col));
        }
        cellGrid_.push_back(curRowCells);
    }

    // После завершения генерации поля отправляем его на отрисовку
    emit requestToDrawMazeGrid(getCellGrid());
}

/*------------------------------------------------------------------------------------------------*/
QVector<QVector<Cell>>& Maze::getCellGrid()
{
    return cellGrid_;
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateAldousBroder()
{
    QVector<Cell> visitedCells {};
    visitedCells.push_back(cellGrid_[0][0]);


    while (visitedCells.size() < mazeSize_)
    {

    }
}
