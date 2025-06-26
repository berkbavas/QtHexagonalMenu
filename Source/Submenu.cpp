#include "Submenu.h"

#include <QWidget>

Submenu::Submenu(QWidget* pParent, int index)
    : QObject(pParent)
    , mParent(pParent)
{
    mHexagonalMenuWidget = new HexagonalMenuWidget(mParent, index);
    mHexagonalMenuWidget->setFixedSize(400, 400);
    mHexagonalMenuWidget->setVisible(false);
    connect(mHexagonalMenuWidget, &HexagonalMenuWidget::ButtonClicked, this, &Submenu::HandleButtonClick);
}

void Submenu::Show(int x, int y)
{
    mHexagonalMenuWidget->Show(x, y);
}

void Submenu::SetChildLevel(int level)
{
    mHexagonalMenuWidget->SetChildLevel(level);

    for (const auto pSubmenu : mSubmenus)
    {
        pSubmenu->SetChildLevel(level + 1);
    }
}

void Submenu::Hide()
{
    for (const auto pSubmenu : mSubmenus)
    {
        pSubmenu->Hide();
    }

    mHexagonalMenuWidget->Hide();
}

void Submenu::AddButton(int index, const QString& label)
{
    mHexagonalMenuWidget->AddButton(index, label);
}

void Submenu::AddSubmenu(int index, Submenu* pSubmenu)
{
    mSubmenus[index] = pSubmenu;

    connect(pSubmenu, &Submenu::RequestHide, this, &Submenu::RequestHide);
}

bool Submenu::OnMouseReleased(const QPointF& point)
{
    if (!mHexagonalMenuWidget->OnMouseReleased(point))
    {
        for (const auto pSubmenu : mSubmenus)
        {
            if (pSubmenu->OnMouseReleased(point))
            {
                return true;
            }
        }
    }
    else
    {
        return true;
    }

    return false;
}

bool Submenu::OnMousePressed(const QPointF& point)
{
    if (!mHexagonalMenuWidget->OnMousePressed(point))
    {
        for (const auto pSubmenu : mSubmenus)
        {
            if (pSubmenu->OnMousePressed(point))
            {
                return true;
            }
        }
    }
    else
    {
        return true;
    }

    return false;
}

bool Submenu::OnMouseMoved(const QPointF& point)
{
    if (!mHexagonalMenuWidget->OnMouseMoved(point))
    {
        for (const auto pSubmenu : mSubmenus)
        {
            if (pSubmenu->OnMouseMoved(point))
            {
                return true;
            }
        }
    }
    else
    {
        return true;
    }

    return false;
}

void Submenu::HandleButtonClick(int index)
{
    if (mSubmenus.contains(index))
    {
        ShowChild(index);
    }
    else
    {
        emit RequestHide();
        emit ButtonClicked(index);
    }
}

void Submenu::ShowChild(int index)
{
    for (const auto pSubmenu : mSubmenus)
    {
        pSubmenu->Hide();
    }

    const auto pChild = mSubmenus[index];
    const auto center = mHexagonalMenuWidget->GetCenter();
    const auto angle = M_PI / 6.0f + index * M_PI / 3.0f;
    const auto r = 0.6f * mHexagonalMenuWidget->width();
    const auto animationStartingIndex = (index + 3) % 6;
    const auto position = center + r * QPointF(std::cos(-angle), std::sin(-angle));

    pChild->Show(position.x(), position.y());
}
