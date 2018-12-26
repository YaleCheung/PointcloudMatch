#include "../include/matchviewer.h"
#include <iostream>


struct VertexData {
    QVector3D position;
    QVector3D color;
};


MatchViewer::MatchViewer(QWindow *parent) :
    OpenGLWindow(parent),
    m_program(NULL),
    m_xrot(0.0f),
    m_yrot(0.0f) { }

MatchViewer::~MatchViewer() {
    glDeleteBuffers(2, &m_vboIds[0]);
}

void MatchViewer::initialize() {
    initGeometry();
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClearDepthf(1.0);
    //glDepthFunc(GL_LEQUAL);
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_POINT_SMOOTH);
    glPointSize(10.0f);
    //glEnable(GL_BLEND);
    //glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    loadShader();

}

void MatchViewer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);
    m_program->bind();

    m_model.setToIdentity();
    //m_model.translate(0.0f, 0.0f, -7.0f);
    m_model.rotate(m_xrot, 1.0f, 0.0f, 0.0f);
    m_view.lookAt(QVector3D(0.0f, -5.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f));
    QMatrix4x4 mvp = m_projection * m_view * m_model;
    //QMatrix4x4 mvp = m_projection * m_model;
    m_program->setUniformValue("mvpMatrix", mvp);



    quintptr offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);

    m_program->enableAttributeArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);

    offset += sizeof(QVector3D);
    m_program->enableAttributeArray((m_colorAttr));
    glVertexAttribPointer(m_colorAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glDrawElements(GL_POINTS,3, GL_UNSIGNED_SHORT, nullptr);

    m_program->release();

    m_xrot += 0.5;
}

void MatchViewer::keyPressEvent(QKeyEvent *event) {
    switch(event->key())
    {
        case Qt::Key_Up:
        {
            m_xrot-=0.5f;
            break;
        }
        case Qt::Key_Down:
        {
            m_xrot+=0.5f;
            break;
        }
        case Qt::Key_Left:
        {
            m_yrot-=0.5f;
            break;
        }
        case Qt::Key_Right:
        {
            m_yrot+=0.5f;
            break;
        }
    }
    renderNow();
    OpenGLWindow::keyPressEvent(event);
}


void MatchViewer::loadShader() {
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vertshader.glsl");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fragshader.glsl");
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    m_colorAttr = m_program->attributeLocation("colorAttr");
}

void MatchViewer::initGeometry() {
    glGenBuffers(2, &m_vboIds[0]);
    // Transfer vertex data to VBO 0
    VertexData vertices[] = {
        {QVector3D(-0.2f, -0.8f, 0.0f), QVector3D(0.36f, 0.0f, 0.0f)},
        {QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(0.00f, 0.8f, 0.0f)},
        {QVector3D( 0.0f,  0.0f, 0.0f), QVector3D(0.00f, 0.0f, 0.3f)},
    };
    std::cout << "size of vertices " << sizeof(vertices) << '\n';
    GLushort indices[] = {0, 1, 2};

    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}
