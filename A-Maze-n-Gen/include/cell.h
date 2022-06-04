#pragma once

#include <QPoint>
#include <QLineF>
#include <QGraphicsLineItem>
#include <QRect>

class Cell
{
private:
    unsigned int cellSize_ {};
    bool visited_ {false};

    QGraphicsLineItem *topWall_ {nullptr};
    QGraphicsLineItem *botWall_ {nullptr};
    QGraphicsLineItem *leftWall_ {nullptr};
    QGraphicsLineItem *rightWall_ {nullptr};

    QRect rectForShowCurrentCell_ {};

public:
    explicit Cell(unsigned int cellSize, unsigned int row, unsigned int col) noexcept;
    ~Cell() {};

    QGraphicsLineItem* getTopWall();
    QGraphicsLineItem* getBotWall();
    QGraphicsLineItem* getLeftWall();
    QGraphicsLineItem* getRightWall();

    void destroyTopWall();
    void destroyBotWall();
    void destroyLeftWall();
    void destroyRightWall();

    const QRect& getRectForShowCurrentCell() const;

    bool isVisited() const;
    void wasVisited();
};
