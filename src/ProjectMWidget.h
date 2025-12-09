#ifndef PROJECTMWIDGET_H
#define PROJECTMWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include <projectM-4/projectM.h>
#include <projectM-4/playlist.h>

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

private:
    projectm_handle m_projectM;
    projectm_playlist_handle m_playlist;
};

#endif // PROJECTMWIDGET_H
