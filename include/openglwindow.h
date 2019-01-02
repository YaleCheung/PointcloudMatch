#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QWindow>
#include <QOpenGLFunctions>
#include <QCoreApplication>
#include <QEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QMatrix4x4>
#include "../include/camera.h"
#include <memory>
#include "noncopyable.h"
#include "cameracontroller.h"

class OpenGLWindow : public QWindow, NonCopyable, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit OpenGLWindow(QWindow *parent = nullptr);
    virtual ~OpenGLWindow();

    void setAnimating(bool animating);
public slots:
    void renderLater();

    void renderNow();

protected:
    bool event(QEvent *event);

    void exposeEvent(QExposeEvent* event);

    void resizeEvent(QResizeEvent* event);

    void keyPressEvent(QKeyEvent* event);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event);

    virtual void render();

    virtual void initialize();

    virtual void resizeGL(int w, int h);
    std::shared_ptr<CameraController> main_cam_controller;

private:
    bool _update_pending;
    bool _animating;
    std::unique_ptr<QOpenGLContext> _context;
    bool _show_full_screen;
};

#endif // OPENGLWINDOW_H
