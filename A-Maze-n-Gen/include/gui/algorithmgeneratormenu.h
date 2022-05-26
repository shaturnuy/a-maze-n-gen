#pragma once

#include "basewidgetmenu.h"
#include "mazearea.h"

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

    bool isFieldReadyToGenerate_ {false};
    bool isAlgorithmReadyToGenerate_ {false};

public:
    AlgorithmGeneratorMenu(QWidget *parent = nullptr) noexcept;
    ~AlgorithmGeneratorMenu() {};

    void initializeMenu();

signals:
    void algorithmReadyToGenerate();

private slots:
    void slotAldousBroderRadio();

public slots:
    void activateGenerateButton();
};
