#include "gui/startstoppushbutton.h"

StartStopPushButton::StartStopPushButton() noexcept
    : QPushButton("Start Generation")
{
    setStyleSheet(inactiveStateColor_);
}

/*------------------------------------------------------------------------------------------------*/
void StartStopPushButton::makeStateStart()
{
    setStyleSheet(startStateColor_);
    setText("Start Generation");
}

/*------------------------------------------------------------------------------------------------*/
void StartStopPushButton::makeStateStop()
{
    setStyleSheet(stopStateColor_);
    setText("STOP");
}
