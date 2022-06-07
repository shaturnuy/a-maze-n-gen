#pragma once

#include "basewidgetmenu.h"
#include "startstoppushbutton.h"

#include <QRadioButton>
#include <QPushButton>

class AlgorithmGeneratorMenu : public BaseWidgetMenu
{
    Q_OBJECT

private:
    QRadioButton *algorithmAldousBroderRadio_ {nullptr};
    QRadioButton *algorithmRecursiveBacktrackerRadio_ {nullptr};
    QRadioButton *algorithmSidewinderRadio_ {nullptr};

    StartStopPushButton *startGenerationButton_ {nullptr};

    int whichAlgorithmWasChosen_ {};
    bool isFieldReadyToGenerate_ {false};
    bool isAlgorithmReadyToGenerate_ {false};

public:
    AlgorithmGeneratorMenu(QWidget *parent = nullptr) noexcept;
    ~AlgorithmGeneratorMenu() {};

    void initializeMenu();
    void setDisabledButtons(bool makeButtonsDisabled);
    enum Algorithm {AldousBroder, RecursiveBacktracker};

signals:
    void algorithmReadyToGenerate();
    void requestToDisableAllButtons();
    void interruptGeneration();
    void startGenerationMaze(int whichAlgorithmWasChosen);
    /* Вероятно, не самая лучшая реализация передачи информации о выбранном алгоритме генерации,
     * т.к. подобное решение влечет за собой необходимость переписывания кода в получателе (maze)
     * при необходимости замены алгоритма. Однако, на данный момент при текущей "архитектуре" я не
     * знаю, как это возможно реализовать изящнее */

private slots:
    void slotAldousBroderRadio();
    void slotRecursiveBacktrackerRadio();
    void slotStartGenerationButton();

public slots:
    void activateGenerateButton();
};
