#include "ProjectMWidget.h"

#include <QOpenGLFunctions>
#include <QDir>
#include <QCoreApplication>

ProjectMWidget::ProjectMWidget(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_projectM(nullptr)
    , m_playlist(nullptr)
{
}

ProjectMWidget::~ProjectMWidget()
{
    if (m_playlist)
    {
        projectm_playlist_destroy(m_playlist);
    }
    if (m_projectM)
    {
        projectm_destroy(m_projectM);
    }
}

void ProjectMWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    m_projectM = projectm_create();
    if (!m_projectM)
    {
        // Handle error
        return;
    }

    projectm_set_window_size(m_projectM, width(), height());
    projectm_set_mesh_size(m_projectM, 1024, 768);

    projectm_set_fps(m_projectM, 30);

    const char* presetPath = "build/_deps/projectm-src/presets";
    const char* texturePath = "build/_deps/projectm-src/textures";
    
    m_playlist = projectm_playlist_create(m_projectM);
    projectm_playlist_add_path(m_playlist, presetPath, true, true);

    projectm_set_texture_search_paths(m_projectM, &texturePath, 1);

}

void ProjectMWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (m_projectM)
    {
        projectm_opengl_render_frame(m_projectM);
    }
}

void ProjectMWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    if (m_projectM)
    {
        projectm_set_window_size(m_projectM, w, h);
    }
}