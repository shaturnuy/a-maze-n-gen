#pragma once

#include "basewidgetmenu.h"

#include <QRadioButton>
#include <QString>

class FieldSizeMenu : public BaseWidgetMenu
{

private:

    QRadioButton *sizeFirstRadio_ {nullptr};
    QRadioButton *sizeSecondRadio_ {nullptr};
    QRadioButton *sizeThirdRadio_ {nullptr};

public:

    explicit FieldSizeMenu(QWidget *parent = nullptr) noexcept;

    void addRadioButton(QRadioButton *radioButton, unsigned int sizeOfMazeGrid, bool isFirstRadioButtonInList = false);
    void initializeMenu();
};
