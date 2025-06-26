#include "Example.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Example* pExample = new Example;
    pExample->showNormal();

    return app.exec();
}
