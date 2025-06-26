#include "Example.h"

#include <QMouseEvent>
#include <QStyle>

Example::Example(QWidget* pParent)
    : QWidget(pParent)
{
    mMenu = new Menu(this);
    setMouseTracking(true);
}

void Example::mouseMoveEvent(QMouseEvent* pEvent)
{
    mMenu->OnMouseMoved(pEvent->position());
}

void Example::mousePressEvent(QMouseEvent* pEvent)
{
    if (!mMenu->OnMousePressed(pEvent->position()))
    {
        mMenu->Hide();
        mMenu->Show(pEvent->position().x(), pEvent->position().y(), 0);
    }
}

void Example::mouseReleaseEvent(QMouseEvent* pEvent)
{
    mMenu->OnMouseReleased(pEvent->position());
}
