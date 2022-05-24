#include "gui/algorithmgeneratormenu.h"

AlgorithmGeneratorMenu::AlgorithmGeneratorMenu(QWidget *parent) noexcept
    : BaseWidgetMenu(parent)
{
    algorithmAldousBroderRadio_ = new QRadioButton("Aldous Broder");
    algorithmBinaryTreeRadio_ = new QRadioButton("Binary Tree");
    algorithmSidewinderRadio_ = new QRadioButton("Sidewinder");

    startGenerationButton_ = new QPushButton("Start Generation");


    AlgorithmGeneratorMenu::initializeMenu();

// TODO
    algorithmBinaryTreeRadio_->setDisabled(true);
    algorithmSidewinderRadio_->setDisabled(true);
    startGenerationButton_->setDisabled(true);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::initializeMenu()
{
    setTextLabel("Maze Construction Algorithm");

    addRadioButton(algorithmAldousBroderRadio_);
    addRadioButton(algorithmBinaryTreeRadio_);
    addRadioButton(algorithmSidewinderRadio_);

    addPushButton(startGenerationButton_);
}
