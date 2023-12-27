
#ifndef rasterizer_hpp
#define rasterizer_hpp

#include <glm/vec3.hpp>

class rasterizer
{
private:
    
public:
    //Return the barycentric coords for a give point and associated triangle verices. (?) Returns (0,0,0) if the point lies outside the triangle
    static bool edgeFunction(const glm::vec3& a, const glm::vec3& b, const glm::vec3& p);
    static glm::vec3 barycentric(const glm::vec3& a, const glm::vec3& b, const glm::vec3&c, const glm::vec3& p);
    static bool triangleIntersection(const glm::vec3& a, const glm::vec3& b, const glm::vec3&c, const glm::vec3& p);
    
};

#endif /* rasterizer_hpp */
