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
    QVector<QVector<Cell>> cellGrid_;

    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};

public:
    explicit Maze(unsigned int mazeGridSizePx);
    const QVector<QVector<Cell>>& getCellGrid();
//    void initializePointsOfGrid();
//    void initializeLinesOfGrid();

//    QVector<QVector<QLineF>> cellWalls;

signals:
    void requestToDrawMazeGrid(const QVector<QVector<Cell>>& cellGrid);

public slots:
    void generateMazeGrid(unsigned int mazeSize);
};
