#include "../include/openglwindow.h"

OpenGLWindow::OpenGLWindow(QWindow *parent) :
    QWindow(parent),
    _update_pending(false),
    _animating(false),
    _context(nullptr),
    _show_full_screen(false) {
    auto camera = std::make_shared<Camera>(DEFAULT_RATIO);
    main_cam_controller = std::make_shared<CameraController>(camera);
    setSurfaceType(QWindow::OpenGLSurface);
    resize(640, 480);
}

OpenGLWindow::~OpenGLWindow() { }

void OpenGLWindow::render() { }

void OpenGLWindow::initialize() { }

void OpenGLWindow::resizeGL(int w, int h) {
    if(h == 0)
        h = 1;
    if (_context)
        glViewport(0, 0, w, h);
    main_cam_controller->resetProj();
    main_cam_controller->setPersModel(DEFAULT_FOV, float(w) / float(h), 1, 1000);
}

void OpenGLWindow::setAnimating(bool animating) {
    _animating = animating;
    if(_animating)
        renderLater();
}

void OpenGLWindow::renderLater() {
    if (!_update_pending) {
        _update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void OpenGLWindow::renderNow() {
    if (!isExposed())
        return;

    auto needs_initialize = false;

    if (!_context) {
        _context = std::unique_ptr<QOpenGLContext>(new QOpenGLContext(this));
        _context->setFormat(requestedFormat());
        _context->create();
        needs_initialize = true;
    }

    _context->makeCurrent(this);
    if (needs_initialize) {
        initializeOpenGLFunctions();
        initialize();
        const auto retina_scale = devicePixelRatio();
        resizeGL(width()*retina_scale, height()*retina_scale);
    }
    render();

    _context->swapBuffers(this);

    if (_animating)
        renderLater();
}

bool OpenGLWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::UpdateRequest:
            _update_pending = false;
            renderNow();
            return true;
        default:
            return QWindow::event(event);
    }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
    if (isExposed())
        renderNow();
    QWindow::exposeEvent(event);
}

void OpenGLWindow::resizeEvent(QResizeEvent *event) {
    auto w = event->size().width();
    auto h = event->size().height();
    const auto retina_scale = devicePixelRatio();
    resizeGL(w * retina_scale, h * retina_scale);
    renderNow();
    QWindow::resizeEvent(event);
}

void OpenGLWindow::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_F1: {
            _show_full_screen = !_show_full_screen;
            if(_show_full_screen)
                showFullScreen();
            else
                showNormal();
            break;
        }
        case Qt::Key_Escape: {
            qApp->exit();
            break;
        }
    }
    QWindow::keyPressEvent(event);
}
