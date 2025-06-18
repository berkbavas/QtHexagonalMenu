#include "Example.h"

#include <QMouseEvent>
#include <QStyle>

QtHexagonalMenu::Example::Example(QWidget* pParent)
    : QWidget(pParent)
{
    mHexagonalMenuWidget = new HexagonalMenuWidget(this);
    mHexagonalMenuWidget->setFixedSize(300, 300);
    mHexagonalMenuWidget->AddButton(0, "Item 0");
    mHexagonalMenuWidget->AddButton(1, "Item 1");
    mHexagonalMenuWidget->AddButton(2, "Item 2");
    mHexagonalMenuWidget->AddButton(3, "Item 3");
    mHexagonalMenuWidget->AddButton(4, "Item 4");
    mHexagonalMenuWidget->AddButton(5, "Item 5");
    mHexagonalMenuWidget->setVisible(false);

    mHexagonalMenuWidgetChild = new HexagonalMenuWidget(this);
    mHexagonalMenuWidgetChild->setFixedSize(300, 300);
    mHexagonalMenuWidgetChild->AddButton(0, "0");
    mHexagonalMenuWidgetChild->AddButton(1, "1");
    mHexagonalMenuWidgetChild->AddButton(2, "2");
    mHexagonalMenuWidgetChild->AddButton(3, "3");
    mHexagonalMenuWidgetChild->AddButton(4, "4");
    mHexagonalMenuWidgetChild->AddButton(5, "5");
    mHexagonalMenuWidgetChild->setVisible(false);

    connect(mHexagonalMenuWidget, &HexagonalMenuWidget::ButtonClicked, this, [=](int index)
            {
                const auto center = mHexagonalMenuWidget->GetCenter();
                const auto angle = M_PI / 6.0f + +index * M_PI / 3.0f;
                const auto r = 0.9f * mHexagonalMenuWidget->width();
                const auto animationStartingIndex = (index + 3) % 6;
                const auto position = center + r * QPointF(std::cos(-angle), std::sin(-angle));
                mHexagonalMenuWidgetChild->Show(position.x(), position.y(), animationStartingIndex);
                //
            });
}

void QtHexagonalMenu::Example::mousePressEvent(QMouseEvent* pEvent)
{
    mHexagonalMenuWidgetChild->Hide();

    if (pEvent->button() == Qt::RightButton)
    {
        mHexagonalMenuWidget->Hide();
    }
    else
    {
        mHexagonalMenuWidget->Show(pEvent->position().x(), pEvent->position().y(), 3);
    }
}
