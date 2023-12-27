// Cpp v17


#include <iostream>
#include <png++/png.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "geometry.hpp"
#include "camera.hpp"
#include "rasterizer.hpp"

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

glm::vec3 fullPipeline(camera& cam, const glm::vec3& vec)
{
    glm::vec3 proc = vec;
    proc = cam.worldToCamera(proc);
    proc = cam.cameraToScreen(proc);
    proc = cam.screenToNDC(proc);
    proc = cam.NDCToRaster(proc);
    return proc;
}

void printV3(glm::vec3 vec)
{
    std::cout << "< " << vec.x << " " << vec.y << " " << vec.z << " >" << endl;
}

int main()
{
    const int width = 512;
    const int height = 512;
    glm::vec3 camP(0,0,-10);
    glm::vec3 lookAt(0,0,10);
    camera cam = camera(camP, lookAt, 1, 10000, 90, 90, width, height);
    
    //Loop throught each pixel and determine if it is in the triangle
    glm::vec3 v0(-2, 0, 1);
    glm::vec3 v1(0, 4, 1);
    glm::vec3 v2(2, 0, 1);
    
    v0 = fullPipeline(cam, v0);
    v1 = fullPipeline(cam, v1);
    v2 = fullPipeline(cam, v2);
    
    printV3(v0);
    printV3(v1);
    printV3(v2);
    
    glm::vec3 * frame_buffer = new glm::vec3[width * height];
    
    for(uint32_t h = 0; h < height; ++h)
    {
        for(uint32_t w = 0; w < width; ++w)
        {
            glm::vec3 pixel(w + 0.5, h + 0.5, 1);
            
            if(rasterizer::triangleIntersection(v0, v1, v2, pixel))
            {
                frame_buffer[h * width + w] = glm::vec3(1,0,0.88);
                //frame_buffer[width * h + w] = rasterizer::barycentric(v0, v1, v2, pixel);
            }
            else
            {
                frame_buffer[h * width + w] = glm::vec3(0,0,0);
            }
        }
    }
    
    png::image<png::rgb_pixel> image(width, height);
    
    for(uint32_t i = 0; i < height; ++i)
    {
        for(uint32_t j = 0; j < width; ++j)
        {
            glm::vec3 vec  = frame_buffer[i * width + j];
            image[i][j] = png::rgb_pixel(vec.x * 255, vec.y * 255, vec.z *255);
        }
    }
    
    image.write("/Users/wbdigital/Desktop/Renders/raster_0.png");
    
    return 0;
}




