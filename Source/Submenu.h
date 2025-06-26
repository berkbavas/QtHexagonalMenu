#pragma once

#include "HexagonalMenuWidget.h"

#include <QMap>
#include <QObject>

class Submenu;

class Submenu : public QObject
{
    Q_OBJECT

  public:
    explicit Submenu(QWidget* pParent);

    void Show(int x, int y, int animationStartingIndex);
    void Hide();

    bool OnMouseReleased(const QPointF& point);
    bool OnMousePressed(const QPointF& point);
    bool OnMouseMoved(const QPointF& point);

    void AddButton(int index, const QString& label);
    void AddSubmenu(int index, Submenu* pSubmenu);

    void SetChildLevel(int level);

  signals:
    void ButtonClicked(int index);
    void RequestHide();

  private:
    void ShowChild(int index);
    void HandleButtonClick(int index);

    QWidget* mParent;
    HexagonalMenuWidget* mHexagonalMenuWidget;
    QMap<int, Submenu*> mSubmenus;
};