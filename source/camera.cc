
//#include "basicmesh.h"
#include <cmath>

#include "../include/camera.h"

void Camera::setView(const QVector3D& eye, const QVector3D& at, const QVector3D& up) {
    _eye = eye;
    _at = at;
    _up = up;
    _updateView();
}

void Camera::setOrthoProj(const QRectF& rect) {
    _projection.setToIdentity();
    _projection.ortho(rect);
}

void Camera::setPerspectiveProj(float fov, float aspect_ratio, float near_plane, float far_plane) {
    _projection.setToIdentity();
    _projection.perspective(fov, aspect_ratio, near_plane, far_plane);
}
