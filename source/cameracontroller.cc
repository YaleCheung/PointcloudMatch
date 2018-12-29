#include "../include/cameracontroller.h"

CameraController::CameraController(std::shared_ptr<Camera> camera) :
    _camera(camera),
    _cam_pos(_camera->getEye()),
    _cam_direction(_camera ->getEye() - _camera ->getAt()),
    _speed(0.0f) {}

void CameraController::zoom(float factor = 0.1){
    _cam_pos += factor * _cam_direction;
    // cam center would be shifted, find the center along the direction;
    // the line function could be expressed as:
    // ax + by + cz + d = 0; (a, b, c) is the direction, _cam_pos is a point in the line
    // then d could be figured out by:
    auto d =  - _cam_pos.x() * _cam_direction.x()
              - _cam_pos.y() * _cam_direction.y()
              - _cam_pos.z() * _cam_direction.z();

    auto new_center = QVector3D{0.0f, 0.0f, -d / _cam_direction.z()};
    _camera->setView(_cam_pos, new_center, _camera->getUp());
}


void CameraController::roll(float angle) {

}

void CameraController::yaw(float angle) {

}

void CameraController::pitch(float angle) {

}
