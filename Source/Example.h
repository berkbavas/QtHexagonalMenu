#pragma once

#include "HexagonalMenuWidget.h"

#include <QWidget>

namespace QtHexagonalMenu
{
    class Example : public QWidget
    {
      public:
        explicit Example(QWidget* pParent = nullptr);

        void mousePressEvent(QMouseEvent* pEvent) override;

      private:
        HexagonalMenuWidget* mHexagonalMenuWidget;
        HexagonalMenuWidget* mHexagonalMenuWidgetChild;
    };
}