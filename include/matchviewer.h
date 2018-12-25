#ifndef MATCHVIEWER_HHH
#define MATCHVIEWER_HHH

#include "openglwindow.h"
#include <QOpenGLShaderProgram>

class MatchViewer : public OpenGLWindow
{
    Q_OBJECT
public:
    explicit MatchViewer(QWindow *parent = 0);
    ~MatchViewer();
protected:
    void initialize();
    void render();
    void keyPressEvent(QKeyEvent *event);
private:
    void loadShader();
private:
    void initGeometry();
private:
    QOpenGLShaderProgram *m_program;
    GLuint m_posAttr;
    GLuint m_colorAttr;
    //GLuint m_texCoordAttr;
    //GLuint m_normalAttr;

    GLuint m_vboIds[2];
    //GLuint m_texture;
    GLfloat m_xrot;
    GLfloat m_yrot;
    GLfloat m_zrot;
};

#endif // MATCHVIEWER_HHH
