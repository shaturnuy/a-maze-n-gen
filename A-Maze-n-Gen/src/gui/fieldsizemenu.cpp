#include "gui/fieldsizemenu.h"

FieldSizeMenu::FieldSizeMenu(QWidget *parent) noexcept
    : BaseWidgetMenu(parent)
{
    sizeFirstRadio_ = new QRadioButton;
    sizeSecondRadio_ = new QRadioButton;
    sizeThirdRadio_ = new QRadioButton;

    FieldSizeMenu::initializeMenu();

//  TODO
    sizeSecondRadio_->setDisabled(true);
    sizeThirdRadio_->setDisabled(true);
}

/*------------------------------------------------------------------------------------------------*/
void FieldSizeMenu::initializeMenu()
{
    setTextLabel("Field Size");

    addRadioButton(sizeFirstRadio_, 5, true);
    addRadioButton(sizeSecondRadio_, 10);
    addRadioButton(sizeThirdRadio_, 15);
}

/*------------------------------------------------------------------------------------------------*/
void addRadioButton(QRadioButton *radioButton, unsigned int sizeOfMazeGrid, bool isFirstRadioButtonInList = false)
{
    BaseWidgetMenu::addRadioButton(radioButton, isFirstRadioButtonInList);
    radioButton->setText(QString::number(sizeOfMazeGrid) + " x " + QString::number(sizeOfMazeGrid));
}
