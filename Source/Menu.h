#pragma once

#include "Submenu.h"

#include <QObject>

class Menu : public QObject
{
    Q_OBJECT
  public:
    explicit Menu(QWidget* pParent);

    void Show(int x, int y, int animationStartingIndex);
    void Hide();

    bool OnMouseReleased(const QPointF& point);
    bool OnMousePressed(const QPointF& point);
    bool OnMouseMoved(const QPointF& point);

  private:
    QWidget* mParent;
    Submenu* mMainMenu;
};