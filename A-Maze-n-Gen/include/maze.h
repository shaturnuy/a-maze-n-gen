#pragma once

#include "cell.h"

#include <QVector>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QLineF>
#include <QLine>
#include <QPoint>

class Maze
{
private:

    QVector<QVector<QPoint>> cellGrid;
    QVector<QVector<QLineF>> cellWalls;
    int cellSize {60};
    int columns {5};
    int rows {5};

public:

    Maze(QGraphicsScene *scene);
    void getCellGrid();
};
