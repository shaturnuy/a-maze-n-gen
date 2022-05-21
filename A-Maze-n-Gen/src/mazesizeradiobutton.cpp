#include "mazesizeradiobutton.h"

MazeSizeRadioButton::MazeSizeRadioButton(unsigned int mazeSize)
    : QRadioButton(QString::number(mazeSize) + "x" + QString::number(mazeSize)),
      mazeSize_(mazeSize)
{
}

/*------------------------------------------------------------------------------------------------*/
unsigned int MazeSizeRadioButton::getMazeSize() const
{
    return mazeSize_;
}
