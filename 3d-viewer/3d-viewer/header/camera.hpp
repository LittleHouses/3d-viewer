
#ifndef camera_hpp
#define camera_hpp

#include <cassert>
#include <cmath>
#include <iostream>

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


class camera
{
public:

private:
    static const float VEC_DELTA;
    float _near;
    float _far;
    float _xFOV;
    float _yFOV;
    float _l,_r,_t,_b;
    int _imageWidth;
    int _imageHeight;
    //resolution _resolution;
    glm::vec3 _position;
    glm::vec3 _lookAt;
    glm::vec3 _forward;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::mat4 _cameraToWorld;
    glm::mat4 _worldToCamera;
    
    void buildTansforms();
    void calculateScreenSpace();
    
public:
    //camera();
    //camera(glm::vec3 pos);
    camera(glm::vec3 pos, glm::vec3 lookAt, float near, float far, float horizontalFOV, float verticalFOV, int imageWidth, int imageHeight);
    
    glm::vec3 position();
    glm::vec3 forward();
    glm::vec3 up();
    glm::vec3 right();
    glm::mat4 cameraToWorldMatrix();
    glm::mat4 worldToCameraMatrix();
    
    glm::vec3 worldToCamera(glm::vec3& pos);
    glm::vec3 cameraToScreen(glm::vec3& pos);
    glm::vec3 screenToNDC(glm::vec3& pos);
    glm::vec3 NDCToRaster(glm::vec3& pos);
};

#endif /* camera_hpp */
