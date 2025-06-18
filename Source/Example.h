#pragma once

#include "HexagonalMenuWidget.h"

#include <QWidget>

namespace QtHexagonalMenu
{
    class Example : public QWidget
    {
      public:
        explicit Example(QWidget* pParent = nullptr);

        void mouseMoveEvent(QMouseEvent* pEvent) override;
        void mousePressEvent(QMouseEvent* pEvent) override;
        void mouseReleaseEvent(QMouseEvent* pEvent) override;

      private:
        HexagonalMenuWidget* mHexagonalMenuWidget;
        HexagonalMenuWidget* mHexagonalMenuWidgetChild;
    };
}