#include "gui/mazearea.h"

MazeArea::MazeArea(QWidget *parent)
    : QWidget(parent)
{
    mazeScene_ = new QGraphicsScene;
    mazeView_ = new QGraphicsView;
    mazeView_->setFixedSize(GRAPHIC_VIEW_SIZE, GRAPHIC_VIEW_SIZE);
    mazeView_->setScene(mazeScene_);

    Maze maze(mazeScene_, MAZE_AREA_SIZE);


    mazeAreaLayout_ = new QVBoxLayout(this);
    mazeAreaLayout_->setAlignment(Qt::AlignCenter);
    mazeAreaLayout_->addWidget(mazeView_);


    mazeAreaGroupBox_ = new QGroupBox(this);
    mazeAreaGroupBox_->setStyleSheet(MAZE_AREA_STYLE_SHEET);
    mazeAreaGroupBox_->setLayout(mazeAreaLayout_);

    setMinimumSize(mazeAreaGroupBox_->sizeHint());
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::setMazeSize(unsigned int mazeSize)
{
    mazeSize_ = mazeSize;
}
