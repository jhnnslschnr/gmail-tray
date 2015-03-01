#include "trayicon.h"
#include "control.h"
#include <QApplication>
#include <QSettings>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("JTL");
    QCoreApplication::setApplicationName("gmailtray");
    app.setQuitOnLastWindowClosed(false);

    Control control;

    return app.exec();
}
