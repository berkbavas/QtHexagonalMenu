#include "HexagonalMenuWidget.h"

#include <cassert>

HexagonalMenuWidget::HexagonalMenuWidget(QWidget* pParent)
    : QWidget(pParent)
    , mParent(pParent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(&mTimer, &QTimer::timeout, this, &HexagonalMenuWidget::Update);
}

void HexagonalMenuWidget::Show(int x, int y, int animationStartingIndex)
{
    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    mAnimationStartingIndex = animationStartingIndex;
    mAnimationVariable = 0.0f;

    move(x - cx, y - cy);
    setVisible(true);

    mTimer.start(10);
}

void HexagonalMenuWidget::Hide()
{
    setVisible(false);

    for (const auto& [index, pButton] : mButtons)
    {
        pButton->setVisible(false);
    }
}

bool HexagonalMenuWidget::OnMouseReleased(const QPointF& point)
{
    for (const auto& [index, pButton] : mButtons)
    {
        if (pButton->OnMouseReleased(mapFromParent(point)))
        {
            return true;
        }
    }

    return false;
}

bool HexagonalMenuWidget::OnMousePressed(const QPointF& point)
{
    for (const auto& [index, pButton] : mButtons)
    {
        if (pButton->OnMousePressed(mapFromParent(point)))
        {
            return true;
        }
    }

    return false;
}

bool HexagonalMenuWidget::OnMouseMoved(const QPointF& point)
{
    for (const auto& [index, pButton] : mButtons)
    {
        if (pButton->OnMouseMoved(mapFromParent(point)))
        {
            return true;
        }
    }

    return false;
}

void HexagonalMenuWidget::AddButton(int index, const QString& name)
{
    assert(mButtons[index] == nullptr);

    const auto pButton = new HexagonalButton(this);
    pButton->setVisible(false);
    pButton->SetLabel(name);

    connect(pButton, &HexagonalButton::Clicked, this, [this, index]()
            { emit ButtonClicked(index); });

    mButtons[index] = pButton;
}

QPointF HexagonalMenuWidget::GetCenter() const
{
    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    return mapToParent(QPoint(cx, cy));
}

void HexagonalMenuWidget::SetChildLevel(int level)
{
    mChildLevel = level;
}

void HexagonalMenuWidget::Update()
{
    mAnimationVariable += 0.035f;

    if (mAnimationVariable > 1.0f)
    {
        mAnimationVariable = 1.0f;
        mTimer.stop();
    }

    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

    for (const auto& [index, pButton] : mButtons)
    {
        float angle;

        angle = M_PI / 6.0f + mAnimationVariable * (index - mAnimationStartingIndex) * M_PI / 3.0f + mAnimationStartingIndex * M_PI / 3.0f;

        const float rw = 0.3f * w;
        const float rh = 0.3f * h;
        const float pw = w / 3.0f;
        const float ph = h / 3.0f;
        pButton->MakeDarker(mChildLevel);
        pButton->setFixedSize(pw, ph);
        pButton->move(cx + rw * std::cos(-angle) - 0.5f * pw, cy + rh * std::sin(-angle) - 0.5f * ph);
        pButton->setVisible(true);
    }
}
