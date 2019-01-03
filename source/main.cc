#include <QApplication>
#include <QSurfaceFormat>
#include "../include/matchviewer.h"

#define DEBUG

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);

    MatchViewer window;
    window.setFormat(format);
    window.show();
    window.setAnimating(true);
    return app.exec();
}
