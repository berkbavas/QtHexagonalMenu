#include "HexagonalButton.h"

#include "HexagonalMenuWidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

QtHexagonalMenu::HexagonalButton::HexagonalButton(QWidget* pParent)
    : QWidget(pParent)
{
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

void QtHexagonalMenu::HexagonalButton::paintEvent(QPaintEvent* pEvent)
{
    OnPaint(pEvent);
}

void QtHexagonalMenu::HexagonalButton::resizeEvent(QResizeEvent* pEvent)
{
    OnResize(pEvent);
}

bool QtHexagonalMenu::HexagonalButton::OnMouseReleased(const QPointF& position)
{
    mPressed = false;
    update();

    return ContainsPointFromParent(position);
}

bool QtHexagonalMenu::HexagonalButton::OnMousePressed(const QPointF& position)
{
    mPressed = ContainsPointFromParent(position);
    update();

    if (mPressed)
    {
        emit MousePressed();
    }

    return mPressed;
}

bool QtHexagonalMenu::HexagonalButton::OnMouseMoved(const QPointF& position)
{
    mHovered = ContainsPointFromParent(position);
    update();

    return mHovered;
}

void QtHexagonalMenu::HexagonalButton::SetLabel(const QString& label)
{
    mLabel = label;
}

void QtHexagonalMenu::HexagonalButton::OnPaint(QPaintEvent* pEvent)
{
    const auto& w = width();
    const auto& h = height();

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QLinearGradient gradient(0.5f * w, 0, 0.5f * w, h);

    if (mHovered)
    {
        gradient.setColorAt(0.0, mFillColor0.darker());
        gradient.setColorAt(1.0, mFillColor1.darker());
    }
    else
    {
        gradient.setColorAt(0.0, mFillColor0);
        gradient.setColorAt(1.0, mFillColor1);
    }

    painter.setBrush(gradient);
    painter.setPen(QPen(mContourColor, 1));
    painter.drawPolygon(mPolygon);

    painter.setPen(mTextColor);
    QFont font("Calibri", 14, QFont::Bold);
    painter.setFont(font);
    painter.drawText(QRectF(0, 0, width(), height()), Qt::AlignCenter, mLabel);
}

void QtHexagonalMenu::HexagonalButton::OnResize(QResizeEvent* pEvent)
{
    float w = pEvent->size().width();
    float h = pEvent->size().height();
    float x = 0.5f * w;
    float y = 0.5f * h;
    float pw = SCALING * w;
    float ph = std::sqrt(3) / 2.0f * pw;
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

bool QtHexagonalMenu::HexagonalButton::ContainsPointFromParent(const QPointF& point)
{
    return mPolygon.containsPoint(mapFromParent(point), Qt::FillRule::WindingFill);
}
