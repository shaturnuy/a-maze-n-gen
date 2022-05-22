#pragma once

#include "cell.h"

#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QLine>
#include <QPoint>

class Maze : public QObject
{
    Q_OBJECT

private:
    QVector<QVector<QPoint>> cellGrid;

    QVector<QVector<Cell>> cellGrid_;

    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};
    unsigned int cellSize_ {};

public:
    explicit Maze(unsigned int mazeGridSizePx);
    void initializePointsOfGrid();
    void initializeLinesOfGrid();

    QVector<QVector<QLineF>> cellWalls;

signals:
    void requestToDrawMazeGrid(Maze *maze);

public slots:
    void generateMazeGrid(unsigned int mazeSize);
};
