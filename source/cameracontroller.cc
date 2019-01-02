#include "../include/cameracontroller.h"

CameraController::CameraController(std::shared_ptr<Camera> camera) :
    _camera(camera),
    _cam_pos(_camera->getEye()),
    _speed(0.0f) {
    _updateDirection();
}

void CameraController::zoom(float factor = 0.01){
    //_updateDirection();
    //_cam_pos += factor * _cam_direction;
    //_camera->setView(_cam_pos, _camera->getAt(), _camera->getUp());
    _camera->setPerspectiveProj(45, 0.75, 1.01, 1000);
}


void CameraController::roll(float angle) {
    QMatrix4x4 m;
    m.rotate(angle, 0.0f, 1.0f, 0.0f); // rotate along x axis
    //_camera->getUp() = _camera->getUp()
    _updateDirection();
}

void CameraController::yaw(float angle) {

}

void CameraController::pitch(float angle) {

}

void CameraController::translate(const QVector3D& direction) {
    _camera->setView(_camera->getEye() + direction, _camera->getAt() + direction, _camera->getUp());
}
