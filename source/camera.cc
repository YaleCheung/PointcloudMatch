#include "../include/camera.h"
//#include "basicmesh.h"
#include <cmath>

#include "../include/camera.h"

void Camera::setView(const QVector3D& eye, const QVector3D& at, const QVector3D& up) {
    _eye = eye;
    _at = at;
    _up = up;
    _updateView();
}

void Camera::setOrthoProj(float left, float right, float bottom, float top, float near_plane, float far_plane) {
    _projection.ortho(left, right, bottom, top, near_plane, far_plane);
}

void Camera::setPerspectiveProj(float vertical_angle, float aspect_ratio, float near_plane, float far_plane) {
    _projection.perspective(vertical_angle, aspect_ratio, near_plane, far_plane);
}
