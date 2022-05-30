#pragma once

#include "cell.h"

#include <QVector>

class Maze : public QObject
{
    Q_OBJECT

private:
    unsigned int mazeGridSizePx_ {};
    unsigned int mazeSize_ {};

    QVector<QVector<Cell>> cellGrid_;

public:
    explicit Maze(unsigned int mazeGridSizePx) noexcept;
    ~Maze() {};

    void generateMazeGrid(unsigned int mazeSize);
    QVector<QVector<Cell>>& getCellGrid();

    void generateAldousBroder();

signals:
    void requestToDrawMazeGrid(QVector<QVector<Cell>>& cellGrid);
};
