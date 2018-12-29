#ifndef MATCHVIEWER_HHH
#define MATCHVIEWER_HHH

#include "openglwindow.h"
#include <QOpenGLShaderProgram>
#include <memory>
#include "noncopyable.h"

class MatchViewer : public OpenGLWindow {
public:
    explicit MatchViewer(QWindow *parent = nullptr);
    virtual ~MatchViewer();
protected:
    void initialize();
    void render();
    void keyPressEvent(QKeyEvent *event);
private:
    void loadShader();
private:
    void initGeometry();
private:
    std::unique_ptr<QOpenGLShaderProgram> _program;
    GLuint _pos_attr;
    GLuint _color_attr;

    QMatrix4x4 _model;
    GLuint _vbo_ids[2];

};

#endif // MATCHVIEWER_HHH
