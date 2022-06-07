#pragma once

#include "cell.h"
#include "gui/algorithmgeneratormenu.h"

#include <QVector>
#include <QStack>
#include <QRandomGenerator>
#include <QEventLoop>
#include <QTimer>
#include <QBitArray>

struct Coordinate;

class Maze : public QObject
{
    Q_OBJECT

private:
    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};

    QVector<QVector<Cell>> cellGrid_;
    bool interruptFlag_ {false};

    enum Direction {Forbidden = -1, Top, Right, Bot, Left, Count};
    const int DELAY_MS_IN_GENERATION_CYCLE {50};

public:
    explicit Maze(unsigned int mazeGridSizePx) noexcept;
    ~Maze() {};

    QVector<QVector<Cell>>& getCellGrid();

    void generateMazeGrid(unsigned int mazeSize);

    void generateMaze(int whichAlgorithmWasChosen);
    void generateAldousBroder(unsigned int &visitedCells, Coordinate &currentCoordinates);
    void generateRecursiveBacktracker(unsigned int &visitedCells, Coordinate &currentCoordinates);

    void interruptReceived();
    bool generationLoopExitCondition(unsigned int &visitedCells);

    int checkNeighborsAndDecideWhichWayToGo(Coordinate currentCoordinates);
    bool isLegitimateStep(Coordinate coordinate, int stepDirection);
    void makeStep(Coordinate &currentCoordinates, int stepDirection, unsigned int &visitedCellsCounter);
    void markCellAfterStep(Coordinate currentCoordinates, Coordinate newCoordinates);

    void goTop(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goRight(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goBot(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goLeft(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);

    // https://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt/43003223#43003223
    void delay(int millisecondsWait);
    void resetGrid();

signals:
    void requestToDrawMazeGrid(QVector<QVector<Cell>>& cellGrid);
    void mazeWasGenerated();
};


struct Coordinate
{
    int x;
    int y;
    Coordinate() : x(0), y(0) {};
    Coordinate(int x, int y) : x(x), y(y) {};
    inline bool operator==(const Coordinate &other) {return (x == other.x) && (y == other.y);};
};
