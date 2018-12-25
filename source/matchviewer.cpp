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
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    loadShader();
    //glDepthFunc(GL_LEQUAL);

}

void MatchViewer::render() {
    m_program->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_modelView.setToIdentity();
    m_modelView.translate(0, 0, -7.0);
    m_modelView.rotate(m_xrot, 1.0, 0.0, 0.0);
    m_modelView.rotate(m_yrot, 0.0, 1.0, 0.0);
    m_modelView.rotate(m_zrot, 0.0, 1.0, 1.0);

    //m_program->setUniformValue("mvMatrix", m_modelView);
    m_program->setUniformValue("mvpMatrix", m_projection * m_modelView);


    //quintptr offset = 0;

    //glDrawElements(GL_POINTS, 2, GL_UNSIGNED_SHORT, 0);

    quintptr offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);

    m_program->enableAttributeArray(m_posAttr);
    glVertexAttribPointer(m_posAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);

    offset += sizeof(QVector3D);
    m_program->enableAttributeArray((m_colorAttr));
    glVertexAttribPointer(m_colorAttr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);
    //glPointSize(10.0f);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glDrawElements(GL_POINTS, 3, GL_UNSIGNED_INT, 0);

    m_program->release();
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
        {QVector3D{-0.2, -0.8, 0.0}, QVector3D{0.36, 0.0, 0.0}},
        {QVector3D{-1.0, -1.0, 0.0}, QVector3D{0.00, 0.8, 0.0}},
        {QVector3D{ 0.0,  0.0, 0.0}, QVector3D{0.00, 0.0, 0.3}},
    };
    std::cout << "size of vertices " << sizeof(vertices) << '\n';
    GLushort indices[] = {0, 1, 2};

    glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}
