#include "../include/cameracontroller.h"

CameraController::CameraController(std::shared_ptr<Camera> camera) :
    _camera(camera),
    _cam_pos(_camera->getEye()),
    _speed(0.0f) {
    _updateDirection();
}

void CameraController::zoom(float factor = DEFAULT_FACTOR){
    _camera->setPerspectiveProj(DEFAULT_FOV + factor, DEFAULT_RATIO, DEFAULT_NEAR, DEFAULT_FAR);
}


void CameraController::roll(float angle) {
    QMatrix4x4 m;
    m.setToIdentity();
    m.rotate(angle, _cam_direction); // rotate along x axis

    // up vector;
    QVector4D up_4d = (_camera->getUp());
    up_4d = up_4d * m;
    setCamView(_camera->getEye(), _camera->getAt(), QVector3D(up_4d.x(), up_4d.y(), up_4d.z()));
}

void CameraController::yaw(float angle) {
    QMatrix4x4 m;
    m.setToIdentity();
    m.rotate(angle, _camera->getUp()); // rotate along x axis

    // up vector;
    QVector4D direction_4d = _cam_direction;
    direction_4d = direction_4d * m;
    QVector3D new_at = _camera ->getEye() - QVector3D(direction_4d.x(), direction_4d.y(), direction_4d.z());
    setCamView(_camera->getEye(), new_at, _camera->getUp());
}

void CameraController::pitch(float angle) {
    QMatrix4x4 m;
    QVector3D cam_pitch_axis = QVector3D::crossProduct(_cam_direction, _camera ->getUp());
    m.setToIdentity();
    m.rotate(angle, cam_pitch_axis); // rotate along x axis

    QVector4D direction_4d = _cam_direction;
    direction_4d = direction_4d * m;

    QVector3D new_at = _camera ->getEye() - QVector3D(direction_4d.x(), direction_4d.y(), direction_4d.z());
    setCamView(_camera->getEye(), new_at, _camera->getUp());
}

void CameraController::translate(const QVector3D& direction) {
    setCamView(_camera->getEye() + direction, _camera -> getAt() + direction, _camera->getUp());
}
