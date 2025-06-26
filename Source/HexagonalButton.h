#pragma once

#include <QPolygon>
#include <QWidget>

class HexagonalButton : public QWidget
{
    Q_OBJECT

  public:
    explicit HexagonalButton(QWidget* pParent);

    void paintEvent(QPaintEvent* pEvent) override;
    void resizeEvent(QResizeEvent* pEvent) override;

    bool OnMouseReleased(const QPointF& point);
    bool OnMousePressed(const QPointF& point);
    bool OnMouseMoved(const QPointF& point);

    void SetLabel(const QString& label);
    void MakeDarker(int factor);

  signals:
    void Clicked();

  private:
    void OnPaint(QPaintEvent* pEvent);
    void OnResize(QResizeEvent* pEvent);
    bool ContainsPoint(const QPointF& point);

    QString mLabel;
    QPointF mCenter;
    QPolygonF mPolygon;
    QColor mTextColor{ 255, 255, 255 };
    QColor mContourColor{ 32, 32, 32 };
    QColor mFillColor{ 64, 64, 64 };

    bool mHovered{ false };
    bool mPressed{ false };
    int mDarkFactor{ 0 };

    static constexpr float SCALING{ 0.9 };
};
