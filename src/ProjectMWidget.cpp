#include "ProjectMWidget.h"
#include <QOpenGLFunctions>

ProjectMWidget::ProjectMWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

ProjectMWidget::~ProjectMWidget()
{
}

void ProjectMWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void ProjectMWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void ProjectMWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}
