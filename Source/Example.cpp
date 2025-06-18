#include "Example.h"

#include <QMouseEvent>
#include <QStyle>

QtHexagonalMenu::Example::Example(QWidget* pParent)
    : QWidget(pParent)
{
    mMenu = new Menu(this, "");

    auto* pTest0 = new Menu(this, "Test 0");
    auto* pTest1 = new Menu(this, "Test 1");
    auto* pTest2 = new Menu(this, "Test 2");
    auto* pTest3 = new Menu(this, "Test 3");
    auto* pTest4 = new Menu(this, "Test 4");
    auto* pTest5 = new Menu(this, "Test 5");

    auto* pTest00 = new Menu(this, "Test 00");
    auto* pTest01 = new Menu(this, "Test 01");
    auto* pTest02 = new Menu(this, "Test 02");
    auto* pTest03 = new Menu(this, "Test 03");
    auto* pTest04 = new Menu(this, "Test 04");
    auto* pTest05 = new Menu(this, "Test 05");

    auto* pTest10 = new Menu(this, "Test 10");
    auto* pTest11 = new Menu(this, "Test 11");
    auto* pTest12 = new Menu(this, "Test 12");
    auto* pTest13 = new Menu(this, "Test 13");
    auto* pTest14 = new Menu(this, "Test 14");
    auto* pTest15 = new Menu(this, "Test 15");

    auto* pTest20 = new Menu(this, "Test 20");
    auto* pTest21 = new Menu(this, "Test 21");
    auto* pTest22 = new Menu(this, "Test 22");
    auto* pTest23 = new Menu(this, "Test 23");
    auto* pTest24 = new Menu(this, "Test 24");
    auto* pTest25 = new Menu(this, "Test 25");

    auto* pTest30 = new Menu(this, "Test 30");
    auto* pTest31 = new Menu(this, "Test 31");
    auto* pTest32 = new Menu(this, "Test 32");
    auto* pTest33 = new Menu(this, "Test 33");
    auto* pTest34 = new Menu(this, "Test 34");
    auto* pTest35 = new Menu(this, "Test 35");

    auto* pTest40 = new Menu(this, "Test 40");
    auto* pTest41 = new Menu(this, "Test 41");
    auto* pTest42 = new Menu(this, "Test 42");
    auto* pTest43 = new Menu(this, "Test 43");
    auto* pTest44 = new Menu(this, "Test 44");
    auto* pTest45 = new Menu(this, "Test 45");

    auto* pTest50 = new Menu(this, "Test 50");
    auto* pTest51 = new Menu(this, "Test 51");
    auto* pTest52 = new Menu(this, "Test 52");
    auto* pTest53 = new Menu(this, "Test 53");
    auto* pTest54 = new Menu(this, "Test 54");
    auto* pTest55 = new Menu(this, "Test 55");

    auto* pTest050 = new Menu(this, "Test 050");
    auto* pTest051 = new Menu(this, "Test 051");
    auto* pTest052 = new Menu(this, "Test 052");
    auto* pTest053 = new Menu(this, "Test 053");

    auto* pTest040 = new Menu(this, "Test 040");
    auto* pTest041 = new Menu(this, "Test 041");
    auto* pTest042 = new Menu(this, "Test 042");
    auto* pTest043 = new Menu(this, "Test 043");

    pTest04->AddChildren({ { 0, pTest040 },
                           { 1, pTest041 },
                           { 2, pTest042 },
                           { 3, pTest043 } });

    pTest05->AddChildren({ { 0, pTest050 },
                           { 1, pTest051 },
                           { 2, pTest052 },
                           { 3, pTest053 } });

    pTest0->AddChildren({ { 1, pTest01 },
                          { 2, pTest02 },
                          { 3, pTest03 },
                          { 4, pTest04 },
                          { 5, pTest05 } });

    pTest1->AddChildren({ { 0, pTest10 },
                          { 1, pTest11 },
                          { 2, pTest12 },
                          { 3, pTest13 },
                          { 4, pTest14 },
                          { 5, pTest15 } });

    pTest2->AddChildren({ { 0, pTest20 },
                          { 1, pTest21 },
                          { 2, pTest22 },
                          { 3, pTest23 },
                          { 4, pTest24 },
                          { 5, pTest25 } });

    pTest3->AddChildren({ { 0, pTest30 },
                          { 1, pTest31 },
                          { 2, pTest32 },
                          { 3, pTest33 },
                          { 4, pTest34 },
                          { 5, pTest35 } });

    pTest4->AddChildren({ { 0, pTest40 },
                          { 1, pTest41 },
                          { 2, pTest42 },
                          { 3, pTest43 },
                          { 4, pTest44 },
                          { 5, pTest45 } });

    pTest5->AddChildren({ { 0, pTest50 },
                          { 1, pTest51 },
                          { 2, pTest52 },
                          { 3, pTest53 },
                          { 4, pTest54 },
                          { 5, pTest55 } });

    mMenu->AddChildren({ { 0, pTest0 },
                         { 1, pTest1 },
                         { 2, pTest2 },
                         { 3, pTest3 },
                         { 4, pTest4 },
                         { 5, pTest5 } });

    setMouseTracking(true);
}

void QtHexagonalMenu::Example::mouseMoveEvent(QMouseEvent* pEvent)
{
    mMenu->OnMouseMoved(pEvent->position());
}

void QtHexagonalMenu::Example::mousePressEvent(QMouseEvent* pEvent)
{
    bool consumed = mMenu->OnMousePressed(pEvent->position());

    if (!consumed)
    {
        mMenu->Hide();
        mMenu->GetWidget()->Show(pEvent->position().x(), pEvent->position().y(), 0);
    }
}

void QtHexagonalMenu::Example::mouseReleaseEvent(QMouseEvent* pEvent)
{
    mMenu->OnMouseReleased(pEvent->position());
}
