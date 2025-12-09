#ifndef PROJECTMWIDGET_H
#define PROJECTMWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class ProjectMWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    ProjectMWidget(QWidget *parent = nullptr);
    ~ProjectMWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;
};

#endif // PROJECTMWIDGET_H