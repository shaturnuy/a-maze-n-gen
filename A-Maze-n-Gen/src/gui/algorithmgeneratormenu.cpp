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

    connect(algorithmAldousBroderRadio_, &QRadioButton::toggled, this, &AlgorithmGeneratorMenu::slotAldousBroderRadio);
    connect(startGenerationButton_, &QPushButton::clicked, this, &AlgorithmGeneratorMenu::slotStartGenerationButton);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::initializeMenu()
{
    setTextLabel("Maze Construction Algorithm");

    addRadioButton(algorithmAldousBroderRadio_);
    addRadioButton(algorithmBinaryTreeRadio_);
    addRadioButton(algorithmSidewinderRadio_);

    addPushButton(startGenerationButton_);
    startGenerationButton_->setDisabled(true);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::slotAldousBroderRadio()
{
    whichAlgorithmWasChosen_ = AlgorithmGeneratorMenu::AldousBroderAlgorithm;
    emit algorithmReadyToGenerate();
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::activateGenerateButton()
{
    /* Данный слот связан с двуями сигналами, один из которых отправляется из этого же объекта при
    нажатии кнопки выбора алгоритма генерации. Поэтому здесь происходит проверка "если отправитель
    этот же объект" ..., а если нет, значит вариантов больше нет и это сигнал из fieldSizeMenu */
    if (sender() == this)
        isAlgorithmReadyToGenerate_ = true;
    else
        isFieldReadyToGenerate_ = true;

    if (isFieldReadyToGenerate_ && isAlgorithmReadyToGenerate_)
        startGenerationButton_->setDisabled(false);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::slotStartGenerationButton()
{
    // Выключаем кнопку до момента, пока лабиринт не сгенерируется
    startGenerationButton_->setDisabled(true);
    emit startGenerationMaze(whichAlgorithmWasChosen_);
}
