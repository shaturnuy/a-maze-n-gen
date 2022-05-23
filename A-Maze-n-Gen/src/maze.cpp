#include "maze.h"

Maze::Maze(unsigned int mazeGridSizePx)
    : mazeGridSizePx_(mazeGridSizePx)
{
}

/*------------------------------------------------------------------------------------------------*/
//void Maze::initializePointsOfGrid()
//{
////    for (unsigned row {0}; row <= mazeSize_; row++)
////    {
////        QVector<QPoint> curColPoints {};
////        for (unsigned col {0}; col <= mazeSize_; col++)
////        {
////            curColPoints.push_back(QPoint(col * cellSize_, row * cellSize_));
////        }
////        cellGrid.push_back(curColPoints);
////    }
//}

/*------------------------------------------------------------------------------------------------*/
//void Maze::initializeLinesOfGrid()
//{
////    for (unsigned row {0}; row < mazeSize_; row++)
////    {
////        QVector<QLineF> curColLines {};
////        for (unsigned col {0}; col < mazeSize_; col++)
////        {
////            curColLines.push_back(QLineF(QLine(cellGrid[row][col], cellGrid[row][col + 1])));
////            curColLines.push_back(QLineF(QLine(cellGrid[row][col], cellGrid[row + 1][col])));
////            curColLines.push_back(QLineF(QLine(cellGrid[row + 1][col], cellGrid[row + 1][col + 1])));
////            curColLines.push_back(QLineF(QLine(cellGrid[row][col + 1], cellGrid[row + 1][col + 1])));
////        }
////        cellWalls.push_back(curColLines);
////    }

//    emit requestToDrawMazeGrid(this);
//}

/*------------------------------------------------------------------------------------------------*/
const QVector<QVector<Cell>>& Maze::getCellGrid()
{
    return cellGrid_;
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateMazeGrid(unsigned int mazeSize)
{
    cellGrid_.clear();

    mazeSize_ = mazeSize;
    unsigned int cellSize = mazeGridSizePx_ / mazeSize_;

    for (unsigned int row {0}; row < mazeSize_; row++)
    {
        QVector<Cell> curRowCells {};
        for (unsigned int col {0}; col < mazeSize_; col++)
            curRowCells.push_back(Cell(cellSize, row, col));
        cellGrid_.push_back(curRowCells);
    }

    emit requestToDrawMazeGrid(getCellGrid());
//    initializePointsOfGrid();
//    initializeLinesOfGrid();
}
