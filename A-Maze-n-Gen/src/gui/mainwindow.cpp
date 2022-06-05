#include "gui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) noexcept
    : QWidget(parent)
{
    initializeMazeSettingsMenu();
    initializeMazeArea();
    initializeMainWindow();

    connect(fieldSizeWidget_, &FieldSizeMenu::sendMazeSize, mazeGrid_, &MazeArea::startGenerateMazeGrid);

    connect(mazeGrid_, &MazeArea::fieldReadyToGenerate,
            algorithmGeneratorWidget_, &AlgorithmGeneratorMenu::activateGenerateButton);
    connect(algorithmGeneratorWidget_, &AlgorithmGeneratorMenu::algorithmReadyToGenerate,
            algorithmGeneratorWidget_, &AlgorithmGeneratorMenu::activateGenerateButton);

    connect(algorithmGeneratorWidget_, &AlgorithmGeneratorMenu::startGenerationMaze,
            mazeGrid_, &MazeArea::startGenerationMaze);
}

/*------------------------------------------------------------------------------------------------*/
void MainWindow::initializeMazeSettingsMenu()
{
    fieldSizeWidget_ = new FieldSizeMenu(this);
    algorithmGeneratorWidget_ = new AlgorithmGeneratorMenu(this);

    sidebarLayout_ = new QVBoxLayout;
    sidebarLayout_->setSpacing(5);
    sidebarLayout_->setAlignment(Qt::AlignRight | Qt::AlignTop);

    sidebarLayout_->addWidget(fieldSizeWidget_);
    sidebarLayout_->addWidget(algorithmGeneratorWidget_);
}

/*------------------------------------------------------------------------------------------------*/
void MainWindow::initializeMazeArea()
{
    mazeGrid_ = new MazeArea(this);
}

/*------------------------------------------------------------------------------------------------*/
void MainWindow::initializeMainWindow()
{
    setWindowTitle("A-Maze-n-Gen");
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    mainLayout_ = new QHBoxLayout(this);
    mainLayout_->setSpacing(5);
    mainLayout_->addWidget(mazeGrid_);
    mainLayout_->addLayout(sidebarLayout_);
    setLayout(mainLayout_);
}
