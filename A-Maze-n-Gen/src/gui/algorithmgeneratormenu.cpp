#include "gui/algorithmgeneratormenu.h"

AlgorithmGeneratorMenu::AlgorithmGeneratorMenu(QWidget *parent) noexcept
    : BaseWidgetMenu(parent)
{
    algorithmAldousBroderRadio_ = new QRadioButton("Aldous Broder");
    algorithmRecursiveBacktrackerRadio_ = new QRadioButton("Recursive Backtracker");
    algorithmSidewinderRadio_ = new QRadioButton("Sidewinder");
    startGenerationButton_ = new StartStopPushButton();

    AlgorithmGeneratorMenu::initializeMenu();


    connect(algorithmAldousBroderRadio_, &QRadioButton::toggled,
            this, &AlgorithmGeneratorMenu::slotAldousBroderRadio);
    connect(algorithmRecursiveBacktrackerRadio_, &QRadioButton::toggled,
            this, &AlgorithmGeneratorMenu::slotRecursiveBacktrackerRadio);
    connect(startGenerationButton_, &QPushButton::clicked,
            this, &AlgorithmGeneratorMenu::slotStartGenerationButton);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::initializeMenu()
{
    setTextLabel("Maze Construction Algorithm");

    addRadioButton(algorithmAldousBroderRadio_);
    addRadioButton(algorithmRecursiveBacktrackerRadio_);
    addRadioButton(algorithmSidewinderRadio_);

    addPushButton(startGenerationButton_);
    startGenerationButton_->setDisabled(true);
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::slotAldousBroderRadio()
{
    whichAlgorithmWasChosen_ = AlgorithmGeneratorMenu::Algorithm::AldousBroder;
    emit algorithmReadyToGenerate();
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::slotRecursiveBacktrackerRadio()
{
    whichAlgorithmWasChosen_ = AlgorithmGeneratorMenu::Algorithm::RecursiveBacktracker;
    emit algorithmReadyToGenerate();
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::activateGenerateButton()
{
    /* Данный слот связан с двуями сигналами, один из которых отправляется из этого же объекта при
     * нажатии кнопки выбора алгоритма генерации. Поэтому здесь происходит проверка "если
     * отправитель этот же объект" ..., а если нет, значит вариантов больше нет и это сигнал
     * из fieldSizeMenu */
    if (sender() == this)
        isAlgorithmReadyToGenerate_ = true;
    else
        isFieldReadyToGenerate_ = true;

    if (isFieldReadyToGenerate_ && isAlgorithmReadyToGenerate_)
    {
        startGenerationButton_->setDisabled(false);
        startGenerationButton_->makeStateStart();
    }
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::slotStartGenerationButton()
{
    if (startGenerationButton_->checkCurrentButtonState() == StartStopPushButton::ButtonState::Start)
    {
        // Выключаем кнопки до момента, пока лабиринт не сгенерируется (или не будет остановлен)
        emit requestToDisableAllButtons();
        emit startGenerationMaze(whichAlgorithmWasChosen_);
    }
    else
    {
        emit interruptGeneration();
    }
}

/*------------------------------------------------------------------------------------------------*/
void AlgorithmGeneratorMenu::setDisabledButtons(bool makeButtonsDisabled)
{
    algorithmAldousBroderRadio_->setDisabled(makeButtonsDisabled);
    algorithmRecursiveBacktrackerRadio_->setDisabled(makeButtonsDisabled);
    algorithmSidewinderRadio_->setDisabled(makeButtonsDisabled);

    if (makeButtonsDisabled == false)
        startGenerationButton_->makeStateStart();
    else
        startGenerationButton_->makeStateStop();
}
