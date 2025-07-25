#include "HexagonalMenuWidget.h"

#include <cassert>

HexagonalMenuWidget::HexagonalMenuWidget(QWidget* pParent, int index)
    : QWidget(pParent)
    , mParent(pParent)
{
    mAnimationStartingIndex = (index + 3) % 6;
    setAttribute(Qt::WA_TransparentForMouseEvents);
    connect(&mTimer, &QTimer::timeout, this, &HexagonalMenuWidget::Update);
}

void HexagonalMenuWidget::Show(int x, int y)
{
    float w = width();
    float h = height();
    float cx = 0.5f * w;
    float cy = 0.5f * h;

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

void HexagonalMenuWidget::SetSelectedIndex(int index)
{
    mSelectedIndex = index;

    for (const auto& [index, pButton] : mButtons)
    {
        pButton->SetSelected(index == mSelectedIndex);
    }
}

void HexagonalMenuWidget::Update()
{
    mAnimationVariable += 0.035f;

    if (mAnimationVariable > 1.0f)
    {
        mAnimationVariable = 1.0f;
        mTimer.stop();
    }

    const float w = width();
    const float h = height();
    const float cx = 0.5f * w;
    const float cy = 0.5f * h;

    for (const auto& [index, pButton] : mButtons)
    {
        const float angle = M_PI / 6.0f + (index - mAnimationStartingIndex) * M_PI / 3.0f + mAnimationStartingIndex * M_PI / 3.0f;
        const float rw = mAnimationVariable * 0.3f * w;
        const float rh = mAnimationVariable * 0.3f * h;
        const float pw = (w / 3.0f);
        const float ph = (h / 3.0f);
        float x = cx + rw * std::cos(-angle) - 0.5f * pw;
        float y = cy + rh * std::sin(-angle) - 0.5f * ph;

        if (mChildLevel == 0) // Main menu
        {
        }
        else // Child menu
        {
            if (index == mAnimationStartingIndex)
            {
                x = cx + (1 - mAnimationVariable) * rw * std::cos(-angle) - 0.5f * pw;
                y = cy + (1 - mAnimationVariable) * rh * std::sin(-angle) - 0.5f * ph;
            }
        }

        pButton->SetSelected(index == mSelectedIndex);
        pButton->MakeDarker(mChildLevel);
        pButton->setFixedSize(pw, ph);
        pButton->move(x, y);
        pButton->setVisible(true);
    }
}
