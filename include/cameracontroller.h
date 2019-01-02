#ifndef CAMERACONTROLLER_H
#define CAMERACONTROLLER_H

#include "../include/camera.h"
#include "noncopyable.h"
#include <memory>
#include <QRectF>

class CameraController : NonCopyable {
public:
    CameraController(std::shared_ptr<Camera> camera);
    void zoom(float factor);
    void moveTo(QVector3D pos) { _camera -> moveTo(pos); }
    void roll(float angle);
    void yaw(float angle);
    void pitch(float angle);
    void translate(const QVector3D& new_pos);

    void resetView() { _camera->resetView(); }
    void resetProj() { _camera->resetProj(); }

    void setCamView(const QVector3D& eye, const QVector3D& at, const QVector3D& up) {
        _cam_pos = eye;
        _cam_direction = eye - at;
        _camera->setView(eye, at, up);
    }

    void setOthoModel(const QRectF& rect) { _camera->setOrthoProj(rect); }
    void setPersModel(float fov, float aspect_ratio, float near, float far) {_camera -> setPerspectiveProj(fov, aspect_ratio, near, far);}

    const QMatrix4x4& getCamView() {return _camera -> getView();}
    const QMatrix4x4& getCamProj() {return _camera -> getProj();}
private:
    void _updateDirection() {
        _cam_direction = _camera -> getEye() - _camera->getAt();
        _cam_direction.normalize();
    }

    std::shared_ptr<Camera> _camera;
    QVector3D _cam_pos;
    QVector3D _cam_direction;
    float _speed;
};

#endif // CAMERACONTROLLER_H
