#include "HexagonalMenuWidget.h"

#include <cassert>

QtHexagonalMenu::HexagonalMenuWidget::HexagonalMenuWidget(QWidget* pParent)
    : QWidget(pParent)
    , mParent(pParent)
{
    setMouseTracking(true);

    connect(&mTimer, &QTimer::timeout, this, &HexagonalMenuWidget::Update);
}

void QtHexagonalMenu::HexagonalMenuWidget::Show(int x, int y, int animationStartingIndex)
{
    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    mAnimationStartingIndex = animationStartingIndex;
    mAnimationVariable = 0.0f;
    Update();
    move(x - cx, y - cy);
    setVisible(true);

    mTimer.start(10);
}

void QtHexagonalMenu::HexagonalMenuWidget::Hide()
{
    setVisible(false);

    for (const auto& [index, button] : mButtons)
    {
        button->setVisible(false);
    }
}

void QtHexagonalMenu::HexagonalMenuWidget::mousePressEvent(QMouseEvent* pEvent)
{
    OnMousePressed(pEvent);
}

void QtHexagonalMenu::HexagonalMenuWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
    OnMouseMoved(pEvent);
}

void QtHexagonalMenu::HexagonalMenuWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
    OnMouseReleased(pEvent);
}

void QtHexagonalMenu::HexagonalMenuWidget::OnMouseReleased(QMouseEvent* pEvent)
{
    for (const auto& [index, button] : mButtons)
    {
        button->OnMouseReleased(pEvent);
    }
}

void QtHexagonalMenu::HexagonalMenuWidget::OnMousePressed(QMouseEvent* pEvent)
{
    for (const auto& [index, button] : mButtons)
    {
        button->OnMousePressed(pEvent);
    }
}

void QtHexagonalMenu::HexagonalMenuWidget::OnMouseMoved(QMouseEvent* pEvent)
{
    for (const auto& [index, button] : mButtons)
    {
        button->OnMouseMoved(pEvent);
    }
}

void QtHexagonalMenu::HexagonalMenuWidget::AddButton(int index, const QString& name)
{
    assert(mButtons[index] == nullptr);

    const auto pButton = new HexagonalButton(this);
    pButton->setVisible(false);
    pButton->setAttribute(Qt::WA_TransparentForMouseEvents);
    pButton->SetLabel(name);

    connect(pButton, &HexagonalButton::MousePressed, this, [this, index]()
            { emit ButtonClicked(index); });

    mButtons[index] = pButton;
}

QPointF QtHexagonalMenu::HexagonalMenuWidget::GetCenter() const
{
    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    return mapToParent(QPoint(cx, cy));
}

void QtHexagonalMenu::HexagonalMenuWidget::Update()
{
    mAnimationVariable += 0.025f;

    if (mAnimationVariable > 1.0f)
    {
        mAnimationVariable = 1.0f;
        mTimer.stop();
    }

    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    for (const auto& [index, button] : mButtons)
    {
        float angle;

        angle = M_PI / 6.0f + mAnimationVariable * (index - mAnimationStartingIndex) * M_PI / 3.0f + mAnimationStartingIndex * M_PI / 3.0f;

        const float rw = 0.3f * w;
        const float rh = 0.3f * h;
        const float pw = w / 3.0f;
        const float ph = h / 3.0f;
        button->setFixedSize(pw, ph);
        button->move(cx + rw * std::cos(-angle) - 0.5f * pw, cy + rh * std::sin(-angle) - 0.5f * ph);
        button->setVisible(true);
    }
}
