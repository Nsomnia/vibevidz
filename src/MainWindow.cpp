#include "MainWindow.h"
#include "ProjectMWidget.h"
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("VibeVidz - projectM 4.1 Visualizer");

    // Create a central widget to hold layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Create layout
    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->setContentsMargins(0, 0, 0, 0);

    // Create and add the visualizer
    m_visualizer = new ProjectMWidget(this);
    layout->addWidget(m_visualizer);
}

MainWindow::~MainWindow()
{
}
