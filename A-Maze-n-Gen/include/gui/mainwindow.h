#pragma once

#include "algorithmgeneratormenu.h"
#include "fieldsizemenu.h"
#include "mazearea.h"
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
    FieldSizeMenu *fieldSizeWidget_ {nullptr};
    AlgorithmGeneratorMenu *algorithmGeneratorWidget_ {nullptr};
    QVBoxLayout *sidebarLayout_ {nullptr};

    MazeArea *mazeGrid_ {nullptr};

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initializeSidebar();
};
