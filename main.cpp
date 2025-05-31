#include <QApplication>
#include "server_gui.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ServerGUI window;
    window.show();
    return app.exec();
}
