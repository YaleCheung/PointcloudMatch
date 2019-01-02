#include "../include/cameracontroller.h"

CameraController::CameraController(std::shared_ptr<Camera> camera) :
    _camera(camera),
    _cam_pos(_camera->getEye()),
    _speed(0.0f) {
    _updateDirection();
}

void CameraController::zoom(float factor = 0.01){
    _updateDirection();
    _cam_pos += factor * _cam_direction;
    _camera->setView(_cam_pos, _camera->getAt(), _camera->getUp());
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

void CameraController::translate(const QVector3D& new_pos) {
    QVector3D vec = new_pos - _camera->getEye();
    QVector3D at = _camera->getAt() + vec;
    _camera->setView(vec, at, _camera->getUp());
}
