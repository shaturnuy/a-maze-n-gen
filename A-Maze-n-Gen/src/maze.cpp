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

    for (unsigned int col {0}; col < mazeSize_; col++)
    {
        QVector<Cell> curColCells {};
        for (unsigned int row {0}; row < mazeSize_; row++)
        {
            curColCells.push_back(Cell(cellSize, row, col));
        }
        cellGrid_.push_back(curColCells);
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
void Maze::generateMaze(int whichAlgorithmWasChosen)
{
    Coordinate currentCoordinates {0, 0};
    unsigned int visitedCells {1};
    cellGrid_[0][0].getRectForShowCurrentCell()->setVisible(true);
    delay(DELAY_MS_IN_GENERATION_CYCLE);

    switch (whichAlgorithmWasChosen)
    {
    case AlgorithmGeneratorMenu::AldousBroder :
        generateAldousBroder(visitedCells, currentCoordinates);
        break;
    }

    cellGrid_[currentCoordinates.x][currentCoordinates.y].getRectForShowCurrentCell()->setVisible(false);
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateAldousBroder(unsigned int &visitedCells, Coordinate &currentCoordinates)
{
    while (visitedCells <= mazeSize_ * mazeSize_)
    {
        int whichWayToGo = QRandomGenerator::global()->generate() % 4;
        if (isLegitimateStep(currentCoordinates, whichWayToGo))
        {
            makeStep(currentCoordinates, whichWayToGo, visitedCells);
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
bool Maze::isLegitimateStep(Coordinate coordinate, int stepDirection)
{
    bool isLegitimateStep {false};
    switch (stepDirection)
    {
    case Direction::Top :
        coordinate.y <= 0 ? isLegitimateStep = false : isLegitimateStep = true;
        break;
    case Direction::Right :
        coordinate.x >= static_cast<int> (mazeSize_ - 1) ? isLegitimateStep = false : isLegitimateStep = true;
        break;
    case Direction::Bot :
        coordinate.y >= static_cast<int> (mazeSize_ - 1) ? isLegitimateStep = false : isLegitimateStep = true;
        break;
    case Direction::Left :
        coordinate.x <= 0 ? isLegitimateStep = false : isLegitimateStep = true;
        break;
    }
    return isLegitimateStep;
}

/*------------------------------------------------------------------------------------------------*/
void Maze::makeStep(Coordinate &currentCoordinates, int stepDirection, unsigned int &visitedCellsCounter)
{
    bool cellWasVisitedOnThisStep {false};
    Coordinate newCoordinates = currentCoordinates;

    switch (stepDirection)
    {
    case Direction::Top :
        goTop(currentCoordinates, newCoordinates, cellWasVisitedOnThisStep);
        break;
    case Direction::Right :
        goRight(currentCoordinates, newCoordinates, cellWasVisitedOnThisStep);
        break;
    case Direction::Bot :
        goBot(currentCoordinates, newCoordinates, cellWasVisitedOnThisStep);
        break;
    case Direction::Left :
        goLeft(currentCoordinates, newCoordinates, cellWasVisitedOnThisStep);
        break;
    }

    markCellAfterStep(currentCoordinates, newCoordinates);
    delay(DELAY_MS_IN_GENERATION_CYCLE);

    currentCoordinates = newCoordinates;
    if (cellWasVisitedOnThisStep)
        visitedCellsCounter++;
}

/*------------------------------------------------------------------------------------------------*/
void Maze::markCellAfterStep(Coordinate currentCoordinates, Coordinate newCoordinates)
{
    cellGrid_[currentCoordinates.x][currentCoordinates.y].getRectForShowCurrentCell()->setVisible(false);
    cellGrid_[newCoordinates.x][newCoordinates.y].getRectForShowCurrentCell()->setVisible(true);
}

/*------------------------------------------------------------------------------------------------*/
void Maze::goTop(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep)
{
    newCoordinates.y = newCoordinates.y - 1;
    if (cellGrid_[newCoordinates.x][newCoordinates.y].isVisited() == false)
    {
        cellGrid_[currentCoordinates.x][currentCoordinates.y].destroyTopWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].destroyBotWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].wasVisited();
        cellWasVisitedOnThisStep = true;
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::goRight(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep)
{
    newCoordinates.x = newCoordinates.x + 1;
    if (cellGrid_[newCoordinates.x][newCoordinates.y].isVisited() == false)
    {
        cellGrid_[currentCoordinates.x][currentCoordinates.y].destroyRightWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].destroyLeftWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].wasVisited();
        cellWasVisitedOnThisStep = true;
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::goBot(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep)
{
    newCoordinates.y = newCoordinates.y + 1;
    if (cellGrid_[newCoordinates.x][newCoordinates.y].isVisited() == false)
    {
        cellGrid_[currentCoordinates.x][currentCoordinates.y].destroyBotWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].destroyTopWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].wasVisited();
        cellWasVisitedOnThisStep = true;
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::goLeft(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep)
{
    newCoordinates.x = newCoordinates.x - 1;
    if (cellGrid_[newCoordinates.x][newCoordinates.y].isVisited() == false)
    {
        cellGrid_[currentCoordinates.x][currentCoordinates.y].destroyLeftWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].destroyRightWall();
        cellGrid_[newCoordinates.x][newCoordinates.y].wasVisited();
        cellWasVisitedOnThisStep = true;
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}
