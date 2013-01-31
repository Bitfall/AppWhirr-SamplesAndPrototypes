#include "mainwindow.h"

#include "MagnetLayoutSystem/magnetmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    _magnetManager = new MagnetManager(this);
}

MainWindow::~MainWindow()
{

}
