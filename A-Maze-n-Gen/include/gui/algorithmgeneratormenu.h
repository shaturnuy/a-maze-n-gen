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

    int whichAlgorithmWasChosen_ {};
    bool isFieldReadyToGenerate_ {false};
    bool isAlgorithmReadyToGenerate_ {false};

public:
    AlgorithmGeneratorMenu(QWidget *parent = nullptr) noexcept;
    ~AlgorithmGeneratorMenu() {};

    void initializeMenu();
    enum {AldousBroderAlgorithm};

signals:
    void algorithmReadyToGenerate();
    void startGenerationMaze(int whichAlgorithmWasChosen);
    /* Вероятно, не самая лучшая реализация передачи информации о выбранном алгоритме генерации,
    т.к. подобное решение влечет за собой необходимость переписывания кода в получателе (maze)
    при необходимости замены алгоритма. Однако, на данный момент при текущей "архитектуре" я не
    знаю, как это возможно реализовать изящнее */

private slots:
    void slotAldousBroderRadio();
    void slotStartGenerationButton();

public slots:
    void activateGenerateButton();
};
