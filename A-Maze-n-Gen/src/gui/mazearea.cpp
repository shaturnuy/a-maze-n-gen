#include "gui/mazearea.h"

MazeArea::MazeArea(QWidget *parent) noexcept
    : QWidget(parent)
{
    initializeMenu();

    maze_ = new Maze(MAZE_AREA_SIZE);
    connect(maze_, &Maze::requestToDrawMazeGrid, this, &MazeArea::drawMazeGrid);
    connect(maze_, &Maze::requestToDrawCurrentCell, this, &MazeArea::drawCurrentCell);
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::initializeMenu()
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
void MazeArea::startGenerateMazeGrid(unsigned int mazeSize)
{
    maze_->generateMazeGrid(mazeSize);
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::startGenerationMaze(int whichAlgorithmWasChosen)
{
    if (whichAlgorithmWasChosen == AlgorithmGeneratorMenu::Algorithm::AldousBroder)
        maze_->generateAldousBroder();
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::drawCurrentCell(const Cell& cell)
{
    mazeScene_->addRect(QRectF(cell.getRectForShowCurrentCell()),
                        Qt::NoPen, QBrush(Qt::gray, Qt::SolidPattern));
}
