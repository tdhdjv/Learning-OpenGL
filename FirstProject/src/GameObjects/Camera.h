#pragma once
#include "glm/glm.hpp"
#include "glm/vec3.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera {
private:
    float zoom;
    glm::vec3 position;

    //the vaulue is in radians
    float pitch;
    float yaw;
    float roll;

    glm::vec3 view;
    
    glm::vec3 right;
    glm::vec3 front;
    
    glm::mat4 viewMat;
    glm::mat4 projectionMat;
public:
    Camera();

    void update(float dt);

    void setView(glm::vec3 view);
    void setPosition(glm::vec3 position);
    void setPitch(float pitch);
    void setYaw(float yaw);
    void setRoll(float roll);

    inline const glm::mat4& getViewMat() const { return viewMat; }
    inline const glm::mat4& getProjectionMat() const { return projectionMat; }
    inline glm::vec3 getView() {return view;}
    inline glm::vec3 getPosition() {return position;}
    inline glm::vec3 getRight() {return right;}
    inline glm::vec3 getFront() {return front;}
    inline float getPitch() {return pitch;}
    inline float getYaw() {return yaw;}
    inline float getRoll() {return roll;}
private:
    void calcSetView();
    void calcSetViewMat();
    void calcSetViewCardinalDirection();
};