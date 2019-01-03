#include "../include/cameracontroller.h"

CameraController::CameraController(std::shared_ptr<Camera> camera) :
    _camera(camera),
    _cam_pos(_camera->getEye()),
    _speed(0.0f) {
    _updateDirection();
}

void CameraController::zoom(float factor = DEFAULT_FACTOR){
    _camera->setPerspectiveProj(DEFAULT_FOV + factor, float(DEFAULT_HEIGHT) / float(DEFAULT_WIDTH), DEFAULT_NEAR, DEFAULT_FAR);
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

}

void CameraController::pitch(float angle) {

}

void CameraController::translate(const QVector3D& direction) {
    _camera->setView(_camera->getEye() + direction, _camera->getAt() + direction, _camera->getUp());
}
