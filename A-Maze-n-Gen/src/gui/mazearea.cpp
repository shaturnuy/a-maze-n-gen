#include "gui/mazearea.h"

MazeArea::MazeArea(QWidget *parent) noexcept
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
void MazeArea::drawMazeGrid(QVector<QVector<Cell>>& cellGrid)
{
    mazeScene_->clear();
    for (auto row = cellGrid.begin(); row != cellGrid.end(); row++)
    {
        for (auto col = row->begin(); col != row->end(); col++)
        {
            addCellOnScene(*col);
        }
    }

    emit fieldReadyToGenerate();
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::addCellOnScene(Cell& cell)
{
    mazeScene_->addItem(cell.getTopWall());
    mazeScene_->addItem(cell.getBotWall());
    mazeScene_->addItem(cell.getLeftWall());
    mazeScene_->addItem(cell.getRightWall());
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::setMazeSize(unsigned int mazeSize)
{
    mazeSize_ = mazeSize;

    emit requestToGenerateMazeGrid(mazeSize_);
}
