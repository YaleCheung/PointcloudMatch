#ifndef CAMERA_HHH
#define CAMERA_HHH

#include <QVector3D>
#include <QString>
#include <QMatrix4x4>

constexpr float DEFAULT_RATIO = 0.75;
constexpr float DEFAULT_FOV = 45.0;
constexpr float DEFAULT_NEAR = 1.0;
constexpr float DEFAULT_FAR = 1000.0;

class Camera {
public:
    Camera(float aspect_ratio = DEFAULT_RATIO) :
        _aspect_ratio(aspect_ratio) {
        resetView();
        _view.lookAt(QVector3D{0.0f, 0.0f, 5.0f},
                     QVector3D{0.0f, 0.0f, 0.0f},
                     QVector3D{0.0f, 1.0f, 0.0f});
        resetProj();
        _projection.perspective(DEFAULT_FOV, _aspect_ratio, DEFAULT_NEAR, DEFAULT_FAR);
    }
    ~Camera(){}

    void resetView() { _view.setToIdentity();}
    void resetProj() { _projection.setToIdentity(); }

    void setView(const QVector3D& eye, const QVector3D& at, const QVector3D& up);
    void setEye(const QVector3D& eye) { _eye = eye; _updateView();}
    void setAt(const QVector3D& at) { _at = at; _updateView();}
    void setUp(const QVector3D& up) { _up = up; _updateView();}
    void moveTo(const QVector3D& eye) { setEye(eye); }

    // Projection
    void setOrthoProj(const QRectF& rect);
    void setPerspectiveProj(float fov, float aspect_ratio, float near_plane, float far_plane);

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
