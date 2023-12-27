
#include "rasterizer.hpp"


bool rasterizer::edgeFunction(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &p)
{
    return ((p.x - a.x) * (b.y - a.y) - (p.y - a.y) * (b.x - a.x) >= 0);
}

glm::vec3 rasterizer::barycentric(const glm::vec3& a, const glm::vec3& b, const glm::vec3&c, const glm::vec3& p)
{
    float tri_area = edgeFunction(a,b,c);
    
    assert(tri_area > 0);
    
    float a_area = edgeFunction(b,c,p);
    float b_area = edgeFunction(c, a, p);
    float c_area = edgeFunction(a,b, p);
    
    return glm::vec3(a_area / tri_area, b_area / tri_area, c_area / tri_area);
    
}

bool rasterizer::triangleIntersection(const glm::vec3 &a, const glm::vec3 &b, const glm::vec3 &c, const glm::vec3 &p)
{
    return edgeFunction(a, b, p) & edgeFunction(b,c,p) & edgeFunction(c, a, p);
    
}
