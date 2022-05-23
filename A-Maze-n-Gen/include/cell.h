#pragma once

#include <QLine>
#include <QPoint>
#include <QLine>
#include <QLineF>
#include <QGraphicsLineItem>

class Cell
{
private:
    unsigned int cellSize_ {};

    QPoint leftTopPoint_ {};
    QPoint rightTopPoint_ {};
    QPoint leftBotPoint_ {};
    QPoint rightBotPoint_ {};

//    QLineF topWall_ {};
//    QLineF botWall_ {};
//    QLineF leftWall_ {};
//    QLineF rightWall_ {};

public:
    Cell(unsigned int cellSize, unsigned int row, unsigned int col);

    QGraphicsLineItem *topWall_ {nullptr};
    QGraphicsLineItem *botWall_ {nullptr};
    QGraphicsLineItem *leftWall_ {nullptr};
    QGraphicsLineItem *rightWall_ {nullptr};
};
