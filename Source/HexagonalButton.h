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

        bool OnMouseReleased(QMouseEvent* pEvent);
        bool OnMousePressed(QMouseEvent* pEvent);
        bool OnMouseMoved(QMouseEvent* pEvent);

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
        QColor mContourColor{ 0, 0, 0 };
        QColor mFillColor{ 255, 0, 0 };

        bool mHovered{ false };
        bool mPressed{ false };

        static constexpr float SCALING{ 0.9 };
    };
}