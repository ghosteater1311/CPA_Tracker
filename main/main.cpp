#include <QApplication>
#include "UI.h"

int main(int argc, char *argv[])
{
    // Create Window
    QApplication app(argc, argv);
    UI window;

    // Define Length and Width of the Window
    int width = 780;
    int length = 500;
    window.resize(width, length);

    // Set Window title
    window.setWindowTitle("CPA Tracker");

    // Show Window
    window.show();
    return app.exec();
}