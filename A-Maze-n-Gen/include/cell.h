#pragma once

#include <QLine>

class Cell
{
private:
    int cellSize {60};
    bool leftWall;
    bool rightWall;
    bool topWall;
    bool botWall;

public:
    Cell();
    bool visited();
};
