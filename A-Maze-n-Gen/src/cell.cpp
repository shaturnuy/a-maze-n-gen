#include "cell.h"

Cell::Cell(unsigned int cellSize, unsigned int row, unsigned int col) noexcept
    : cellSize_(cellSize)
{
    QPoint leftTopPoint {};
    QPoint rightTopPoint {};
    QPoint leftBotPoint {};
    QPoint rightBotPoint {};

    leftTopPoint.setX((col + 0) * cellSize_);
    leftTopPoint.setY((row + 0) * cellSize_);

    rightTopPoint.setX((col + 1) * cellSize_);
    rightTopPoint.setY((row + 0) * cellSize_);

    leftBotPoint.setX((col + 0) * cellSize_);
    leftBotPoint.setY((row + 1) * cellSize_);

    rightBotPoint.setX((col + 1) * cellSize_);
    rightBotPoint.setY((row + 1) * cellSize_);


    topWall_ = new QGraphicsLineItem;
    botWall_ = new QGraphicsLineItem;
    leftWall_ = new QGraphicsLineItem;
    rightWall_ = new QGraphicsLineItem;

    topWall_->setLine(QLineF(leftTopPoint, rightTopPoint));
    botWall_->setLine(QLineF(leftBotPoint, rightBotPoint));
    leftWall_->setLine(QLineF(leftTopPoint, leftBotPoint));
    rightWall_->setLine(QLineF(rightTopPoint, rightBotPoint));

    /* Координаты второй точки необходимо уменьшить на 1, т.к. квадрат отображается на 1 пиксель
    больше, чем узлы сетки, построенной на линиях */
    rightBotPoint.setX(rightBotPoint.x() - 1);
    rightBotPoint.setY(rightBotPoint.y() - 1);
    rectForShowCurrentCell_ = QRect(leftTopPoint, rightBotPoint);
}

/*------------------------------------------------------------------------------------------------*/
QGraphicsLineItem* Cell::getTopWall()
{
    return topWall_;
}

/*------------------------------------------------------------------------------------------------*/
QGraphicsLineItem* Cell::getBotWall()
{
    return botWall_;
}

/*------------------------------------------------------------------------------------------------*/
QGraphicsLineItem* Cell::getLeftWall()
{
    return leftWall_;
}

/*------------------------------------------------------------------------------------------------*/
QGraphicsLineItem* Cell::getRightWall()
{
    return rightWall_;
}

/*------------------------------------------------------------------------------------------------*/
void Cell::destroyTopWall()
{
    topWall_->setVisible(false);
}

/*------------------------------------------------------------------------------------------------*/
void Cell::destroyBotWall()
{
    botWall_->setVisible(false);
}

/*------------------------------------------------------------------------------------------------*/
void Cell::destroyLeftWall()
{
    leftWall_->setVisible(false);
}

/*------------------------------------------------------------------------------------------------*/
void Cell::destroyRightWall()
{
    rightWall_->setVisible(false);
}

/*------------------------------------------------------------------------------------------------*/
const QRect& Cell::getRectForShowCurrentCell() const
{
    return rectForShowCurrentCell_;
}

/*------------------------------------------------------------------------------------------------*/
bool Cell::isVisited() const
{
    return visited_;
}

/*------------------------------------------------------------------------------------------------*/
void Cell::wasVisited()
{
    visited_ = true;
}
