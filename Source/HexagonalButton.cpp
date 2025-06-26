#include "HexagonalButton.h"

#include "HexagonalMenuWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

HexagonalButton::HexagonalButton(QWidget* pParent)
    : QWidget(pParent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void HexagonalButton::paintEvent(QPaintEvent* pEvent)
{
    OnPaint(pEvent);
}

void HexagonalButton::resizeEvent(QResizeEvent* pEvent)
{
    OnResize(pEvent);
}

bool HexagonalButton::OnMouseReleased(const QPointF& point)
{
    if (!isVisible())
    {
        return false;
    }

    mPressed = false;
    update();

    return ContainsPoint(point);
}

bool HexagonalButton::OnMousePressed(const QPointF& point)
{
    if (!isVisible())
    {
        return false;
    }

    mPressed = ContainsPoint(point);
    update();

    if (mPressed)
    {
        emit Clicked();
    }

    return mPressed;
}

bool HexagonalButton::OnMouseMoved(const QPointF& point)
{
    if (!isVisible())
    {
        return false;
    }

    mHovered = ContainsPoint(point);
    update();

    return mHovered;
}

void HexagonalButton::SetLabel(const QString& label)
{
    mLabel = label;
}

void HexagonalButton::MakeDarker(int factor)
{
    mDarkFactor = factor;
}

void HexagonalButton::OnPaint(QPaintEvent* pEvent)
{
    const auto w = width();
    const auto h = height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QColor fillColor = mHovered ? mFillColor.darker() : mFillColor;

    fillColor.setAlpha(128 + 64 * mDarkFactor);
    painter.setBrush(fillColor);
    painter.setPen(QPen(mContourColor, 2));
    painter.drawPolygon(mPolygon);

    painter.setPen(mTextColor);
    QFont font("Arial", 14, QFont::Bold);
    painter.setFont(font);
    painter.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, mLabel);
}

void HexagonalButton::OnResize(QResizeEvent* pEvent)
{
    const float w = pEvent->size().width();
    const float h = pEvent->size().height();
    const float x = 0.5f * w;
    const float y = 0.5f * h;
    const float pw = SCALING * w;
    const float ph = std::sqrt(3) / 2.0f * pw;
    mCenter = QPointF(x, y);

    const auto v0 = QPointF(x + 0.50f * pw, y);
    const auto v1 = QPointF(x + 0.25f * pw, y - 0.5 * ph);
    const auto v2 = QPointF(x - 0.25f * pw, y - 0.5 * ph);
    const auto v3 = QPointF(x - 0.50f * pw, y);
    const auto v4 = QPointF(x - 0.25f * pw, y + 0.5 * ph);
    const auto v5 = QPointF(x + 0.25f * pw, y + 0.5 * ph);

    mPolygon.clear();
    mPolygon.append({ v0, v1, v2, v3, v4, v5 });
}

bool HexagonalButton::ContainsPoint(const QPointF& point)
{
    return mPolygon.containsPoint(mapFromParent(point), Qt::FillRule::WindingFill);
}
