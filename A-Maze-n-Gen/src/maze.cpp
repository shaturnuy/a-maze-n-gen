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
    cellGrid_[0][0].wasVisited();
    cellGrid_[0][0].getRectForShowCurrentCell()->setVisible(true);
    delay(DELAY_MS_IN_GENERATION_CYCLE);

    switch (whichAlgorithmWasChosen)
    {
    case AlgorithmGeneratorMenu::Algorithm::AldousBroder :
        generateAldousBroder(visitedCells, currentCoordinates);
        break;
    case AlgorithmGeneratorMenu::Algorithm::RecursiveBacktracker :
        generateRecursiveBacktracker(visitedCells, currentCoordinates);
        break;
    case AlgorithmGeneratorMenu::Algorithm::Wilson :
        generateWilson(visitedCells, currentCoordinates);
        break;
    }

    cellGrid_[currentCoordinates.x][currentCoordinates.y].getRectForShowCurrentCell()->setVisible(false);
    interruptFlag_ = false;
    emit mazeWasGenerated();
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateAldousBroder(unsigned int &visitedCells, Coordinate &currentCoordinates)
{
    while (generationLoopExitCondition(visitedCells))
    {
        int whichWayToGo = QRandomGenerator::global()->generate() % Direction::Count;
        if (isLegitimateStep(currentCoordinates, whichWayToGo))
            makeStep(currentCoordinates, whichWayToGo, visitedCells);
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateRecursiveBacktracker(unsigned int &visitedCells, Coordinate &currentCoordinates)
{
    QStack<Coordinate> backtrackingStack {};
    backtrackingStack.push(currentCoordinates);

    while (generationLoopExitCondition(visitedCells))
    {
        int whichWayToGo = checkNeighborsAndDecideWhichWayToGo(backtrackingStack.top());
        if (whichWayToGo != Direction::Forbidden)
        {
            makeStep(backtrackingStack.top(), whichWayToGo, visitedCells);
            backtrackingStack.push(backtrackingStack.top());
        }
        else
        {
            cellGrid_[backtrackingStack.top().x][backtrackingStack.top().y].
                    getRectForShowCurrentCell()->setVisible(false);
            backtrackingStack.pop();
        }
    }
    currentCoordinates = backtrackingStack.top();
}

/*------------------------------------------------------------------------------------------------*/
void Maze::generateWilson(unsigned int &visitedCells, Coordinate &currentCoordinates)
{
    QStack<Coordinate> currentPathStack {};
    QVector<Coordinate> cellsAlreadyInMaze {};
    cellsAlreadyInMaze.push_back(currentCoordinates);
    cellGrid_[0][0].getRectForShowCurrentCell()->setVisible(false);

    while (generationLoopExitCondition(visitedCells))
    {
        while (cellsAlreadyInMaze.contains(currentCoordinates))
        {
            currentCoordinates = Coordinate(QRandomGenerator::global()->generate() % mazeSize_,
                                            QRandomGenerator::global()->generate() % mazeSize_);
        }
        cellGrid_[currentCoordinates.x][currentCoordinates.y].
                getRectForShowCurrentCell()->setVisible(true);
        cellGrid_[currentCoordinates.x][currentCoordinates.y].wasVisited();
        currentPathStack.push(currentCoordinates);

        while (!cellsAlreadyInMaze.contains(currentCoordinates))
        {
            int whichWayToGo = QRandomGenerator::global()->generate() % Direction::Count;
            if (isLegitimateStep(currentCoordinates, whichWayToGo))
            {
                makeStep(currentCoordinates, whichWayToGo, visitedCells);
                if (!currentPathStack.contains(currentCoordinates))
                {
                    currentPathStack.push(currentCoordinates);
                }
                else
                {
                    while (currentCoordinates != currentPathStack.top())
                    {
                        Coordinate savedCord = currentPathStack.top();
                        currentPathStack.pop();
                        Coordinate tempCord = Coordinate(savedCord.x - currentPathStack.top().x, savedCord.y - currentPathStack.top().y);
//                        cellGrid_[currentPathStack.top().x][currentPathStack.top().y].visited_ = false;

                        if (tempCord.x == 1)
                        {
                            cellGrid_[savedCord.x][savedCord.y].getLeftWall()->setVisible(true);
                            cellGrid_[currentPathStack.top().x][currentPathStack.top().y].getRightWall()->setVisible(true);
                        }
                        if (tempCord.x == -1)
                        {
                            cellGrid_[savedCord.x][savedCord.y].getRightWall()->setVisible(true);
                            cellGrid_[currentPathStack.top().x][currentPathStack.top().y].getLeftWall()->setVisible(true);
                        }
                        if (tempCord.y == 1)
                        {
                            cellGrid_[savedCord.x][savedCord.y].getTopWall()->setVisible(true);
                            cellGrid_[currentPathStack.top().x][currentPathStack.top().y].getBotWall()->setVisible(true);
                        }
                        if (tempCord.y == -1)
                        {
                            cellGrid_[savedCord.x][savedCord.y].getBotWall()->setVisible(true);
                            cellGrid_[currentPathStack.top().x][currentPathStack.top().y].getTopWall()->setVisible(true);
                        }
                        visitedCells--;
                    }
                    cellGrid_[currentCoordinates.x][currentCoordinates.y].wasVisited();
                }
            }
        }
        cellGrid_[currentCoordinates.x][currentCoordinates.y].getRectForShowCurrentCell()->setVisible(false);
        while (currentPathStack.size() != 0)
        {
            cellsAlreadyInMaze.push_back(currentPathStack.top());
            currentPathStack.pop();
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
int Maze::checkNeighborsAndDecideWhichWayToGo(Coordinate currentCoordinates)
{
    QBitArray cellNeighborsState(Direction::Count);

    if (isLegitimateStep(currentCoordinates, Direction::Top) &&
            !cellGrid_[currentCoordinates.x][currentCoordinates.y - 1].isVisited())
        cellNeighborsState.setBit(Direction::Top, true);

    if (isLegitimateStep(currentCoordinates, Direction::Right) &&
            !cellGrid_[currentCoordinates.x + 1][currentCoordinates.y].isVisited())
        cellNeighborsState.setBit(Direction::Right, true);

    if (isLegitimateStep(currentCoordinates, Direction::Bot) &&
            !cellGrid_[currentCoordinates.x][currentCoordinates.y + 1].isVisited())
        cellNeighborsState.setBit(Direction::Bot, true);

    if (isLegitimateStep(currentCoordinates, Direction::Left) &&
            !cellGrid_[currentCoordinates.x - 1][currentCoordinates.y].isVisited())
        cellNeighborsState.setBit(Direction::Left, true);


    if (cellNeighborsState == QBitArray(Direction::Count, false))
        return Direction::Forbidden;
    else
    {
        int whichWayToGo = QRandomGenerator::global()->generate() % Direction::Count;
        while (cellNeighborsState[whichWayToGo] != true)
            whichWayToGo = QRandomGenerator::global()->generate() % Direction::Count;
        return whichWayToGo;
    }
}

/*------------------------------------------------------------------------------------------------*/
void Maze::interruptReceived()
{
    interruptFlag_ = true;
}

/*------------------------------------------------------------------------------------------------*/
bool Maze::generationLoopExitCondition(unsigned int &visitedCells)
{
    return (!interruptFlag_ && visitedCells < mazeSize_ * mazeSize_);
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

/*------------------------------------------------------------------------------------------------*/
void Maze::resetGrid()
{
    for (auto row = cellGrid_.begin(); row != cellGrid_.end(); row++)
    {
        for (auto col = row->begin(); col != row->end(); col++)
        {
            col->resetCell();
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
bool Coordinate::operator==(const Coordinate &other) const
{
    return (x == other.x) && (y == other.y);
}

/*------------------------------------------------------------------------------------------------*/
bool Coordinate::operator!=(const Coordinate &other) const
{
    return (x != other.x) || (y != other.y);
}
