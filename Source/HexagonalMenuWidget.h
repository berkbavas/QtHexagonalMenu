#pragma once

#include "HexagonalButton.h"

#include <map>

#include <QTimer>
#include <QWidget>

namespace QtHexagonalMenu
{
    class HexagonalMenuWidget : public QWidget
    {
        Q_OBJECT
      public:
        explicit HexagonalMenuWidget(QWidget* pParent);

        void Show(int x, int y, int animationStartingIndex);
        void Hide();

        bool OnMouseReleased(const QPointF& position);
        bool OnMousePressed(const QPointF& position);
        bool OnMouseMoved(const QPointF& position);

        void AddButton(int index, const QString& name);

        QPointF GetCenter() const;

      signals:
        void ButtonClicked(int index);

      private:
        void Update();

        QWidget* mParent{ nullptr };
        std::map<int, HexagonalButton*> mButtons;
        QTimer mTimer;
        int mAnimationStartingIndex;
        float mAnimationVariable{ 0.0f }; // [0,1]
    };
}