#include "Camera.h"
#define PI 3.14159265359

Camera::Camera()
    : zoom(1.0),
    position(0.0),
    pitch(0.0),
    yaw(0.0),
    roll(0.0),
    right(-1.0, 0.0, 0.0),
    front(0.0, 0.0, 1.0),
    view(0, 0, -1.0),
    projectionMat(glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f)) {
    calcSetView();
};

void Camera::setView(glm::vec3 view) {
    this->view = glm::normalize(view);
    calcSetViewCardinalDirection();
    calcSetViewMat();
}

void Camera::setPosition(glm::vec3 position) {
    this->position = position;
    calcSetViewMat();
}

void Camera::setPitch(float pitch) {
    this->pitch = pitch;
    if (this->pitch > PI/2) {
        this->pitch = PI / 2;
    }
    if (this->pitch < -PI / 2) {
        this->pitch = -PI / 2;
    }
    calcSetView();
}

void Camera::setYaw(float yaw) {
    this->yaw = yaw;
    calcSetView();
}

void Camera::setRoll(float roll) {
    this->roll = roll;
    calcSetViewMat();
}

void Camera::calcSetView() {
    glm::vec3 newView = glm::normalize(glm::vec3(sin(yaw)*cos(pitch), sin(pitch), cos(yaw)*cos(pitch)));
    view = newView;
    calcSetViewCardinalDirection();
    calcSetViewMat();
}

void Camera::calcSetViewMat() {
    viewMat = glm::lookAt(position, position+view, glm::vec3(0.0, 1.0, 0.0));
}

void Camera::calcSetViewCardinalDirection() {
    right = glm::normalize(glm::cross(glm::vec3(0.0, 1.0, 0.0), view));
    front = glm::normalize(glm::cross(right, glm::vec3(0.0, 1.0, 0.0)));
}