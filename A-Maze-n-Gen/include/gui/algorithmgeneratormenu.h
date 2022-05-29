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

    enum {AldousBroderAlgorithm};

    void initializeMenu();

signals:
    void algorithmReadyToGenerate();
    void startGenerationMaze(int whichAlgorithmWasChosen);

private slots:
    void slotAldousBroderRadio();
    void slotStartGenerationButton();

public slots:
    void activateGenerateButton();
};
