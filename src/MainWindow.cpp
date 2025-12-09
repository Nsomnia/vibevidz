#include "MainWindow.h"
#include <QDockWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set up the main window
    setWindowTitle("Vibevidz");
    resize(1280, 720);

    // Central widget for projectM visualization
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    centralWidget->setStyleSheet("background-color: black;");


    // Dock widget for controls
    auto *dock = new QDockWidget("Controls", this);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    auto *controlsWidget = new QWidget();
    dock->setWidget(controlsWidget);

    auto *layout = new QVBoxLayout();
    controlsWidget->setLayout(layout);

    // Placeholder for controls
    auto *playlist = new QListWidget();
    layout->addWidget(playlist);
}

MainWindow::~MainWindow()
{
}
