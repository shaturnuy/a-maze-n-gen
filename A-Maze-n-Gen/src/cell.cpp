#include "cell.h"

Cell::Cell(unsigned int cellSize, unsigned int row, unsigned int col)
    : cellSize_(cellSize)
{
    leftTopPoint_.setX((col + 0) * cellSize_);
    leftTopPoint_.setY((row + 0) * cellSize_);

    rightTopPoint_.setX((col + 1) * cellSize_);
    rightTopPoint_.setY((row + 0) * cellSize_);

    leftBotPoint_.setX((col + 0) * cellSize_);
    leftBotPoint_.setY((row + 1) * cellSize_);

    rightBotPoint_.setX((col + 1) * cellSize_);
    rightBotPoint_.setY((row + 1) * cellSize_);

    topWall_ = new QGraphicsLineItem;
    botWall_ = new QGraphicsLineItem;
    leftWall_ = new QGraphicsLineItem;
    rightWall_ = new QGraphicsLineItem;

//    topWall_.setPoints(leftTopPoint_, rightTopPoint_);
//    botWall_.setPoints(leftBotPoint_, rightBotPoint_);
//    leftWall_.setPoints(leftTopPoint_, leftBotPoint_);
//    rightWall_.setPoints(rightTopPoint_, rightBotPoint_);

    topWall_->setLine(QLineF(leftTopPoint_, rightTopPoint_));
    botWall_->setLine(QLineF(leftBotPoint_, rightBotPoint_));
    leftWall_->setLine(QLineF(leftTopPoint_, leftBotPoint_));
    rightWall_->setLine(QLineF(rightTopPoint_, rightBotPoint_));
}
