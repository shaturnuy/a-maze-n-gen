#pragma once

#include "basewidgetmenu.h"
#include "mazesizeradiobutton.h"
#include "mazearea.h"

class FieldSizeMenu : public BaseWidgetMenu
{
    Q_OBJECT

private:
/*  3 очередь. Вероятно, следует сделать кнопки и ассоциированные с ними слоты с помощью векторов
    и указателей на функции (если возможно таким образом создать слоты), ибо сейчас выглядит ужасно.
    Возможно вообще переделать на вводимый юзером размер клеток */
    MazeSizeRadioButton *sizeFirstRadio_ {nullptr};
    MazeSizeRadioButton *sizeSecondRadio_ {nullptr};
    MazeSizeRadioButton *sizeThirdRadio_ {nullptr};

signals:
    void sendMazeSizeToMazeArea(unsigned int mazeSize);

private slots:
    void slotFirstRadio();
    void slotSecondRadio();
    void slotThirdRadio();

public:
    explicit FieldSizeMenu(QWidget *parent = nullptr) noexcept;
    void initializeMenu();

    virtual ~FieldSizeMenu() {};
};
