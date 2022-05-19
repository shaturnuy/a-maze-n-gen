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

/*  Попытка сделать полиморфично-красивый метод была провалена
    Ни одно решение из инета не помогло, скорее всего здесь какая-то базовая ошибка в логике, которую я не вижу
    Потрачено слишком много времени на это, возвращаю старое некрасивое (зато рабочее) решение
    Заниматься этим в самую последнюю очередь, если будут идеи
    void addRadioButton(QRadioButton *radioButton, unsigned int sizeOfMazeGrid, bool isFirstRadioButtonInList = false); */
    void initializeMenu();

    virtual ~FieldSizeMenu() {};
};
