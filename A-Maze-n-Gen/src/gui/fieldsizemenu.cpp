#include "gui/fieldsizemenu.h"

FieldSizeMenu::FieldSizeMenu(QWidget *parent) noexcept
    : BaseWidgetMenu(parent)
{
    sizeFirstRadio_ = new QRadioButton("5x5");
    sizeSecondRadio_ = new QRadioButton("10x10");
    sizeThirdRadio_ = new QRadioButton("15x15");

    FieldSizeMenu::initializeMenu();

//  TODO
    sizeSecondRadio_->setDisabled(true);
    sizeThirdRadio_->setDisabled(true);
}

/*------------------------------------------------------------------------------------------------*/
void FieldSizeMenu::initializeMenu()
{
    setTextLabel("Field Size");

    addRadioButton(sizeFirstRadio_, true);
    addRadioButton(sizeSecondRadio_);
    addRadioButton(sizeThirdRadio_);
}
