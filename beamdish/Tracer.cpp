// MIT License

// Copyright (c) 2019 Ganesh Belgur Ramachandra

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include <iostream>
#include <cfloat>

#include "beamdish/primitives/HitableList.hpp"
#include "beamdish/utils/Camera.hpp"
#include "beamdish/materials/Lambertian.hpp"
#include "beamdish/materials/Metal.hpp"
#include "beamdish/materials/Dielectric.hpp"
#include "beamdish/lights/DiffuseLight.hpp"
#include "beamdish/primitives/Sphere.hpp"
#include "beamdish/primitives/XYRectangle.hpp"
#include "beamdish/primitives/XZRectangle.hpp"
#include "beamdish/primitives/YZRectangle.hpp"
#include "beamdish/primitives/FlipNormals.hpp"

using namespace Beamdish;

Vec3f color(const Ray& r, HitablePtr world, int depth)
{
    HitRecord record;

    if(world->hit(r, 0.001f, FLT_MAX, record))
    {
        Ray scattered;
        Vec3f attenuation;

        // For emissive surfaces
        Vec3f emitted =
            record.assignedMaterial->emitted(record.u, record.v, record.hitPosition);

        if(depth < 50 &&
           record.assignedMaterial->scatter(r, record, attenuation, scattered))
        {
            return emitted + attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return emitted;
        }
    }
    else
    {
        return Vec3f(0.0f, 0.0f, 0.0f);
    }
}

HitablePtr cornellBox()
{
    HitablePtr *list = new HitablePtr[8];

    int i = 0;
    TexturePtr texture = TexturePtr(new ConstantTexture(Vec3f(15.0f, 15.0f, 15.0f)));
    MaterialPtr light = MaterialPtr(new DiffuseLight(texture));

    texture = TexturePtr(new ConstantTexture(Vec3f(0.65f, 0.05f, 0.05f)));
    MaterialPtr red = MaterialPtr(new Lambertian(texture));
    texture = TexturePtr(new ConstantTexture(Vec3f(0.73f, 0.73f, 0.73f)));
    MaterialPtr white = MaterialPtr(new Lambertian(texture));
    texture = TexturePtr(new ConstantTexture(Vec3f(0.12f, 0.45f, 0.15f)));
    MaterialPtr green = MaterialPtr(new Lambertian(texture));
    MaterialPtr glass = MaterialPtr(new Dielectric(1.5f));
    MaterialPtr bronzeMetal = MaterialPtr(new Metal(Vec3f(0.7, 0.6, 0.5), 0.0));

    list[i++] = HitablePtr(new FlipNormals(HitablePtr(new YZRectangle(0, 555, 0, 555, 555, green))));
    list[i++] = HitablePtr(new YZRectangle(0, 555, 0, 555, 0, red));
    list[i++] = HitablePtr(new XZRectangle(213, 343, 227, 332, 554, light));
    list[i++] = HitablePtr(new FlipNormals(HitablePtr(new XZRectangle(0, 555, 0, 555, 555, white))));
    list[i++] = HitablePtr(new XZRectangle(0, 555, 0, 555, 0, white));
    list[i++] = HitablePtr(new FlipNormals(HitablePtr(new XYRectangle(0, 555, 0, 555, 555, white))));
    list[i++] = HitablePtr(new Sphere(75.0f, Vec3f(370.0f, 277.5f, 277.5f), glass));
    list[i++] = HitablePtr(new Sphere(75.0f, Vec3f(185.0f, 277.5f, 277.5f), bronzeMetal));

    return HitablePtr(new HitableList(list, i));
}

int main()
{
    // The resolution of the image frame
    int nx = 2048;
    int ny = 1152;

    // The number of samples per pixel
    int ns = 50;

    // The header info for the PPM image format
    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    // Generating a scene to render
    HitablePtr world = cornellBox();

    // Preparing a camera to view to the scene
    Vec3f lookfrom(278.0f, 278.0f, -800.0f);
    Vec3f lookat(278.0f, 278.0f, 0.0f);
    float distance_of_focus = 10.0f;
    float aperture = 0.0f;
    float vfov = 40.0f;

    Camera cam(
            lookfrom,
            lookat,
            Vec3f(0.0f, 1.0f, 0.0f),
            vfov,
            float(nx)/float(ny),
            aperture,
            distance_of_focus
    );

    // Main render loop which renders all the
    // pixels in the image to be rendered.
    for(int j = ny - 1; j >= 0; j--)
    {
        for(int i = 0; i < nx; i++)
        {
            Vec3f colors(0, 0, 0);

            // For each pixel create multiple Ray
            // samples within the pixel's range,
            // i.e nx + (0.0f to 1.0f) and ny + (0.0f to 1.0f)
            for(int z = 0; z < ns; z++)
            {
                float u = float(i + drand48()) / float(nx);
                float v = float(j + drand48()) / float(ny);
                Ray r = cam.getRay(u, v);
                colors += color(r, world, 0);
            }

            // Average out the sampled colors for the pixel
            colors /= (float)ns;

            // Correct the gamma
            colors = Vec3f(sqrt(colors.x()), sqrt(colors.y()), sqrt(colors.z()));

            // Convert the color to interger values in the range 0
            // to 255 from values in range 0.0f to 1.0f
            int ir = (int) 255 * colors.x();
            int ig = (int) 255 * colors.y();
            int ib = (int) 255 * colors.z();

            // Print the color in the PPM format
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
