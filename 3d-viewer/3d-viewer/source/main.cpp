// Cpp v17


#include <iostream>
#include <png++/png.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "geometry.hpp"
#include "camera.hpp"

using namespace std;

void hello_png()
{
    png::image< png::rgb_pixel > image(1080, 1080);
    for (png::uint_32 y = 0; y < image.get_height(); ++y)
    {
        for (png::uint_32 x = 0; x < image.get_width(); ++x)
        {
            image[y][x] = png::rgb_pixel(x, y, x + y);
            // non-checking equivalent of image.set_pixel(x, y, ...);
        }
    }
    image.write("/Users/wbdigital/Desktop/Renders/rgb.png");
}

void hello_glm()
{
    glm::mat4 mat;
    
    mat[0] = {1,2,3,4};
    
    cout << mat[0][2] << endl;
}

int main()
{
    glm::vec3 camP(0,0,-1);
    glm::vec3 lookAt(0,0,0);
    camera cam = camera(camP, lookAt, 1, 1000, 90, 30, 800, 800);
    
    
    
    return 0;
}




