#include "ProjectMWidget.h"

// Includes for projectM C API
#include <projectM-4/projectM.h>

#include <QDebug>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QDir>

ProjectMWidget::ProjectMWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    // Enable Drag and Drop for .milk files
    setAcceptDrops(true);

    // Timer to trigger continuous rendering (60 FPS target)
    m_renderTimer = new QTimer(this);
    connect(m_renderTimer, &QTimer::timeout, this, QOverload<>::of(&ProjectMWidget::update));
    m_renderTimer->start(16);

    initAudio();
}

ProjectMWidget::~ProjectMWidget()
{
    if (m_projectM) {
        projectm_destroy(m_projectM);
    }
}

void ProjectMWidget::initAudio()
{
    // Setup Audio Format for Capture
    m_audioFormat.setSampleRate(44100);
    m_audioFormat.setChannelCount(2);
    m_audioFormat.setSampleFormat(QAudioFormat::Float); 

    QAudioDevice defaultDevice = QMediaDevices::defaultAudioInput();
    if (defaultDevice.isNull()) {
        qWarning() << "No audio input device found!";
        return;
    }

    if (!defaultDevice.isFormatSupported(m_audioFormat)) {
        qWarning() << "Default format not supported, trying nearest.";
        m_audioFormat = defaultDevice.preferredFormat();
    }

    m_audioSource = new QAudioSource(defaultDevice, m_audioFormat, this);
    
    // Buffer size to keep latency low
    m_audioSource->setBufferSize(4096); 

    // Start recording from the mic/system loopback
    m_audioDevice = m_audioSource->start();
    
    // When data is available, process it
    connect(m_audioDevice, &QIODevice::readyRead, this, &ProjectMWidget::processAudio);
}

void ProjectMWidget::processAudio()
{
    if (!m_audioDevice || !m_projectM) return;

    QByteArray data = m_audioDevice->readAll();
    if (data.isEmpty()) return;

    // projectM expects PCM data.
    // If our format is Float, we can pass it directly.
    if (m_audioFormat.sampleFormat() == QAudioFormat::Float) {
        const float* samples = reinterpret_cast<const float*>(data.constData());
        int numSamples = data.size() / sizeof(float);

        // projectM 4 API: add float PCM data
        // The last argument is the number of channels.
        projectm_pcm_add_float(m_projectM, samples, numSamples / m_audioFormat.channelCount(),
                                   (projectm_channels)m_audioFormat.channelCount());
    }
    // Other formats would need conversion to float here.
}

void ProjectMWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Create projectM instance
    m_projectM = projectm_create();

    if (!m_projectM) {
        qCritical() << "Failed to create projectM instance!";
        return;
    }

    loadTextureResources();

    // Load a default preset to ensure something is displayed
    projectm_load_preset_file(m_projectM, "/home/nsomnia/Documents/GoogleAntigravity/vibevid_gemini3/vibevidz/build/_deps/projectm-src/presets/tests/001-line.milk", true);
}

void ProjectMWidget::loadTextureResources()
{
    // Set resource paths so projectM can find fonts/textures
    // We use the definition passed from CMake
#ifdef PROJECTM_RESOURCES_PATH
    const char* texturePaths[] = { PROJECTM_RESOURCES_PATH };
    projectm_set_texture_search_paths(m_projectM, texturePaths, 1);
#endif
}

void ProjectMWidget::resizeGL(int w, int h)
{
    if (m_projectM) {
        projectm_set_window_size(m_projectM, w, h);
    }
}

void ProjectMWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_projectM) {
        return;
    }

    // Perform the rendering
    projectm_opengl_render_frame(m_projectM);
}

void ProjectMWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void ProjectMWidget::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) return;

    QString fileName = urls.first().toLocalFile();
    if (fileName.endsWith(".milk", Qt::CaseInsensitive)) {
        qDebug() << "Loading preset:" << fileName;
        if (m_projectM) {
            projectm_load_preset_file(m_projectM, fileName.toUtf8().constData(), true);
        }
    }
}
