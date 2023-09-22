
#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    // Initialize the Qt application
    QApplication app(argc, argv);
    
    // Create and show the main window
    MainWindow mainWindow;
    mainWindow.show();
    
    // Enter the application's event loop
    return app.exec();
}
