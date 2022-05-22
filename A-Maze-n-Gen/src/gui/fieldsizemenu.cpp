#include "gui/fieldsizemenu.h"

FieldSizeMenu::FieldSizeMenu(QWidget *parent) noexcept
    : BaseWidgetMenu(parent)
{
    sizeFirstRadio_ = new MazeSizeRadioButton(5);
    sizeSecondRadio_ = new MazeSizeRadioButton(10);
    sizeThirdRadio_ = new MazeSizeRadioButton(15);

    FieldSizeMenu::initializeMenu();

    connect(sizeFirstRadio_, &MazeSizeRadioButton::toggled, this, &FieldSizeMenu::slotFirstRadio);
    connect(sizeSecondRadio_, &MazeSizeRadioButton::toggled, this, &FieldSizeMenu::slotSecondRadio);
    connect(sizeThirdRadio_, &MazeSizeRadioButton::toggled, this, &FieldSizeMenu::slotThirdRadio);
}

/*---------------------------------------------------------R---------------------------------------*/
void FieldSizeMenu::initializeMenu()
{
    setTextLabel("Field Size");

    addRadioButton(sizeFirstRadio_, true);
    addRadioButton(sizeSecondRadio_);
    addRadioButton(sizeThirdRadio_);
}

/*------------------------------------------------------------------------------------------------*/
void FieldSizeMenu::slotFirstRadio()
{
    emit sendMazeSizeToMazeArea(sizeFirstRadio_->getMazeSize());
}

/*------------------------------------------------------------------------------------------------*/
void FieldSizeMenu::slotSecondRadio()
{
    emit sendMazeSizeToMazeArea(sizeSecondRadio_->getMazeSize());
}

/*------------------------------------------------------------------------------------------------*/
void FieldSizeMenu::slotThirdRadio()
{
    emit sendMazeSizeToMazeArea(sizeThirdRadio_->getMazeSize());
}
