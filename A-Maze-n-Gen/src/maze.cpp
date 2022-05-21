#include "maze.h"

Maze::Maze(QGraphicsScene *scene, unsigned int mazeGridSizePx, unsigned int mazeSize)
    : mazeGridSizePx_(mazeGridSizePx),
      mazeSize_(mazeSize),
      cellSize_(mazeGridSizePx / mazeSize)
{
    getPointsOfGrid();

    for (unsigned row {0}; row < mazeSize_; row++)
    {
        QVector<QLineF> curColLines {};
        for (unsigned col {0}; col < mazeSize_; col++)
        {
            curColLines.push_back(QLineF(QLine(cellGrid[row][col], cellGrid[row][col + 1])));
            curColLines.push_back(QLineF(QLine(cellGrid[row][col], cellGrid[row + 1][col])));
            curColLines.push_back(QLineF(QLine(cellGrid[row + 1][col], cellGrid[row + 1][col + 1])));
            curColLines.push_back(QLineF(QLine(cellGrid[row][col + 1], cellGrid[row + 1][col + 1])));
        }
        cellWalls.push_back(curColLines);
    }

    for (unsigned i = 0; i < mazeSize_; i++)
    {
        for (unsigned j = 0; j < mazeSize_ * 4; j++)
        {
            scene->addItem(new QGraphicsLineItem(cellWalls[i][j]));
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::getPointsOfGrid()
{
    for (unsigned row {0}; row <= mazeSize_; row++)
    {
        QVector<QPoint> curColPoints {};
        for (unsigned col {0}; col <= mazeSize_; col++)
        {
            curColPoints.push_back(QPoint(col * cellSize_, row * cellSize_));
        }
        cellGrid.push_back(curColPoints);
    }
}

void Maze::generateMazeGrid(unsigned int mazeSize)
{

}
