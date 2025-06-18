#include "Menu.h"

QtHexagonalMenu::Menu::Menu(QWidget* pParent, const QString& name)
    : QObject(pParent)
    , mParent(pParent)
    , mName(name)
{
}

bool QtHexagonalMenu::Menu::OnMouseReleased(const QPointF& position)
{
    if (!mHexagonalMenuWidget)
    {
        return false;
    }

    if (mHexagonalMenuWidget->isVisible())
    {
        mHexagonalMenuWidget->OnMouseReleased(mHexagonalMenuWidget->mapFromParent(position));
    }

    for (const auto& [index, pChild] : mChildren)
    {
        pChild->OnMouseReleased(position);
    }

    return false;
}

bool QtHexagonalMenu::Menu::OnMousePressed(const QPointF& position)
{
    if (!mHexagonalMenuWidget)
    {
        return false;
    }

    bool consumed = false;

    if (mHexagonalMenuWidget->isVisible())
    {
        consumed = mHexagonalMenuWidget->OnMousePressed(mHexagonalMenuWidget->mapFromParent(position));
    }

    if (!consumed)
    {
        for (const auto& [index, pChild] : mChildren)
        {
            if (pChild->OnMousePressed(position))
            {
                consumed = true;
            }
        }
    }

    return consumed;
}

bool QtHexagonalMenu::Menu::OnMouseMoved(const QPointF& position)
{
    if (!mHexagonalMenuWidget)
    {
        return false;
    }

    bool consumed = false;

    if (mHexagonalMenuWidget->isVisible())
    {
        consumed = mHexagonalMenuWidget->OnMouseMoved(mHexagonalMenuWidget->mapFromParent(position));
    }

    if (!consumed)
    {
        for (const auto& [index, pChild] : mChildren)
        {
            if (pChild->OnMouseMoved(position))
            {
                consumed = true;
            }
        }
    }

    return consumed;
}

void QtHexagonalMenu::Menu::AddChildren(const std::map<int, Menu*>& children)
{
    assert(mChildren.empty());

    mChildren = children;

    mHexagonalMenuWidget = new HexagonalMenuWidget(mParent);
    mHexagonalMenuWidget->setFixedSize(300, 300);
    mHexagonalMenuWidget->setVisible(false);

    for (const auto& [index, pMenu] : mChildren)
    {
        mHexagonalMenuWidget->AddButton(index, pMenu->GetName());
    }

    connect(mHexagonalMenuWidget, &HexagonalMenuWidget::ButtonClicked, this, [=](int index)
            { ShowChild(index); });
}

void QtHexagonalMenu::Menu::Hide()
{
    if (mHexagonalMenuWidget)
    {
        mHexagonalMenuWidget->Hide();
    }

    for (const auto& [index, pMenu] : mChildren)
    {
        pMenu->Hide();
    }
}

const QString& QtHexagonalMenu::Menu::GetName() const
{
    return mName;
}

QtHexagonalMenu::HexagonalMenuWidget* QtHexagonalMenu::Menu::GetWidget() const
{
    return mHexagonalMenuWidget;
}

void QtHexagonalMenu::Menu::ShowChild(int index)
{
    for (const auto& [index, pMenu] : mChildren)
    {
        pMenu->Hide();
    }

    const auto* pChild = mChildren[index];
    const auto center = mHexagonalMenuWidget->GetCenter();
    const auto angle = M_PI / 6.0f + +index * M_PI / 3.0f;
    const auto r = 0.9f * mHexagonalMenuWidget->width();
    const auto animationStartingIndex = (index + 3) % 6;
    const auto position = center + r * QPointF(std::cos(-angle), std::sin(-angle));

    if (auto* pWidget = pChild->GetWidget())
    {
        pWidget->Show(position.x(), position.y(), animationStartingIndex);
    }
}
