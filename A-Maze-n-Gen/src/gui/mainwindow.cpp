#include "gui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) noexcept
    : QWidget(parent)
{
    setWindowTitle("A-Maze-n-Gen");
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    initializeSidebar();

    mazeGrid_ = new MazeArea(this);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(5);
    mainLayout->addWidget(mazeGrid_);
    mainLayout->addLayout(sidebarLayout_);

    setLayout(mainLayout);


    connect(fieldSizeWidget_, &FieldSizeMenu::sendMazeSizeToMazeArea, mazeGrid_, &MazeArea::setMazeSize);
}

/*------------------------------------------------------------------------------------------------*/
void MainWindow::initializeSidebar()
{
    fieldSizeWidget_ = new FieldSizeMenu(this);
    algorithmGeneratorWidget_ = new AlgorithmGeneratorMenu(this);

    sidebarLayout_ = new QVBoxLayout;
    sidebarLayout_->setSpacing(5);
    sidebarLayout_->setAlignment(Qt::AlignRight | Qt::AlignTop);

    sidebarLayout_->addWidget(fieldSizeWidget_);
    sidebarLayout_->addWidget(algorithmGeneratorWidget_);
}
