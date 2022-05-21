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

    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};
    unsigned int cellSize_ {};

public:
    explicit Maze(QGraphicsScene *scene, unsigned int mazeGridSizePx, unsigned int mazeSize = 5);
    void getPointsOfGrid();

public slots:
    void generateMazeGrid(unsigned int mazeSize);
};
