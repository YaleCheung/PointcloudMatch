#include "../include/matchviewer.h"
#include "../include/point.h"


MatchViewer::MatchViewer(QWindow *parent) :
    OpenGLWindow(parent),
    _xrot(0.0f),
    _yrot(0.0f),
    _zrot(0.0f) { }

MatchViewer::~MatchViewer() {
    glDeleteBuffers(2, &_vbo_ids[0]);
}

void MatchViewer::initialize() {
    initGeometry();
    glClearColor(1.0f, 1.0f, 1.0f, 0.5f);
    glClearDepthf(1.0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);
    glPointSize(10.0f);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    loadShader();

}

void MatchViewer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _program->bind();


    _model.setToIdentity();
    _model.rotate(_xrot, 1.0f, 0.0f, 0.0f);


    camera->resetView();
    camera->setView(QVector3D(5.0f, 10.0f, 5.0), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 1.0f));
    auto mvp = camera->getProj() * camera->getView() * _model;
    _program->setUniformValue("mvp", mvp);



    quintptr offset = 0;
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_ids[0]);

    _program->enableAttributeArray(_pos_attr);
    glVertexAttribPointer(_pos_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);

    offset += sizeof(QVector3D);
    _program->enableAttributeArray((_color_attr));
    glVertexAttribPointer(_color_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void*)offset);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_ids[1]);
    glDrawElements(GL_POINTS,3, GL_UNSIGNED_SHORT, nullptr);

    _program->release();

    _xrot += 0.5;
}

void MatchViewer::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Up: {
            _xrot-=0.5f;
            break;
        }
        case Qt::Key_Down: {
            _xrot+=0.5f;
            break;
        }
        case Qt::Key_Left: {
            _yrot-=0.5f;
            break;
        }
        case Qt::Key_Right: {
            _yrot+=0.5f;
            break;
        }
    }
    renderNow();
    OpenGLWindow::keyPressEvent(event);
}


void MatchViewer::loadShader() {
    _program = std::unique_ptr<QOpenGLShaderProgram>(new QOpenGLShaderProgram(this));
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader/vertshader.glsl");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader/fragshader.glsl");
    _program->link();
    _pos_attr = _program->attributeLocation("pos_attr");
    _pos_attr = _program->attributeLocation("color_attr");
}

void MatchViewer::initGeometry() {
    glGenBuffers(2, &_vbo_ids[0]);
    // Transfer vertex data to VBO 0
    VertexData vertices[] = {
        {QVector3D(-0.2f, -0.8f, 0.0f), QVector3D(0.36f, 0.0f, 0.0f)},
        {QVector3D(-1.0f, -1.0f, 0.0f), QVector3D(0.40f, 0.8f, 0.0f)},
        {QVector3D( 1.0f,  0.0f, 0.0f), QVector3D(0.00f, 0.20f, 0.0f)},
    };
    GLushort indices[] = {0, 1, 2};

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_ids[0]);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(VertexData), vertices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_ids[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}
