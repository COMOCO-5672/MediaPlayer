#ifndef MEDIAPLAY_OPENGLRENDER_H__
#define MEDIAPLAY_OPENGLRENDER_H__

#include "QOpenGLBuffer"
#include "QOpenGLFunctions"
#include "QOpenGLShaderProgram"
#include "QOpenGLWidget"
#include "qtimer.h"
#include "mutex"

class OpenGLRenderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit OpenGLRenderWidget(QWidget *parent = nullptr);
    ~OpenGLRenderWidget();

    void render(uchar *py, uchar *puv, int w, int h);

signals:
    void widget_exit();

public slots:
    void timer_render();

protected:
    void initializeGL() override;
    void paintGL() override;
    void closeEvent(QCloseEvent *event) override;

public:
    std::mutex m_mtx_;

private:
    QTimer *m_timer;
    QOpenGLShaderProgram program;
    GLuint idY, idUV;
    QOpenGLBuffer vbo;
};

#endif