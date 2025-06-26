#include "Menu.h"

Menu::Menu(QWidget* pParent)
    : QObject(pParent)
    , mParent(pParent)
{
    mMainMenu = new Submenu(mParent, 3);
    mMainMenu->AddButton(0, "Test 0");
    mMainMenu->AddButton(1, "Test 1");
    mMainMenu->AddButton(2, "Test 2");
    mMainMenu->AddButton(3, "Test 3");
    mMainMenu->AddButton(4, "Test 4");
    mMainMenu->AddButton(5, "Test 5");

    Submenu* pSubmenu0 = new Submenu(mParent, 0);
    pSubmenu0->AddButton(0, "Test 00");
    pSubmenu0->AddButton(1, "Test 01");
    pSubmenu0->AddButton(2, "Test 02");
    pSubmenu0->AddButton(4, "Test 04");
    pSubmenu0->AddButton(5, "Test 05");

    Submenu* pSubmenu05 = new Submenu(mParent, 5);
    pSubmenu05->AddButton(0, "Test 050");
    pSubmenu05->AddButton(1, "Test 051");
    pSubmenu05->AddButton(3, "Test 053");
    pSubmenu05->AddButton(4, "Test 054");
    pSubmenu05->AddButton(5, "Test 055");

    pSubmenu0->AddSubmenu(5, pSubmenu05);

    Submenu* pSubmenu1 = new Submenu(mParent, 1);
    pSubmenu1->AddButton(0, "Test 10");
    pSubmenu1->AddButton(1, "Test 11");
    pSubmenu1->AddButton(2, "Test 12");
    pSubmenu1->AddButton(3, "Test 13");
    pSubmenu1->AddButton(5, "Test 15");

    Submenu* pSubmenu2 = new Submenu(mParent, 2);
    pSubmenu2->AddButton(0, "Test 20");
    pSubmenu2->AddButton(1, "Test 21");
    pSubmenu2->AddButton(2, "Test 22");
    pSubmenu2->AddButton(3, "Test 23");
    pSubmenu2->AddButton(4, "Test 24");

    Submenu* pSubmenu3 = new Submenu(mParent, 3);
    pSubmenu3->AddButton(1, "Test 31");
    pSubmenu3->AddButton(2, "Test 32");
    pSubmenu3->AddButton(3, "Test 33");
    pSubmenu3->AddButton(4, "Test 34");
    pSubmenu3->AddButton(5, "Test 35");

    mMainMenu->AddSubmenu(0, pSubmenu0);
    mMainMenu->AddSubmenu(1, pSubmenu1);
    mMainMenu->AddSubmenu(2, pSubmenu2);
    mMainMenu->AddSubmenu(3, pSubmenu3);

    connect(mMainMenu, &Submenu::RequestHide, this, &Menu::Hide);

    mMainMenu->SetChildLevel(0);
}

void Menu::Show(int x, int y)
{
    mMainMenu->Show(x, y);
}

void Menu::Hide()
{
    mMainMenu->Hide();
}

bool Menu::OnMouseReleased(const QPointF& point)
{
    return mMainMenu->OnMouseReleased(point);
}

bool Menu::OnMousePressed(const QPointF& point)
{
    return mMainMenu->OnMousePressed(point);
}

bool Menu::OnMouseMoved(const QPointF& point)
{
    return mMainMenu->OnMouseMoved(point);
}