#include "MainWindow.h"
#include "ProjectMWidget.h"
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
    m_projectMWidget = new ProjectMWidget(this);
    setCentralWidget(m_projectMWidget);


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