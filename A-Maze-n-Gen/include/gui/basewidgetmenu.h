#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>

class BaseWidgetMenu : public QWidget
{
    Q_OBJECT

private:

    const int TITLE_LABEL_SIZE {250};
    const int PUSH_BUTTON_SIZE {150};
    const QString GROUP_BOX_STYLE_SHEET {
        "QGroupBox {border-style: double;"
                   "border-width: 3px;}"
        "QLabel    {border-bottom-width: 1px;"
                   "border-bottom-style: solid;"
                   "border-radius: 0px;"
                   "font-size: 16pt;}"
        "*         {font-family: Centaur;"
                   "font-size: 14pt;}"};


    QLabel *titleLabel_ {nullptr};
    QVBoxLayout *menuLayout_ {nullptr};
    QGroupBox *menuGroupBox_ {nullptr};

public:

    explicit BaseWidgetMenu(QWidget *parent = nullptr);

    virtual void initializeMenu() = 0;

    void setTextLabel(const QString textLabel);
    void addRadioButton(QRadioButton *radioButton, bool isFirstRadioButtonInList = false);
    void addPushButton(QPushButton *pushButton);

    virtual ~BaseWidgetMenu() {};
};
