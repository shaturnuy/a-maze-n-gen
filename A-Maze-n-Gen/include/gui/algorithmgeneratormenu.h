#pragma once

#include "basewidgetmenu.h"

#include <QRadioButton>
#include <QPushButton>

class AlgorithmGeneratorMenu : public BaseWidgetMenu
{
    Q_OBJECT

private:
    QRadioButton *algorithmAldousBroderRadio_ {nullptr};
    QRadioButton *algorithmBinaryTreeRadio_ {nullptr};
    QRadioButton *algorithmSidewinderRadio_ {nullptr};

    QPushButton *startGenerationButton_ {nullptr};

public:
    AlgorithmGeneratorMenu(QWidget *parent = nullptr) noexcept;
    ~AlgorithmGeneratorMenu() {};

    void initializeMenu();
};
