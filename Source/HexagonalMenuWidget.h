#pragma once

#include "HexagonalButton.h"

#include <map>

#include <QTimer>
#include <QWidget>

class HexagonalMenuWidget : public QWidget
{
    Q_OBJECT
  public:
    explicit HexagonalMenuWidget(QWidget* pParent, int index);

    void Show(int x, int y);
    void Hide();

    bool OnMouseReleased(const QPointF& point);
    bool OnMousePressed(const QPointF& point);
    bool OnMouseMoved(const QPointF& point);

    void AddButton(int index, const QString& name);
    QPointF GetCenter() const;

    void SetChildLevel(int level);

  signals:
    void ButtonClicked(int index);

  private:
    void Update();

    QWidget* mParent{ nullptr };
    std::map<int, HexagonalButton*> mButtons;
    QTimer mTimer;
    int mAnimationStartingIndex;
    float mAnimationVariable{ 0.0f }; // [0,1]
    int mChildLevel{ 0 };
};
