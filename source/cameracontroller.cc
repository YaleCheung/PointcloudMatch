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
    m.rotate(angle, 0.0f, 1.0f, 0.0f); // rotate along x axis
    _updateDirection();
}

void CameraController::yaw(float angle) {

}

void CameraController::pitch(float angle) {

}

void CameraController::translate(const QVector3D& direction) {
    _camera->setView(_camera->getEye() + direction, _camera->getAt() + direction, _camera->getUp());
}
