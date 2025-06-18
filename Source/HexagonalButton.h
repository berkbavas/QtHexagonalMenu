#pragma once

#include <QMouseEvent>
#include <QPolygon>
#include <QWidget>

namespace QtHexagonalMenu
{
    class HexagonalButton : public QWidget
    {
        Q_OBJECT

      public:
        explicit HexagonalButton(QWidget* pParent);

        void paintEvent(QPaintEvent* pEvent) override;
        void resizeEvent(QResizeEvent* pEvent) override;

        bool OnMouseReleased(const QPointF& position);
        bool OnMousePressed(const QPointF& position);
        bool OnMouseMoved(const QPointF& position);

        void SetLabel(const QString& label);

      signals:
        void MousePressed();

      private:
        void OnPaint(QPaintEvent* pEvent);
        void OnResize(QResizeEvent* pEvent);

        bool ContainsPointFromParent(const QPointF& point);

        QString mLabel;
        QPointF mCenter;
        QPolygonF mPolygon;
        QColor mTextColor{ 255, 255, 255 };
        QColor mContourColor{ 9, 45, 71 };
        QColor mFillColor0{ 12, 97, 175 };
        QColor mFillColor1{ 9, 65, 97 };

        bool mHovered{ false };
        bool mPressed{ false };

        static constexpr float SCALING{ 0.9 };
    };
}