#include "gui/mazearea.h"

MazeArea::MazeArea(QWidget *parent) noexcept
    : QWidget(parent)
{
    initializeMenu();

    maze_ = new Maze(MAZE_AREA_SIZE);
    connect(maze_, &Maze::requestToDrawMazeGrid, this, &MazeArea::drawMazeGrid);
    connect(maze_, &Maze::mazeWasGenerated, this, &MazeArea::requestToEnableAllButtons);
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

    mazeScene_->addItem(cell.getRectForShowCurrentCell());
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::startGenerateMazeGrid(unsigned int mazeSize)
{
    maze_->generateMazeGrid(mazeSize);
}

/*------------------------------------------------------------------------------------------------*/
void MazeArea::startGenerationMaze(int whichAlgorithmWasChosen)
{
    /* Ужасный костыль, но пути назад нет.
    Чему служит: Благодаря "особенной" системе перегенерации лабиринтной сетки при переключении
    между размерами, в случае, если размеры не переключать, то перегенерация сетки не происходит,
    а лабиринт пытается сгенерироваться на сгенерированном поле, из-за чего улетает в бесконечный
    цикл, так как все клетки посещены
    Как работает: Сначала мы проверяем, была ли посещена первая клетка лабиринта (а она становится
    посещенной сразу же при запуске генерации, даже если она была прервана). Если проверка успешна,
    перегенерируем сетку лабиринта. Но из-за того, что метод перегенерации требует в качестве
    параметра размер, а размер хранится только в private maze'а, то беря размер сетки, я получаю
    размер стороны, что и необходимо
    Как улучшить: Возможно стоит переписать способ отправки и хранения размера по аналогии с
    хранением выбранного алгоритма, но с этим тоже есть нюансы. Пока работает - пускай будет так */
    if (maze_->getCellGrid()[0][0].isVisited())
        maze_->generateMazeGrid(maze_->getCellGrid().size());

    maze_->generateMaze(whichAlgorithmWasChosen);
}
