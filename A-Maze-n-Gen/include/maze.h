#pragma once

#include "cell.h"

#include <QVector>
#include <QRandomGenerator>
#include <QEventLoop>
#include <QTimer>

struct Coordinate;

class Maze : public QObject
{
    Q_OBJECT

private:
    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};

    QVector<QVector<Cell>> cellGrid_;

    enum Direction {Top, Right, Bot, Left};
    const int DELAY_MS_IN_GENERATION_CYCLE {0};

public:
    explicit Maze(unsigned int mazeGridSizePx) noexcept;
    ~Maze() {};

    void generateMazeGrid(unsigned int mazeSize);
    QVector<QVector<Cell>>& getCellGrid();

    void generateAldousBroder();

    bool isLegitimateStep(Coordinate coordinate, int stepDirection);
    void makeStep(Coordinate &currentCoordinates, int stepDirection, unsigned int &visitedCellsCounter);

    void goTop(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goRight(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goBot(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);
    void goLeft(Coordinate &currentCoordinates, Coordinate &newCoordinates, bool &cellWasVisitedOnThisStep);

    // https://stackoverflow.com/questions/3752742/how-do-i-create-a-pause-wait-function-using-qt/43003223#43003223
    void delay(int millisecondsWait);

signals:
    void requestToDrawMazeGrid(QVector<QVector<Cell>>& cellGrid);
    void requestToDrawCurrentCell(const Cell& cell);
};


struct Coordinate
{
    int x;
    int y;
    Coordinate() : x(0), y(0) {};
    Coordinate(int x, int y) : x(x), y(y) {};
};
