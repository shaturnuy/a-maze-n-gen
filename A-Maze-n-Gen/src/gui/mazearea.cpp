#include "gui/mazearea.h"

MazeArea::MazeArea(QWidget *parent)
    : QWidget(parent)
{
    mazeScene_ = new QGraphicsScene;
    mazeView_ = new QGraphicsView;
    mazeView_->setFixedSize(GRAPHIC_VIEW_SIZE, GRAPHIC_VIEW_SIZE);
    mazeView_->setScene(mazeScene_);


    mazeAreaLayout_ = new QVBoxLayout(this);
    mazeAreaLayout_->setAlignment(Qt::AlignCenter);
    mazeAreaLayout_->addWidget(mazeView_);


    mazeAreaGroupBox_ = new QGroupBox(this);
    mazeAreaGroupBox_->setStyleSheet(MAZE_AREA_STYLE_SHEET);
    mazeAreaGroupBox_->setLayout(mazeAreaLayout_);

    setMinimumSize(mazeAreaGroupBox_->sizeHint());

    maze_ = new Maze(MAZE_AREA_SIZE);
    connect(this, &MazeArea::requestToGenerateMazeGrid, maze_, &Maze::generateMazeGrid);

    connect(maze_, &Maze::requestToDrawMazeGrid, this, &MazeArea::drawMazeGrid);
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::drawMazeGrid(Maze *maze)
{
    for (unsigned i = 0; i < mazeSize_; i++)
    {
        for (unsigned j = 0; j < mazeSize_ * 4; j++)
        {
            mazeScene_->addItem(new QGraphicsLineItem(maze->cellWalls[i][j]));
        }
    }
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::setMazeSize(unsigned int mazeSize)
{
    mazeSize_ = mazeSize;
    emit requestToGenerateMazeGrid(mazeSize_);
}
