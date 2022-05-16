#include "gui/mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("A-Maze-n-Gen");
    resize(WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);


    fieldSizeWidget_ = new FieldSizeMenu(this);
    algorithmGeneratorWidget_ = new AlgorithmGeneratorMenu(this);


    sidebarLayout_ = new QVBoxLayout;
    sidebarLayout_->setSpacing(5);
    sidebarLayout_->setAlignment(Qt::AlignRight | Qt::AlignTop);

    sidebarLayout_->addWidget(fieldSizeWidget_);
    sidebarLayout_->addWidget(algorithmGeneratorWidget_);

//---------------TEST--------------

    QGraphicsView *testView = new QGraphicsView;
    testView->setFixedSize(303, 303);

    QGraphicsScene *testScene = new QGraphicsScene;
    testView->setScene(testScene);

    Maze maze(testScene);
//    testScene->addRect(QRectF(QRect(0, 0, 60, 60)));
//    testScene->addRect(QRectF(QRect(60, 60, 60, 60)));
//    testScene->addRect(QRectF(QRect(120, 120, 60, 60)));
//    testScene->addRect(QRectF(QRect(180, 180, 60, 60)));
//    testScene->addRect(QRectF(QRect(240, 240, 60, 60)));

    QVBoxLayout *fieldLayout = new QVBoxLayout();
    fieldLayout->setAlignment(Qt::AlignCenter);
    fieldLayout->addWidget(testView);

    QGroupBox *fieldGroupBox = new QGroupBox;
    fieldGroupBox->setStyleSheet(        "QGroupBox {border-style: double;"
                                         "border-width: 3px;}");
    fieldGroupBox->setLayout(fieldLayout);


    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(5);
    mainLayout->addWidget(fieldGroupBox);
    mainLayout->addLayout(sidebarLayout_);

    setLayout(mainLayout);
}
