#ifndef PROJECTMWIDGET_H
#define PROJECTMWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include <QElapsedTimer>
#include <QAudioSource>
#include <QMediaDevices>

#include <projectM-4/projectM.h>

class ProjectMWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    explicit ProjectMWidget(QWidget *parent = nullptr);
    ~ProjectMWidget() override;

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int w, int h) override;

    // Support dragging .milk files onto the window
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void processAudio();

private:
    void initAudio();
    void loadTextureResources();

    projectm_handle m_projectM = nullptr;
    QTimer *m_renderTimer;
    
    // Audio capture
    QAudioSource *m_audioSource = nullptr;
    QIODevice *m_audioDevice = nullptr;
    QAudioFormat m_audioFormat;
};

#endif // PROJECTMWIDGET_H
