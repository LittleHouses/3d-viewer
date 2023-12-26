
#ifndef geometry_hpp
#define geometry_hpp

#include <glm/vec3.hpp>

template<typename T>
class vec2
{
public:
    T x;
    T y;
    vec2() : x{0}, y{0} {};
    vec2(T _x, T _y) : x{_x}, y{_y} {};
};

template<typename T>
class vec3
{
public:
    T x;
    T y;
    T z;
    vec3() : x{0}, y{0}, z{0} {};
    vec3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z} {};
};

using vec2f = vec2<float>;
using vec3f = vec3<float>;

class triangle
{
public:
    glm::vec3 vertices[3];
    triangle();
    triangle(glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
    {
        vertices[0] = v0;
        vertices[1] = v1;
        vertices[2] = v2;
    }
};

#endif /* geometry_hpp */

