#include "maze.h"

Maze::Maze(QGraphicsScene *scene)
{
    getCellGrid();

    for (int curRow {0}; curRow < rows; curRow++)
    {
        QVector<QLineF> curColLines {};
        for (int curCol {0}; curCol < columns; curCol++)
        {
            curColLines.push_back(QLineF(QLine(cellGrid[curRow][curCol], cellGrid[curRow][curCol + 1])));
            curColLines.push_back(QLineF(QLine(cellGrid[curRow][curCol], cellGrid[curRow + 1][curCol])));
            curColLines.push_back(QLineF(QLine(cellGrid[curRow + 1][curCol], cellGrid[curRow + 1][curCol + 1])));
            curColLines.push_back(QLineF(QLine(cellGrid[curRow][curCol + 1], cellGrid[curRow + 1][curCol + 1])));
        }
        cellWalls.push_back(curColLines);
    }

    for (auto i = 0; i < 5; i++)
    {
        for (auto j = 0; j < 20; j++)
        {
            scene->addItem(new QGraphicsLineItem(cellWalls[i][j]));
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::getCellGrid()
{
    for (int curRow {0}; curRow <= rows; curRow++)
    {
        QVector<QPoint> curColPoints {};
        for (int curCol {0}; curCol <= columns; curCol++)
        {
            curColPoints.push_back(QPoint(curCol * cellSize, curRow * cellSize));
        }
        cellGrid.push_back(curColPoints);
    }
}
