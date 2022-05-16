#pragma once

#include "algorithmgeneratormenu.h"
#include "fieldsizemenu.h"
#include "maze.h"

#include <QWidget>
#include <QLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPen>
#include <QRectF>
#include <QRect>
#include <QGroupBox>

class MainWindow : public QWidget
{
    Q_OBJECT

private:

    const int               WINDOW_SIZE_WIDTH           {600};
    const int               WINDOW_SIZE_HEIGHT          {300};

    FieldSizeMenu           *fieldSizeWidget_           {nullptr};
    AlgorithmGeneratorMenu  *algorithmGeneratorWidget_  {nullptr};
    QVBoxLayout             *sidebarLayout_             {nullptr};

public:

    explicit MainWindow(QWidget *parent = nullptr);
};
