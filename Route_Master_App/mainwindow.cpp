#include "mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Route Master");
    setMinimumSize(800, 600);

    routeMaster = new RouteMaster(this);
    setCentralWidget(routeMaster);
}

MainWindow::~MainWindow()
{
}
