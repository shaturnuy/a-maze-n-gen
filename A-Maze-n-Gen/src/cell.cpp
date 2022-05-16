#include "cell.h"

Cell::Cell() :
    leftWall {true}, rightWall {true}, topWall {true}, botWall {true}
{
}

bool Cell::visited()
{
    if (leftWall && rightWall && topWall && botWall)
        return true;
    else
        return false;
}
