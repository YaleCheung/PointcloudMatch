#ifndef CAMERA_HHH
#define CAMERA_HHH

#include <QVector3D>
#include <QString>
#include <QMatrix4x4>

class Camera {
public:
    Camera(float aspect_ratio) :
        _aspect_ratio(aspect_ratio) {
        resetView();
        _view.lookAt(QVector3D{0.0f, 0.0f, 5.0f},
                     QVector3D{0.0f, 0.0f, 0.0f},
                     QVector3D{0.0f, 1.0f, 0.0f});
        resetProj();
        _projection.perspective(45, _aspect_ratio, 1, 1000);
    }
    ~Camera(){}

    void resetView() { _view.setToIdentity();}
    void resetProj() {
        _projection.setToIdentity();
    }

    void setView(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
    void setEye(const QVector3D& eye) { _eye = eye; _updateView();}
    void setAt(const QVector3D& at) { _at = at; _updateView();}
    void setUp(const QVector3D& up) { _up = up; _updateView();}
    void moveTo(QVector3D& eye) { setEye(eye); }

    // Projection
    void setOrthoProj(float left, float right, float bottom, float top, float near_plane, float far_plane);
    void setPerspectiveProj(float vertical_angle, float aspect_ratio, float near_plane, float far_plane);

     // todos: rotation transmations
    //void rotRoll(float angle_rad);
    //void rotYaw(float angle_rad);
    //void rotPitch(float angle_rad);
    //void camRotate(float degree, QVector3D axis);


    // get set
    const QMatrix4x4& getView() {return _view;}
    const QMatrix4x4& getProj() {return _projection;}
    const QVector3D& getEye() {return _eye;}
    const QVector3D& getAt() {return _at;}
    const QVector3D& getUp() {return _up;}

private:

    void _updateView() { _view.lookAt(_eye, _at, _up); }
    QVector3D _eye;
    QVector3D _at;
    QVector3D _up;

    QMatrix4x4 _view;   // for convinence;
    QMatrix4x4 _projection;
    float _aspect_ratio;
};

#endif // CAMERA_HHHclass Camera
