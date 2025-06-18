#pragma once

#include "HexagonalMenuWidget.h"

#include <QObject>

namespace QtHexagonalMenu
{
    class Menu;

    class Menu : QObject
    {
        Q_OBJECT
      public:
        explicit Menu(QWidget* pParent, const QString& name);

        bool OnMouseReleased(const QPointF& position);
        bool OnMousePressed(const QPointF& position);
        bool OnMouseMoved(const QPointF& position);

        void Hide();
        void AddChildren(const std::map<int, Menu*>& children);
        const QString& GetName() const;

        HexagonalMenuWidget* GetWidget() const;

      private slots:
        void ShowChild(int index);

      private:
        QWidget* mParent;
        QString mName;
        HexagonalMenuWidget* mHexagonalMenuWidget{ nullptr };
        std::map<int, Menu*> mChildren;
    };
}