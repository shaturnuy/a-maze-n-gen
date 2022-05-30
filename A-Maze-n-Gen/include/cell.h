#pragma once

#include <QPoint>
#include <QLineF>
#include <QGraphicsLineItem>
#include <QRect>

class Cell
{
private:
    unsigned int cellSize_ {};

    QGraphicsLineItem *topWall_ {nullptr};
    QGraphicsLineItem *botWall_ {nullptr};
    QGraphicsLineItem *leftWall_ {nullptr};
    QGraphicsLineItem *rightWall_ {nullptr};

public:
    explicit Cell(unsigned int cellSize, unsigned int row, unsigned int col) noexcept;
    ~Cell() {};

    QGraphicsLineItem* getTopWall();
    QGraphicsLineItem* getBotWall();
    QGraphicsLineItem* getLeftWall();
    QGraphicsLineItem* getRightWall();

    QRect testRect {};
};
