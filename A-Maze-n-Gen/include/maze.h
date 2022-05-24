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

    QVector<QVector<Cell>>& getCellGrid();

signals:
    void requestToDrawMazeGrid(QVector<QVector<Cell>>& cellGrid);

public slots:
    void generateMazeGrid(unsigned int mazeSize);
};
