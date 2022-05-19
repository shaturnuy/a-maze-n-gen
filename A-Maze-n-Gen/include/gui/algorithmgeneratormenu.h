#pragma once

#include "basewidgetmenu.h"

#include <QRadioButton>
#include <QPushButton>

class AlgorithmGeneratorMenu : public BaseWidgetMenu
{

private:

    QRadioButton *algorithmAldousBroderRadio_ {nullptr};
    QRadioButton *algorithmBinaryTreeRadio_ {nullptr};
    QRadioButton *algorithmSidewinderRadio_ {nullptr};

    QPushButton *startGenerationButton_ {nullptr};

public:

    explicit AlgorithmGeneratorMenu(QWidget *parent = nullptr);

    void initializeMenu();

    virtual ~AlgorithmGeneratorMenu() {};
};
