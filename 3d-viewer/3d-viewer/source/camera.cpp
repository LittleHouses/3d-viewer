
#include "camera.hpp"


const float camera::VEC_DELTA(0.000001);
/*
camera::camera() : _position(glm::vec3(0)), _lookAt(glm::vec3(0,0,-1))
{
    buildTansforms();
}

camera::camera(glm::vec3 pos) : _position(pos)
{
    _lookAt = glm::vec3(pos.x,pos.y, pos.z - 1);
    
    buildTansforms();
}
 */

camera::camera(glm::vec3 pos, glm::vec3 lookAt, float near, float far, float horizontalFOV, float verticalFOV, int imageWidth, int imageHeight) : _position(pos), _lookAt(lookAt), _near(near), _far(far), _xFOV(horizontalFOV), _yFOV(verticalFOV), _imageWidth(imageWidth), _imageHeight(imageHeight)
{
    buildTansforms();
    calculateScreenSpace();
}

void camera::buildTansforms()
{
    //What can go wrong? Missing position or lookAt. lookAt == forward.
    //Check that they aren't too close together. May change later.
    assert(glm::length(_position - _lookAt) > VEC_DELTA);
        
    _forward = glm::normalize(_position - _lookAt);
    _right = glm::cross(glm::vec3(0,1,0), _forward);
    _up = glm::cross(_forward, _right);
    
    _cameraToWorld[0] = { _right.x, _up.x, _forward.x, _position.x };
    _cameraToWorld[1] = { _right.y, _up.y, _forward.y, _position.y };
    _cameraToWorld[2] = { _right.z, _up.z, _forward.z, _position.z };
    _cameraToWorld[3] = { 0, 0, 0, 1};
    
    _worldToCamera = glm::inverse(_cameraToWorld);
}

glm::vec3 camera::worldToCamera(glm::vec3& pW)
{
    glm::vec4 res = _worldToCamera * glm::vec4(pW, 1);
    
    return glm::vec3(res.x, res.y, res.z);
}

void camera::calculateScreenSpace()
{
    _t = _near * std::tan(_yFOV / 2);
    _b = -_t;
    
    _r = _near * std::tan(_xFOV / 2);
    _l = -_r;
}

glm::vec3 camera::cameraToScreen(glm::vec3& pCam)
{
    //Property of similar triangles.
    // Note that we are looking down -z.
    return glm::vec3((_near * pCam.x) / -pCam.z, (_near * pCam.y) / -pCam.z, -pCam.z);
}

glm::vec3 camera::screenToNDC(glm::vec3& pScreen)
{

    float xNDC = (2 * pScreen.x) / (_r - _l) - (_r + _l) / (_r - _l);
    
    float yNDC = (2 * pScreen.y) / (_t - _b) - (_t + _b) / (_t - _b);
    
    return glm::vec3(xNDC, yNDC, pScreen.z);
}

glm::vec3 camera::NDCToRaster(glm::vec3 &pNDC)
{
    float xRast = (pNDC.x + 1) / 2 * _imageWidth;
    float yRast = (pNDC.y + 1) / 2 * _imageHeight;
    float zRast = -pNDC.z;
    
    return glm::vec3(xRast, yRast, zRast);
}

glm::vec3 camera::position()
{
    return _position;
}

glm::vec3 camera::forward()
{
    return _forward;
}

glm::vec3 camera::up()
{
    return _up;
}

glm::vec3 camera::right()
{
    return _right;
}

glm::mat4 camera::cameraToWorldMatrix()
{
    return _cameraToWorld;
}
