#include "Example.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QtHexagonalMenu::Example* pExample = new QtHexagonalMenu::Example;
    pExample->showNormal();

    return app.exec();
}
